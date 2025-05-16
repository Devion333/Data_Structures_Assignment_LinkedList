#include <iostream>
#include <fstream>
#include <sstream>
#include "Transaction_Handler.h"
#include "Review_Handler.h"
#include "Algorithms.h"
#include "utilities.h"

int main()
{
    TransactionNode* transactionList = loadTransactions("transactions_cleaned.csv");
    ReviewNode* reviewList = loadReviews("reviews_cleaned.csv");

    int choice;
    while (true) {
        cout << "\nMenu\n";
        cout << string(30, '-') << endl;
        cout << "1. Display Total Entries in Transaction and Review Datasets\n";
        cout << "2. Display All Transactions\n";
        cout << "3. Display All Reviews\n";
        cout << "4. Sort Transactions by Date\n";
        cout << "5. Analyze Transaction Statistics\n";
        cout << "6. Analyze 1-Star Review Word Frequency\n";
        cout << "7. Exit\n";

        cout << "Choose an option: ";
        cin >> choice;
		//Display Total Entries in both Datasets
        if (choice == 1) {
            cout << "Total Transaction Count: " << countTransactions(transactionList) << endl;
            cout << "Total Review Count:  " << countReviews(reviewList) << endl;
        }
		//Display All Transactions
        else if (choice == 2) {
            displayTransactions(transactionList);
            continue;

        }
		//Display All Reviews
        else if (choice == 3) {
			displayReviews(reviewList);
            continue;
		}
        //Transaction Sorting by Date
        else if (choice == 4) {

            cout << "Choose sorting algorithm:\n";
            cout << "1. Bubble Sort\n";
            cout << "2. Merge Sort\n";
            cout << "3. Insertion Sort\n";

            int sortChoice;
			cout << "Choose an algorithm (1-3): ";
            cin >> sortChoice;

            startTimer();
            comparisonCount = 0;


            if (sortChoice == 1) {
                bubbleSortTransactions(transactionList);
                cout << endl << string(100, '-') << endl;
                cout << "Statistics of Bubble Sort:\n";
                stopTimer();
                cout << "Total comparisons: " << comparisonCount << endl;
                cout << endl << string(100, '-') << endl;
                displayTransactions(transactionList);
            }

            else if (sortChoice == 2) {
                mergeSortTransactions(&transactionList);
                cout << "Sorted using Merge Sort.\n";               
				cout << endl << string(100, '-') << endl;
				cout << "Statistics of Merge Sort:\n";
                stopTimer();
                cout << "Total comparisons: " << comparisonCount << endl;
                cout << endl << string(100, '-') << endl;
                displayTransactions(transactionList);
            }
            else if (sortChoice == 3) {
                insertionSortTransactions(&transactionList);
                cout << endl << string(100, '-') << endl;
                cout << "Statistics of Insertion Sort:\n";
                stopTimer();
                cout << "Total comparisons: " << comparisonCount << endl;
                cout << endl << string(100, '-') << endl;
                displayTransactions(transactionList);

                }
            else {
                cout << "Invalid choice.\n";
                continue;
            }
        }
        //Transaction Percentage Calculation
        else if (choice == 5) {
            const string categories[] = {
                    "Automotive", "Books", "Groceries", "Sports", "Toys",
					"Beauty", "Furniture", "Electronics", "Fashion", "Home Appliances" //List of categories
            };
            const string paymentMethods[] = {
				"Bank Transfer", "PayPal", "Debit Card", "Cash on Delivery", "Credit Card" //List of payment methods
            };

            int categoryChoice, paymentChoice;
            string selectedCategory, selectedPayment;

            cout << "\nSelect a category (0 for All):\n";
            for (int i = 0; i < sizeof(categories) / sizeof(categories[0]); ++i)
                cout << i + 1 << ". " << categories[i] << endl;
            cout << "Choice: ";
            cin >> categoryChoice;
            if (categoryChoice < 0 || categoryChoice > sizeof(categories) / sizeof(categories[0])) {
                cout << "Invalid category.\n";
                continue;
            }
            selectedCategory = (categoryChoice == 0) ? "All" : categories[categoryChoice - 1];

            cout << "\nSelect a payment method (0 for All):\n";
            for (int i = 0; i < sizeof(paymentMethods) / sizeof(paymentMethods[0]); ++i)
                cout << i + 1 << ". " << paymentMethods[i] << endl;
            cout << "Choice: ";
            cin >> paymentChoice;
            if (paymentChoice < 0 || paymentChoice > sizeof(paymentMethods) / sizeof(paymentMethods[0])) {
                cout << "Invalid payment method.\n";
                continue;
            }
            selectedPayment = (paymentChoice == 0) ? "All" : paymentMethods[paymentChoice - 1];

            if (selectedCategory == "All" && selectedPayment == "All") {
                cout << "You must select at least one filter.\n";
                continue;
            }

            int searchChoice;
            cout << "\nSelect search algorithm:\n1. Linear Search\n2. Sentinel Search\nChoice: ";
            cin >> searchChoice;
            if (searchChoice != 1 && searchChoice != 2) {
                cout << "Invalid search choice.\n";
                continue;
            }
			startTimer();
            calculatePercentage(transactionList, selectedCategory, selectedPayment, searchChoice);
			stopTimer();
			cout << "Total comparisons: " << comparisonCount << endl;
        }
		//Word Frequency Analysis
        else if (choice == 6) {
            while (true) {
                int sortChoice;
                cout << "\nChoose sorting algorithm for word frequency:\n";
                cout << "1. Insertion Sort\n";
                cout << "2. Merge Sort\n";
                cout << "3. Bubble Sort\n";
                cout << "Enter choice: ";
                cin >> sortChoice;
				comparisonCount = 0;
                if (sortChoice < 1 || sortChoice > 3) {
                    cout << "Invalid choice input!";
                    continue;
                }
                else {
                    startTimer();
                    analyzeOneStarWordFrequency(reviewList, sortChoice);
                    cout << endl << string(100, '-') << endl;
                    cout << "Statistics:\n";
                    stopTimer();
					cout << "Total comparisons: " << comparisonCount << endl;
                    break;
                }
            }

        }
        else if (choice == 7) {
            cout << "Exiting..." << endl;
            freeTransactionList(transactionList);
            return 0;
        }
        else {
            cout << "Invalid choice. Try again..." << endl;
        }


    }
}




