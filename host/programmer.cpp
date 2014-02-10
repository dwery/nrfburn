#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <string>
#include <memory>

#include "programmer.h"
#include "utils.h"

// This one reads the response from the programmer.
// The first byte is always the length of the data block to read.
void Programmer::ReadResponseRaw(uint8_t* buff, size_t buff_size)
{
	memset(buff, 0, buff_size);		// wipe the buffer
	
	resp_simple_t* pResp = (resp_simple_t*) buff;
	
	int cnt = 0;
	while (cnt < 15)
	{
		hidBurn.ReadFirst(buff);

		// if we have a response of length == 0 that means the programmer is still busy
		if (pResp->length != 0)
			break;
			
		// wait a little
		// ...
		
		cnt++;
	}

	if (pResp->length == 0)
		throw std::string("Timeout on read data from programmer.");
	
	// read the rest of the message if necessary
	if (pResp->length > HIDREP_FIRST_BYTES)
		hidBurn.ReadSecond(buff + HIDREP_FIRST_BYTES);
	
	// calc the checksum
	int c;
	uint8_t sum = 0;
	for (c = 0; c < pResp->length; ++c)
		sum ^= buff[c];

	if (sum)
		throw std::string("Programmer to host communication error - bad checksum.");

	if (pResp->response == respError)
	{
		resp_error_t* pRespErr = (resp_error_t*) buff;
		if (pRespErr->error_code == respErrBadChecksum)
			throw std::string("Host to programmer communication error - bad checksum.");
		else if (pRespErr->error_code == respErrTimeoutExpired)
			throw std::string("Programmer timeout expired -- check connection.");
	}
}

template <class Resp>
void Programmer::ReadResponse1(Resp& resp)
{
	uint8_t buff[MAX_PROT_BUFF_SIZE];
	
	ReadResponseRaw(buff, sizeof buff);
	
	if (buff[0] != sizeof resp)
		throw std::string("Unexpected response from programmer.");
		
	memcpy(&resp, buff, sizeof resp);
}

template <class Resp1, class Resp2>
size_t Programmer::ReadResponse2(Resp1& resp1, Resp2& resp2)
{
	uint8_t buff[MAX_PROT_BUFF_SIZE];
	
	ReadResponseRaw(buff, sizeof buff);
	
	size_t retVal = 0;
	if (buff[0] == sizeof resp1)
	{
		memcpy(&resp1, buff, sizeof resp1);
		retVal = 1;
	} else if (buff[0] == sizeof resp2) {
		memcpy(&resp2, buff, sizeof resp2);
		retVal = 2;
	} else {
		throw std::string("Unexpected response from programmer.");
	}
	
	return retVal;
}

template <class Req>
void reqSetChecksum(Req& req)
{
	uint8_t* pChecksum = &req.checksum;
	uint8_t* pData = (uint8_t*) &req;
	*pChecksum = 0;
	while (pData < pChecksum)
		*pChecksum ^= *pData++;
}

inline uint8_t req2resp(const int req)
{
	return req | 0x80;
}

void Programmer::ProgressBar::Refresh(const double progress)
{
	double seconds = (clock() - time_begin) / double(CLOCKS_PER_SEC);

	std::string hashes(size_t(progress * 50), '#');

	printf("\r%-10s | %-50s | %3i%%  %.2fs", process_name, hashes.c_str(), int(progress * 100), seconds);
	fflush(stdout);
}

Programmer::~Programmer()
{
	if (needsProgEnd)
		ProgEnd();
}

void Programmer::CheckProgrammerVer()
{
	// send version request
	req_simple_t req;
	req.length = sizeof req;
	req.request = reqVersion;
	reqSetChecksum(req);
	hidBurn.Write(req);
	
	// read the response
	resp_version_t resp_ver;
	ReadResponse1(resp_ver);

	if (resp_ver.response != req2resp(reqVersion))
		throw std::string("Unexpected response from programmer while reading version code.");

	if (resp_ver.ver_major != PRG_VER_MAJOR  ||  resp_ver.ver_minor != PRG_VER_MINOR)
		throw std::string("Programmer and host version mismatch. "
							"Host: v" + int2str(PRG_VER_MAJOR) + "." + int2str(PRG_VER_MINOR)
							+ " Programmer: v" + int2str(resp_ver.ver_major) + "." + int2str(resp_ver.ver_minor));
}

void Programmer::ReadFlashRegisters()
{
	// read FSR and FPCR
	req_simple_t read_regs;
	read_regs.length = sizeof read_regs;
	read_regs.request = reqReadFsrFpcr;
	reqSetChecksum(read_regs);
	hidBurn.Write(read_regs);

	resp_read_fsr_fpcr_t resp_regs;
	ReadResponse1(resp_regs);

	if (resp_regs.response != req2resp(reqReadFsrFpcr))
		throw std::string("Unexpected response from programmer while reading flash registers.");
		
	fsr = resp_regs.fsr;
	fpcr = resp_regs.fpcr;
}

void Programmer::ProgBegin()
{
	// send ProgBegin request
	req_simple_t req;
	req.length = sizeof req;
	req.request = reqProgBegin;
	reqSetChecksum(req);
	hidBurn.Write(req);

	// validate response
	resp_simple_t resp;
	ReadResponse1(resp);

	if (resp.response != req2resp(reqProgBegin))
		throw std::string("Unexpected response from programmer in ProgBegin()");

	needsProgEnd = true;
}

void Programmer::ProgEnd()
{
	// send ProgEnd request
	req_simple_t req;
	req.length = sizeof req;
	req.request = reqProgEnd;
	reqSetChecksum(req);
	hidBurn.Write(req);

	// validate response
	resp_simple_t resp;
	ReadResponse1(resp);

	if (resp.response != req2resp(reqProgEnd))
		throw std::string("Unexpected response from programmer in ProgEnd()");

	needsProgEnd = false;
}

void Programmer::Open()
{
	// open the port
	hidBurn.Open();

	CheckProgrammerVer();
}

void Programmer::BeginProgramming()
{
	// in case the last programming session ended before a ProgEnd
	// due to a crash or Ctrl-Break
	ProgEnd();

	// tell the programmer to enable the programming mode on the nRF
	ProgBegin();

	// read FSR and FPCR
	ReadFlashRegisters();
}

void Programmer::EraseAll()
{
	ProgressBar pb("Erase all");
	
	// send ERASE_ALL request
	req_simple_t req;
	req.length = sizeof req;
	req.request = reqEraseAll;
	reqSetChecksum(req);
	hidBurn.Write(req);

	pb.Refresh(0.5);
	
	// validate response
	resp_simple_t resp;
	ReadResponse1(resp);

	if (resp.response != req2resp(reqEraseAll))
		throw std::string("Unexpected response from programmer in EraseAll()");

	pb.Refresh(1);
}

void Programmer::WriteChunk(const bool isInfoPage, const FlashMemory& flash, const int offset)
{
	if (offset + PROG_CHUNK_SIZE > flash.GetFlashSize())
		throw std::string("Offset outside available flash in WriteChunk()");

	// send WriteFlash request
	req_write_flash_t req;
	req.length = sizeof req;
	req.address = offset;
	memcpy(req.data, flash.GetFlash() + offset, PROG_CHUNK_SIZE);
	req.request = isInfoPage ? reqWriteInfoPage : reqWriteMainBlock;
	reqSetChecksum(req);
	hidBurn.Write(req);

	// validate the response
	resp_simple_t resp;
	ReadResponse1(resp);

	if (resp.response != req2resp(req.request))
		throw std::string("Unexpected response from programmer in WriteChunk()");
}

void Programmer::ReadChunk(const bool isInfoPage, FlashMemory& flash, const int offset)
{
	if (offset + PROG_CHUNK_SIZE > flash.GetFlashSize())
		throw std::string("Offset outside available flash in ReadChunk()");

	// send ReadFlash request
	req_read_flash_t req;
	req.length = sizeof req;
	req.address = offset;
	req.request = isInfoPage ? reqReadInfoPage : reqReadMainBlock;
	reqSetChecksum(req);
	hidBurn.Write(req);

	// We can receive one of two responses:
	// a full resp_read_flash_t response that contains the entire flash block,
	// or a resp_simple_t in case the block we've read contains only 0xff.
	// This way we are reducing times for reading and verification
	// for devices which are mostly unprogrammed.
	resp_read_flash_t resp1;
	resp_simple_t resp2;
	
	memset(&resp1, 0, sizeof resp1);
	memset(&resp2, 0, sizeof resp2);
	
	size_t activeResp = ReadResponse2(resp1, resp2);

	if (resp1.response != req2resp(req.request)  &&  resp2.response != req2resp(req.request))
		throw std::string("Unexpected response from programmer in ReadChunk()");

	if (activeResp == 1)
		// copy the chunk to the flash object
		memcpy(flash.GetFlash() + offset, resp1.data, PROG_CHUNK_SIZE);
	else
		// or just set everything to 0xff
		memset(flash.GetFlash() + offset, 0xff, PROG_CHUNK_SIZE);
}

void Programmer::ReadMainBlock(const std::string& hexfilename)
{
	// is MainBlock readback disabled?
	if (!CanReadMainBlock())
		throw std::string("MainBlock readback is disabled by the target configuration.");

	ProgressBar pb("Reading");

	FlashMemory flash(flashSize);

	int address = 0;
	while (address < flash.GetFlashSize())
	{
		ReadChunk(false, flash, address);

		address += PROG_CHUNK_SIZE;

		// update the progress bar
		pb.Refresh(address / double(flash.GetFlashSize()));
	}

	// now save everything
	flash.SaveHex(hexfilename);
}

void Programmer::ReadInfoPage(const std::string& hexfilename)
{
	// is MainBlock readback disabled?
	if (!CanReadInfoPage())
		throw std::string("InfoPage readback is disabled by the chip config.");

	FlashMemory flash(InfoPageSize);

	int address = 0;
	while (address < flash.GetFlashSize())
	{
		ReadChunk(true, flash, address);
		address += PROG_CHUNK_SIZE;
	}
	
	// print the chip ID
	const uint8_t* pFlash = flash.GetFlash();
	printf("Chip ID = %02x-%02x-%02x-%02x-%02x\n", pFlash[0x0B], pFlash[0x0C], pFlash[0x0D], pFlash[0x0E], pFlash[0x0F]);

	// now save everything
	flash.SaveHex(hexfilename);
}

void Programmer::WriteMainBlock(const std::string& hexfilename)
{
	FlashMemory flash(flashSize);
	
	flash.LoadHex(hexfilename);		// read the HEX file

	// do the flash writing
	ProgressBar pb("Writing MB");
	
	EraseAll();			// erase the chip's MainBlock

	// start writing the flash
	int address = 0;
	while (address < flash.GetFlashSize())
	{
		const uint8_t* pChunk = flash.GetFlash() + address;

		// Check all the bytes of the chunk to see if we have any non-0xff bytes. This is
		// good because we don't want to waste time sending an empty block for programming.
		int bytes = 0, c;
		for (c = 0; c < PROG_CHUNK_SIZE; c++)
		{
			if (pChunk[c] != 0xff)
				bytes = c + 1;
		}

		// do we have a non-empty block?
		if (bytes)
			WriteChunk(false, flash, address);

		address += PROG_CHUNK_SIZE;

		// update the progress bar
		pb.Refresh(address / double(flash.GetFlashSize()));
	}
}

void Programmer::VerifyMainBlock(const std::string& hexfilename)
{
	ProgressBar pb("Verifying");
	
	FlashMemory flash(flashSize);
	flash.LoadHex(hexfilename);		// read the HEX file
	
	FlashMemory verifyFlash(flashSize);

	int address = 0;
	while (address < flashSize)
	{
		ReadChunk(false, verifyFlash, address);

		address += PROG_CHUNK_SIZE;

		// update the progress bar
		pb.Refresh(address / double(flashSize));
	}

	// now compare
	if (flash != verifyFlash)
	{
		/*flash.SaveHex("orig.hex");
		verifyFlash.SaveHex("verif.hex");*/
		throw std::string("MainBlock verification failed.");
	}
}

void Programmer::WriteInfoPage(const std::string& chipID)
{
	// first parse the chipID
	uint8_t chip_id[5];
	const char* pEnd = chipID.c_str();
	int c;
	for (c = 0; c < 5  &&  *pEnd; ++c)
	{
		long int res = strtol(pEnd, (char**) &pEnd, 16);
		if (res < 0  ||  res > 0xff  ||  (*pEnd != '\0'  &&  *pEnd != '-'))
			throw std::string("Incorrect ChipID format.");

		chip_id[c] = uint8_t(res);

		if (*pEnd)
			pEnd++;
	}

	// do an erase all
	// we must do this for the chip to allow an InfoPage erase
	EraseAll();

	ProgressBar pb("Writing IP");
	
	// send the erase page command
	req_erase_page_t erasePage;
	erasePage.page_num = 0;
	erasePage.length = sizeof erasePage;
	erasePage.request = reqErasePageIP;
	reqSetChecksum(erasePage);
	hidBurn.Write(erasePage);

	pb.Refresh(0.3);
	
	// validate the response
	resp_simple_t resp;
	ReadResponse1(resp);

	if (resp.response != req2resp(reqErasePageIP))
		throw std::string("Unexpected response from programmer while erase page in WriteInfoPage()");

	// now init and send the new InfoPage
	req_write_flash_t writeFlash;
	writeFlash.length = sizeof writeFlash;
	writeFlash.address = 0;
	writeFlash.request = reqWriteInfoPage;
	memset(writeFlash.data, 0xff, sizeof writeFlash.data);
	memcpy(writeFlash.data + 0x0B, chip_id, sizeof chip_id);
	reqSetChecksum(writeFlash);
	hidBurn.Write(writeFlash);

	pb.Refresh(0.6);
	
	// validate
	ReadResponse1(resp);

	if (resp.response != req2resp(reqWriteInfoPage))
		throw std::string("Unexpected response from programmer while writing page in WriteInfoPage()");
		
	pb.Refresh(1);
}

void Programmer::ResetTarget()
{
	ProgressBar pb("Resetting");

	pb.Refresh(0.3);
	
	req_simple_t resetTarget;
	resetTarget.length = sizeof resetTarget;
	resetTarget.request = reqResetTarget;
	reqSetChecksum(resetTarget);
	hidBurn.Write(resetTarget);

	pb.Refresh(0.6);
	
	// validate
	resp_simple_t resp;
	ReadResponse1(resp);

	if (resp.response != req2resp(resetTarget.request))
		throw std::string("Unexpected response from programmer during ResetTarget()");
	
	pb.Refresh(1);
}
