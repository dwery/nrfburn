#pragma once

#include "hiddev.h"
#include "flashmem.h"
#include "../firmware/prg_common.h"

class Programmer
{
private:
	HIDBurner	hidBurn;		// the programmer communication

	uint8_t		fsr;
	uint8_t		fpcr;
	int			flashSize;

	bool		needsProgEnd;
	
	void CheckProgrammerVer();
	void ReadFlashRegisters();

	void ProgBegin();
	void ProgEnd();

	void WriteChunk(const bool isInfoPage, const FlashMemory& flash, const int offset);
	void ReadChunk(const bool isInfoPage, FlashMemory& flash, const int offset);

	template <class Resp>
	void ReadResponse(Resp& resp);

	enum {
		InfoPageSize = 512,
	};
	
public:
	typedef void (*ProgressCallback)(const bool is_init, const double progress);

	Programmer(const int fs)
	:	fsr(0), fpcr(0), flashSize(fs), needsProgEnd(false)
	{}

	~Programmer();

	// opens the programmer device, checks the programmer version,
	// starts the programming, reads the flash status registers
	void Open();

	uint8_t GetFSR() const		{ return fsr; }
	uint8_t GetFPCR() const		{ return fpcr; }

	bool CanReadMainBlock() const	{ return (fsr & (1<<FSR_RDISMB)) == 0; }
	bool CanReadInfoPage() const	{ return (fsr & (1<<FSR_RDISIP)) == 0; }
	bool IsTargetPresent() const	{ return (fsr & 1) == 0; }

	void EraseAll();

	void ReadMainBlock(const std::string& hexfilename, ProgressCallback printProgress = NULL);
	void WriteMainBlock(const std::string& hexfilename, const bool verify, ProgressCallback printWriteProgress = NULL, ProgressCallback printVerifyProgress = NULL);
	void VerifyMainBlock(const std::string& hexfilename, ProgressCallback printProgress = NULL);

	void ReadInfoPage(const std::string& hexfilename);
	void WriteInfoPage(const std::string& chipID);
};
