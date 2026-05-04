Intro To Systems Programming Assignment - Transaction Ledger & Blockchain Simulation
Description:
  A C++ implementation of a secure transaction ledger system. This project explores the fundamentals of systems programming, focusing on manual memory management,
  file stream manipulation, and data integrity verification through hashing.
  The primary objective of this project was to build a robust backend for managing financial transactions using a linked-list-based "Blockchain" structure.

Core Architecture
  1. The Transaction Engine
    The system defines a Transaction as a basic unit of data containing a value, a sender, and a receiver. It includes a custom hashing utility to generate unique fingerprints     for every exchange.

  2. The Blockchain Structure
    The ledger is implemented as a Singly Linked List of blocks. Each block extends the transaction data with metadata, such as a unique transactionId and a timeStamp.

  3. Data Transformation & Compression
    Compression: To optimize storage, the system identifies consecutive blocks with identical senders and receivers and merges them into a single aggregate transaction.
    Transformation: Using the updateFunction type definition, the system can apply dynamic mathematical updates to all values in the chain (e.g., applying a tax or a currency       conversion). 
