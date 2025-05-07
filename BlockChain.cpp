#include "BlockChain.h"
#include "Transaction.h"
#include "Utilities.h"

/**
 * BlockChainGetSize - returns the number of Blocks in the BlockChain
 *
 * @param blockChain - BlockChain to measure
 *
 * @return Number of Blocks in the BlockChain
 *
*/
int BlockChainGetSize(const BlockChain& blockChain) {
    int count = 0;
	//begin this way because first blockchain block is a dummy block
	const BlockChain* current = blockChain.next;
	while (current != nullptr) {
		count++;
		current = current -> next;
	}
	return count;
}


/**
 * BlockChainPersonalBalance - returns the balance of a given person, relative to a given BlockChain
 *
 * @param blockChain - BlockChain to calculate the balance from
 * @param name - Name of the person to calculate the balance for
 *
 * @return Balance of the person
 *
*/
int BlockChainPersonalBalance(const BlockChain& blockChain, const string& name) {
	int sent = 0, received = 0;
	const BlockChain* current = blockChain.next;
	while(current != nullptr) {
		if(current -> sender == name) {
			sent+= current -> value;
		} else if (current -> receiver == name){
			received = current -> value;
		}
		current = current -> next;
	}
	return received - sent;
}

/**
 * BlockChainAppendTransaction - creates and appends a new transaction to the BlockChain
 *
 * @param blockChain BlockChain to append the transaction to
 * @param value Value of the transaction
 * @param sender Name of the sender
 * @param receiver Name of the receiver
 * @param timestamp String that holds the time the transaction was made
 *
*/
void BlockChainAppendTransaction(
        BlockChain& blockChain,
        unsigned int value,
        const string& sender,
        const string& receiver,
        const string& timestamp
) {
	BlockChain* latest = new BlockChain;
	latest->value = value;
	latest->sender = sender;
	latest->receiver = receiver;
	latest->timeStamp = timestamp;
	latest->next = blockChain.next;
		//latest now points to the previous first block, which the dummy block pointed to
		//now we make our orignal next, the one associated with the blockchain, point to our newest guy
	blockChain.next = latest;

}


/**
 * BlockChainAppendTransaction - appends a copy of a given transaction to the BlockChain
 *
 * @param blockChain BlockChain to append the transaction to
 * @param transaction Transaction we want to append
 * @param timestamp String that holds the time the transaction was made
*/
void BlockChainAppendTransaction(
        BlockChain& blockChain,
        const Transaction& transaction,
        const string& timestamp
) {
	{
		BlockChain* latest = new BlockChain;
		latest->value = transaction.value;
		latest->sender = transaction.sender;
		latest->receiver = transaction.receiver;
		latest->timeStamp = timestamp;
		latest->next = blockChain.next;
		//latest now points to the previous first block, which the dummy block pointed to
		//now we make our orignal next, the one associated with the blockchain, point to our newest guy
		blockChain.next = latest;

	}
}


/**
 * BlockChainLoad - Reads data from a file and creates a new block chain
 *
 * @param file Data file to read from
 *
 * @return BlockChain created from the file
 *
*/

BlockChain BlockChainLoad(ifstream& file) {
	//temporary list to transfer all the data from the file to in reverse order
	struct tempList {
		unsigned int value;
		string sender, receiver, timestamp;
		tempList* next = nullptr;
	};
	//loop through the document and parse each line to isolate the variables
	tempList* tempHead = nullptr;
	string line;
	while(std::getline(file, line)) {
		string sender, receiver, timestamp;
		unsigned int value;
		// Parse sender
		size_t pos = line.find(' ');
		sender = line.substr(0, pos);
		line.erase(0, pos + 1);

		// Parse receiver
		pos = line.find(' ');
		receiver = line.substr(0, pos);
		line.erase(0, pos + 1);

		// Parse value
		pos = line.find(' ');
		value = std::stoul(line.substr(0, pos));
		line.erase(0, pos + 1);

		// Remaining part is timestamp
		timestamp = line;

		tempList* nextTransaction = new tempList
		{value, sender, receiver, timestamp, tempHead};
		tempHead = nextTransaction;
		}
	BlockChain blockChain;
	blockChain.next = nullptr;
	tempList* current = tempHead;
	while (current != nullptr) {
	BlockChainAppendTransaction(blockChain, current->value, current->sender,
		current->receiver,current->timestamp);
	current = current ->next;
	}
	return blockChain;
}


/**
 * BlockChainDump - Prints the data of all transactions in the BlockChain to a given file
 *
 * Data will be printed in the following format:
 *
 * BlockChain info:
 * <n>.
 * Sender Name: <name>
 * Receiver Name: <name>
 * Transaction Value: <value>
 * Transaction Timestamp: <time>
 *
 * @param blockChain BlockChain to print
 * @param file File to print to
 *
*/
void BlockChainDump(const BlockChain& blockChain, ofstream& file);



/**
 * BlockChainDumpHashed - Prints the *hashed data* of all transactions in the BlockChain to a given file
 *
 * Data will be printed in the following format:
 * <hashed message>
 * <hashed message>
 * ...
 * <hashed message>
 *
 * @param blockChain BlockChain to print
 * @param file File to print to
 *
*/
void BlockChainDumpHashed(const BlockChain& blockChain, ofstream& file);


/**
 * BlockChainVerifyFile - verifies that the file contains correct hashed messages of the given BlockChain
 *
 * Input file is expected to contain data in the following format:
 * <hashed message>
 * <hashed message>
 * ...
 * <hashed message>
 *
 * @param blockChain BlockChain to verify
 * @param file File to read from
 *
 * @return true if the file is valid, false otherwise
*/
bool BlockChainVerifyFile(const BlockChain& blockChain, std::ifstream& file);


/**
 * BlockChainCompress - Compresses the given block chain based on the transaction's data.
 * All consecutive blocks with the same sender and receiver will be compressed to one Block.
 *
 * @param blockChain BlockChain to compress
*/
void BlockChainCompress(BlockChain& blockChain);


/**
 * BlockChainTransform - Update the values of each transaction in the BlockChain
 *
 * @param blockChain BlockChain to update
 * @param function a pointer to a transform function
*/
void BlockChainTransform(BlockChain& blockChain, updateFunction function);

