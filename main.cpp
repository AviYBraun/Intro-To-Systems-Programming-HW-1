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
	std::ofstream targetFile(argv[3]);
	if(std::string(argv[1]) == "format") {
		BlockChainDump(refBlock, targetFile);
		return 0;
	}
	if(std::string(argv[1]) == "hash") {
		BlockChainDumpHashed(refBlock, targetFile);
		return 0;
	}
	if(std::string(argv[1]) == "compress") {
		BlockChainCompress(refBlock);
		BlockChainDump(refBlock, targetFile);
		return 0;
	}
	if(std::string(argv[1]) == "verify") {
		targetFile.close();
		std::ifstream targetFile(argv[3]);
		if(BlockChainVerifyFile(refBlock, targetFile)) {
		std::cout << "Verification passed";
		} else {
			std::cout << "Verification failed";
		}
		return 0;

	}
}