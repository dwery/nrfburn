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
	printf("nrfburn v0.1  build %s %s\n", __DATE__, __TIME__);
	puts("Usage: nrfburn [options]");	puts("Options:");	puts("  -f <flashsize>   Specify flash size in kilobytes. Only 16 or 32 are valid.");	puts("                   Default is 16kB.");	puts("  -w <filename>    Write contents of HEX file to nRF target MainBlock flash.");	puts("                   Automatically performs a chip erase before programming.");	puts("                   Does a verification pass after writing is complete.");	puts("  -v <filename>    Verify nRF target MainBlock with contents of HEX file.");	puts("  -r <filename>    Read nRF target MainBlock into HEX file.");	puts("  -p <filename>    Read nRF target InfoPage into HEX file.");	puts("  -e               Perform a chip erase. This erases only the MainBlock, ");	puts("                   and leaves the InfoPage intact.");	puts("  -i <chipID>      Erase the InfoPage and write the specified chip ID.");	puts("                   This also performs a chip erase.");	puts("                   chipID must be in the format xx-xx-xx-xx-xx");	puts("                   where x is a hex digit.");	puts("  -s               Reset the target nRF chip.");	puts("");
}

struct Options
{
	std::string		WriteMBFrom;	// HEX -> MainBlock
	std::string		ReadMBInto;		// MainBlock -> HEX
	std::string		VerifyWith;		// HEX with MainBlock
	std::string		ReadIPInto;		// InfoPage -> HEX
	std::string		ChipID;
	int				FlashSize;
	bool			EraseAll;
	bool			ResetTarget;

	Options()
		: FlashSize(16*1024), EraseAll(false), ResetTarget(false)
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
			++c;

			if (c < argc)
				opt.VerifyWith = argv[c];
			else
				throw std::string("Invalid HEX file name.");
				
			break;
			
		case 's':
			opt.ResetTarget = true;
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
	// open the programmer
	Programmer prg(opt.FlashSize);

	printf("\nOpening programmer\n");
	prg.Open();
	
	// just reset the target and return
	if (opt.ResetTarget)
	{
		puts("");
		prg.ResetTarget();
		puts("\nTarget has been reset.");
		return;
	}	
	
	puts("Reading Flash registers");
	prg.BeginProgramming();
	
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
		prg.WriteMainBlock(opt.WriteMBFrom);
		prg.VerifyMainBlock(opt.WriteMBFrom);
		printf("\nMainBlock flash written from %s\n", opt.WriteMBFrom.c_str());
	} else if (!opt.ReadMBInto.empty()) {
		prg.ReadMainBlock(opt.ReadMBInto);
		printf("\nMainBlock contents saved into %s\n", opt.ReadMBInto.c_str());
	} else if (!opt.VerifyWith.empty()) {
		prg.VerifyMainBlock(opt.VerifyWith);
		printf("\nMainBlock flash verified with %s\n", opt.VerifyWith.c_str());
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
