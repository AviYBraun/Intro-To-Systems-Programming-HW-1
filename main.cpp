#include "BlockChain.h"
#include "Utilities.h"
#include <fstream>
#include <iostream>
#include <string>

int main (int argc, char* argv[]) {
	if(argc != 4) {
	getErrorMessage();
	}
	// open source file and load info to a temporary blockchain
	std::ifstream sourceFile(argv[2]);
	BlockChain refBlock= BlockChainLoad(sourceFile);
	//open target doc
	if(std::string(argv[1]) == "format") {
		std::ofstream targetFile(argv[3]);
		BlockChainDump(refBlock, targetFile);
		return 0;
	}
	if(std::string(argv[1]) == "hash") {
		std::ofstream targetFile(argv[3]);
		BlockChainDumpHashed(refBlock, targetFile);
		return 0;
	}
	if(std::string(argv[1]) == "compress") {
		std::ofstream targetFile(argv[3]);
		BlockChainCompress(refBlock);
		BlockChainDump(refBlock, targetFile);
		return 0;
	}
	if(std::string(argv[1]) == "verify") {
		std::ifstream targetFile(argv[3]);
		if(BlockChainVerifyFile(refBlock, targetFile)) {
		std::cout << "Verification passed";
		} else {
			std::cout << "Verification failed";
		}
		return 0;

	}
}