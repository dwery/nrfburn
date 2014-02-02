#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#include <string>
#include <memory>

#include "programmer.h"
#include "flashmem.h"
#include "utils.h"

void PrintHelp()
{
	printf("nrfburn v0.1   build %s %s\n", __DATE__, __TIME__);
	printf("Usage: nrfburn [options]\n");
	printf("Options:\n");
	printf("  -f <flashsize>   Specify flash size in kilobytes. Only 16 or 32 are valid.\n");
	printf("                   Default is 16kB.\n");
	printf("  -w <filename>    Write contents of HEX file to nRF target MainBlock flash.\n");
	printf("                   Automatically performs a chip erase before programming.\n");
	printf("                   Does a verification pass after writing is complete.\n");
	printf("  -v               Skip the flash write verification.\n");
	printf("  -r <filename>    Read nRF target MainBlock into HEX file.\n");
	printf("  -p <filename>    Read nRF target InfoPage into HEX file.\n");
	printf("  -e               Perform a chip erase. This erases only the MainBlock, \n");
	printf("                   and leaves the InfoPage intact.\n");
	printf("  -i <chipID>      Erase the InfoPage and write the specified chip ID.\n");
	printf("                   This also performs a chip erase.\n");
	printf("                   chipID must be in the format xx-xx-xx-xx-xx\n");
	printf("                   where x is a hex digit.\n");
	printf("\n");
}

struct Options
{
	std::string		WriteMBFrom;	// HEX -> MainBlock
	std::string		ReadMBInto;		// MainBlock -> HEX
	std::string		ReadIPInto;		// InfoPage -> HEX
	std::string		ChipID;
	int				FlashSize;
	bool			EraseAll;
	bool			DoVerify;

	Options()
		: FlashSize(16*1024), EraseAll(false), DoVerify(true)
	{}
};

void ParseArgs(const int argc, const char* argv[], Options& opt)
{
	int c = 1;
	while (c < argc)
	{
		if (argv[c] == NULL  ||  *argv[c] != '-'  ||  strlen(argv[c]) < 2)
			throw std::string("Invalid argument.");

		switch (argv[c][1])
		{
		case 'w':
			++c;

			if (c < argc)
				opt.WriteMBFrom = argv[c];
			else
				throw std::string("Invalid HEX file name.");

			break;
		case 'r':
			++c;

			if (c < argc)
				opt.ReadMBInto = argv[c];
			else
				throw std::string("Invalid HEX file name.");

			break;
		case 'p':
			++c;

			if (c < argc)
				opt.ReadIPInto = argv[c];
			else
				throw std::string("Invalid HEX file name.");

			break;
		case 'e':
			opt.EraseAll = true;
			break;
		case 'f':
			++c;

			opt.FlashSize = 0;
			
			if (c < argc)
			{
				if (strcmp(argv[c], "16") == 0)
					opt.FlashSize = 16*1024;
				else if (strcmp(argv[c], "32") == 0)
					opt.FlashSize = 32*1024;
			}
			
			if (opt.FlashSize == 0)
				throw std::string("Invalid flash size.");
			
			break;
		case 'i':
			++c;

			if (c < argc)
				opt.ChipID = argv[c];
			else
				throw std::string("ChipID not specified.");

			break;
		case 'v':
			opt.DoVerify = false;
			break;
		default:
			throw std::string("Invalid command line option: -") + argv[c][1];
			break;
		}

		++c;
	}
}

std::string int2str(const int i)
{
	char buff[32];
	snprintf(buff, sizeof buff, "%d", i);
	return buff;
}

void DoProg(const Options& opt)
{
	// open the port
	Programmer prg(opt.FlashSize);

	printf("\nOpening programmer and reading Flash registers\n");

	prg.Open();

	// print the FSR and FPCR
	printf("\nnRF device flash registers:\n");
	printf("FPCR = 0x%02x\n", prg.GetFPCR());
	printf("FSR  = 0x%02x    DBG=%i  STP=%i  RDISMB=%i  RDISIP=%i\n",
					prg.GetFSR(),
					prg.GetFSR() & (1<<FSR_DBG) ? 1 : 0,
					prg.GetFSR() & (1<<FSR_STP) ? 1 : 0,
					prg.GetFSR() & (1<<FSR_RDISMB) ? 1 : 0,
					prg.GetFSR() & (1<<FSR_RDISIP) ? 1 : 0);

	printf("\nMainBlock readback %s\nInfoPage readback %s\n\n",
					prg.CanReadMainBlock() ? "enabled" : "disabled",
					prg.CanReadInfoPage() ? "enabled" : "disabled");

	// check if the target nRF device is present.
	// if the nRF is not present, we will read the FSR register as 0xff.
	// 0xff is not a valid value on a powered nRF, because bit 0 is always
	// read as 0.
	if (!prg.IsTargetPresent())
		throw std::string("FSR == 0xff. Target device not found.");
	
	if (opt.EraseAll)
	{
		prg.EraseAll();
	} else if (!opt.WriteMBFrom.empty()) {
		prg.WriteMainBlock(opt.WriteMBFrom, opt.DoVerify);
		printf("\nMainBlock flash written from %s\n", opt.WriteMBFrom.c_str());
	} else if (!opt.ReadMBInto.empty()) {
		prg.ReadMainBlock(opt.ReadMBInto);
		printf("\nMainBlock contents saved into %s\n", opt.ReadMBInto.c_str());
	} else if (!opt.ReadIPInto.empty()) {
		prg.ReadInfoPage(opt.ReadIPInto);
		printf("\nInfoPage contents saved into %s\n", opt.ReadIPInto.c_str());
	} else if (!opt.ChipID.empty()) {
		prg.WriteInfoPage(opt.ChipID);
		printf("ChipID %s written.\n", opt.ChipID.c_str());
	}
}

int main(const int argc, const char* argv[])
{
	try {
		Options opt;
		if (argc == 1)
		{
			PrintHelp();
			return 1;
		}

		ParseArgs(argc, argv, opt);

		DoProg(opt);
	} catch (std::string& e) {
		fprintf(stderr, "\nError: %s\n", e.c_str());
		return 1;
	}

	return 0;
}
