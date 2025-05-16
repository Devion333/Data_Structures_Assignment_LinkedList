#include "Review_Handler.h"
#include "utilities.h"
#include "Algorithms.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
using namespace std;

ReviewNode* loadReviews(const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cerr << "Error opening reviews file: " << filename << endl;
        return nullptr;
    }

    string line;
    getline(inFile, line); // skip header

    ReviewNode* head = nullptr;
    ReviewNode* tail = nullptr;

    while (getline(inFile, line)) {
        istringstream ss(line);
        string ratingStr;
        Review review;

        if (!getline(ss, review.productId, ',')) continue;
        if (!getline(ss, review.customerId, ',')) continue;
        if (!getline(ss, ratingStr, ',')) continue;
        if (!getline(ss, review.reviewText)) continue;

        review.rating = stoi(ratingStr);

        ReviewNode* newNode = new ReviewNode{ review, nullptr };
        if (!head) {
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

void displayReviews(const ReviewNode* head) {
    cout << left
        << setw(15) << "Product ID"
        << setw(15) << "Customer ID"
        << setw(8) << "Rating"
        << "Review Text" << endl;

    cout << string(80, '-') << endl;

    while (head) {
        cout << left
            << setw(15) << head->data.productId
            << setw(15) << head->data.customerId
            << setw(8) << head->data.rating
            << head->data.reviewText << endl;

        head = head->next;
    }
}

int countReviews(const ReviewNode* head) {
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}


void freeReviewList(ReviewNode* head) {
    while (head) {
        ReviewNode* temp = head;
        head = head->next;
        delete temp;
    }
}


void analyzeOneStarWordFrequency(const ReviewNode* head, int sortChoice) {
    WordCountNode* wordList = nullptr;

    while (head) {
        if (head->data.rating == 1) {
            istringstream ss(head->data.reviewText);
            string rawWord;
            while (ss >> rawWord) {
                string word = cleanWord(rawWord);
                if (word.empty()) continue;

                WordCountNode* existing = wordList;
                bool found = false;
                while (existing) {
                    if (existing->word == word) {
                        existing->count++;
                        found = true;
                        break;
                    }
                    existing = existing->next;
                }

                if (!found) {
                    WordCountNode* newNode = new WordCountNode{ word, 1, wordList };
                    wordList = newNode;
                }
            }
        }
        head = head->next;
    }

    // Sort based on user's choice
    if (sortChoice == 1)
        wordList = insertSortWordCounts(wordList);
    if (sortChoice == 2)
        wordList = mergeSortWordCounts(wordList);
    if (sortChoice == 3)
        wordList = bubbleSortWordCounts(wordList);

    // Display top 20
    cout << "\nTop 20 most frequent words in 1-star reviews:\n";
    cout << left << setw(15) << "Word" << "Count\n";
    cout << "---------------------------\n";

    int displayed = 0;
    WordCountNode* current = wordList;

    // Continue until we've displayed 20 words or run out of words
    while (current && displayed < 20) {
        // Only display words that have 4 or fewer characters
        if (current->word.length() >= 4) {
            cout << left << setw(15) << current->word << current->count << endl;
            displayed++;
        }
        current = current->next;
    }
    // Cleanup
    while (wordList) {
        WordCountNode* temp = wordList;
        wordList = wordList->next;
        delete temp;
    }
}