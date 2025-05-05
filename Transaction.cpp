#include "Transaction.h"
#include "Utilities.h"

void TransactionDumpInfo(const Transaction& transaction, ofstream& file) {

    file << "Sender Name: " << transaction.sender << std::endl;
    file <<"Receiver Name: " << transaction.receiver << std::endl;
    file <<"Transaction Value: " << transaction.value << std::endl;
}

string TransactionHashedMessage(const Transaction& transaction) {
    unsigned int value = transaction.value;
    string sender = transaction.sender;
    string receiver = transaction.receiver;
    return hash(value, sender, receiver);
}

bool TransactionVerifyHashedMessage(
        const Transaction& transaction,
        string hashedMessage
) {
    string hash = TransactionHashedMessage(transaction);
    return(hash == hashedMessage);
}



