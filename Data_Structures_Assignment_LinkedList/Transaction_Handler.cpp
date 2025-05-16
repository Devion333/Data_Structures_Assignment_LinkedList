#include "Transaction_Handler.h"
#include "Algorithms.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstdlib> // for stod

using namespace std;

TransactionNode* loadTransactions(const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return nullptr;
    }

    string line;
    getline(inFile, line); // skip header

    TransactionNode* head = nullptr;
    TransactionNode* tail = nullptr;

    while (getline(inFile, line)) {
        istringstream ss(line);
        string priceStr;
        Transaction t;

        if (!getline(ss, t.customerId, ',')) continue;
        if (!getline(ss, t.product, ',')) continue;
        if (!getline(ss, t.category, ',')) continue;
        if (!getline(ss, priceStr, ',')) continue;
        if (!getline(ss, t.date, ',')) continue;
        if (!getline(ss, t.paymentMethod)) continue;

        try {
            t.price = stod(priceStr);
        }
        catch (...) {
            continue; // skip invalid entries
        }

        TransactionNode* newNode = new TransactionNode{ t, nullptr };

        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    inFile.close();
    return head;
}

void displayTransactions(TransactionNode* head) {
    cout << left
        << setw(15) << "Customer ID"
        << setw(15) << "Product"
        << setw(20) << "Category"
        << setw(15) << "Price"
        << setw(15) << "Date"
        << "Payment Method" << endl;

    cout << string(100, '-') << endl;

    TransactionNode* current = head;
    while (current != nullptr) {
        const Transaction& t = current->data;
        cout << left
            << setw(15) << t.customerId
            << setw(15) << t.product
            << setw(20) << t.category
            << setw(15) << fixed << setprecision(2) << t.price
            << setw(15) << t.date
            << t.paymentMethod << endl;

        current = current->next;
    }
}

int countTransactions(const TransactionNode* head) {
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}


void freeTransactionList(TransactionNode* head) {
    while (head != nullptr) {
        TransactionNode* temp = head;
        head = head->next;
        delete temp;
    }
}


void calculatePercentage(TransactionNode* head, const string& selectedCategory, const string& selectedPayment, int searchChoice) {
    int baseCount = 0, matchingCount = 0;
    switch (searchChoice) {
    case 1:
        transactionsLinearSearch(head, selectedCategory, selectedPayment, baseCount, matchingCount);
        break;
    case 2:
        transactionsSentinelSearch(head, selectedCategory, selectedPayment, baseCount, matchingCount);
        break;
    default:
        cout << "Invalid search choice.\n";
        return;
    }
    if (baseCount == 0) {
        cout << "No transactions match the selected filter(s).\n";
        return;
    }

    double percentage = static_cast<double>(matchingCount) / baseCount * 100.0;
    cout << fixed << setprecision(2);

    if (selectedCategory != "All") {
        cout << "Out of " << baseCount << " purchases in " << selectedCategory << ", "
            << matchingCount << " used " << selectedPayment << ".\n";
    }
    else {
        cout << "Out of " << baseCount << " purchases using " << selectedPayment << ", "
            << matchingCount << " were in " << selectedCategory << ".\n";
    }

    cout << "Percentage: " << percentage << "%\n";
}