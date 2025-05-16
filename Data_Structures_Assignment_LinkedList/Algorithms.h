#pragma once
#define ALGORITHMS_H
#include "Transaction_Handler.h"
extern int comparisonCount;

struct WordCountNode {
    string word;
    int count;
    WordCountNode* next;
};

void bubbleSortTransactions(TransactionNode* head);
void mergeSortTransactions(TransactionNode** headRef);
void insertionSortTransactions(TransactionNode** headRef);
void insertSorted(TransactionNode** sortedRef, TransactionNode* newNode);

void transactionsLinearSearch(TransactionNode* head, const string& selectedCategory,
    const string& selectedPayment, int& baseCount, int& matchingCount);

void transactionsSentinelSearch(TransactionNode*& head, const string& selectedCategory,
    const string& selectedPayment, int& baseCount, int& matchingCount);


WordCountNode* insertSortWordCounts(WordCountNode* head);
WordCountNode* mergeSortWordCounts(WordCountNode* head);
WordCountNode* bubbleSortWordCounts(WordCountNode* head);