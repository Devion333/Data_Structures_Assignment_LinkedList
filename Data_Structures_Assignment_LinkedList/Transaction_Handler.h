#pragma once
#define TRANSACTION_HANDLER_H
#include <string>
using namespace std;

struct Transaction {
    string customerId;
    string product;
    string category;
    double price;
    string date;
    string paymentMethod;
};

// Linked list node
struct TransactionNode {
    Transaction data;
    TransactionNode* next;
};

// Function declarations
TransactionNode* loadTransactions(const string& filename);
void displayTransactions(TransactionNode* head);
void freeTransactionList(TransactionNode* head);
int countTransactions(const TransactionNode* head);
void calculatePercentage(TransactionNode* head, const string& selectedCategory, const string& selectedPayment, int searchChoice);
