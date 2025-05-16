#include "Algorithms.h"
#include "Transaction_Handler.h"
#include "Review_Handler.h"
#include "utilities.h"
#include <iostream>
using namespace std;
int comparisonCount = 0;

//----------------------------------------------------------------------------------------------------------------------------
//---------------------------------------Transaction Sorting Algorithms-------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------
// 
//-------------------Bubble Sort-----------------------------------------
void bubbleSortTransactions(TransactionNode* head) {
    if (head == nullptr) return ;

    bool swapped;
    TransactionNode* ptr;
    TransactionNode* lastSorted = nullptr;

    do {
        swapped = false;
        ptr = head;

        while (ptr->next != lastSorted) {
            comparisonCount++;

            if (convertDateToInt(ptr->data.date) > convertDateToInt(ptr->next->data.date)) {
                swap(ptr->data, ptr->next->data);  // swap data fields
                swapped = true;
            }
            ptr = ptr->next;
        }
        lastSorted = ptr;
    } while (swapped);
    return;
}


//----------------------------------Merge Sort---------------------------------------------
TransactionNode* sortedMerge(TransactionNode* a, TransactionNode* b);
void splitList(TransactionNode* source, TransactionNode** frontRef, TransactionNode** backRef);

void mergeSortTransactions(TransactionNode** headRef) {
    TransactionNode* head = *headRef;
    if (head == nullptr || head->next == nullptr) return;

    TransactionNode* a;
    TransactionNode* b;

    // Split the list into 'a' and 'b' sublists
    splitList(head, &a, &b);

    // Recursively sort the sublists
    mergeSortTransactions(&a);
    mergeSortTransactions(&b);

    // Merge the sorted sublists
    *headRef = sortedMerge(a, b);
	return;
}

TransactionNode* sortedMerge(TransactionNode* a, TransactionNode* b) {
    // Dummy node to start the merged list
    TransactionNode dummy;
    TransactionNode* tail = &dummy;
    dummy.next = nullptr;

    while (a != nullptr && b != nullptr) {
        int dateA = convertDateToInt(a->data.date);
        int dateB = convertDateToInt(b->data.date);
        comparisonCount++;

        if (dateA <= dateB) {
            tail->next = a;
            a = a->next;
        }
        else {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }

    // Append remaining nodes
    tail->next = (a != nullptr) ? a : b;

    return dummy.next;
}

void splitList(TransactionNode* source, TransactionNode** frontRef, TransactionNode** backRef) {
    TransactionNode* slow = source;
    TransactionNode* fast = source->next;

    // Fast advances two nodes, and slow advances one
    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    // slow is before the midpoint
    *frontRef = source;
    *backRef = slow->next;
    slow->next = nullptr;
}
//------------------------------Insertion Sort------------------------------------------------
void insertSorted(TransactionNode** sortedRef, TransactionNode* newNode);

void insertionSortTransactions(TransactionNode** headRef) {
    TransactionNode* sorted = nullptr;
    TransactionNode* current = *headRef;

    while (current != nullptr) {
        TransactionNode* next = current->next;
        insertSorted(&sorted, current);
        current = next;
    }

    *headRef = sorted;
    return;
}

void insertSorted(TransactionNode** sortedRef, TransactionNode* newNode) {
    if (*sortedRef == nullptr ||
        convertDateToInt(newNode->data.date) <= convertDateToInt((*sortedRef)->data.date)) {

        comparisonCount++; // At least one comparison is made
        newNode->next = *sortedRef;
        *sortedRef = newNode;
    }
    else {
        TransactionNode* current = *sortedRef;

        while (current->next != nullptr &&
            convertDateToInt(current->next->data.date) < convertDateToInt(newNode->data.date)) {
            comparisonCount++; // Count each comparison in the loop
            current = current->next;
        }

        // One last comparison when exiting the loop (failed case)
        comparisonCount++;

        newNode->next = current->next;
        current->next = newNode;
    }

    return ;
}
//-----------------------------------------------------------------------------------------------------------------------
//---------------------------------------Transaction Searching Algorithms-------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------Linear Search---------------------------------------------------
void transactionsLinearSearch(TransactionNode* head, const string& selectedCategory, const string& selectedPayment, int& baseCount, int& matchingCount) {
    baseCount = 0;
    matchingCount = 0;

    while (head != nullptr) {
		comparisonCount++;
        bool matchesCategory = (selectedCategory == "All" || head->data.category == selectedCategory);
        bool matchesPayment = (selectedPayment == "All" || head->data.paymentMethod == selectedPayment);

        if (selectedCategory != "All" && matchesCategory) {
            baseCount++;
            if (matchesPayment) {
                matchingCount++;
            }
        }
        else if (selectedPayment != "All" && selectedCategory == "All" && matchesPayment) {
            baseCount++;
        }

        head = head->next;
    }
}
//----------------------------------------------------Sentinel Search---------------------------------------------------
void transactionsSentinelSearch(TransactionNode*& head, const string& selectedCategory, const string& selectedPayment, int& baseCount, int& matchingCount) {
    baseCount = 0;
    matchingCount = 0;

    // Create and attach sentinel node
    TransactionNode* sentinel = new TransactionNode;
    sentinel->data.category = selectedCategory;
    sentinel->data.paymentMethod = selectedPayment;
    sentinel->next = nullptr;

    if (head == nullptr) {
        delete sentinel;
        return;
    }

    // Traverse to the last node
    TransactionNode* curr = head;
    while (curr->next != nullptr) {
        curr = curr->next;
    }

    // Attach the sentinel to the end of the list
    curr->next = sentinel;

    // Sentinel search begins
    curr = head;  // Start from the beginning again
    while (curr != sentinel) {  // Stop when we reach the sentinel node
		comparisonCount++;
        bool matchesCategory = (selectedCategory == "All" || curr->data.category == selectedCategory);
        bool matchesPayment = (selectedPayment == "All" || curr->data.paymentMethod == selectedPayment);

        if (selectedCategory != "All" && matchesCategory) {
            baseCount++;
            if (matchesPayment) {
                matchingCount++;
            }
        }
        else if (selectedPayment != "All" && selectedCategory == "All" && matchesPayment) {
            baseCount++;
        }

        curr = curr->next;
    }

    // Remove sentinel
    delete sentinel;
}
//-----------------------------------------------------------------------------------------------------------------------
//---------------------------------------Review Sorting Algorithms-------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------

//-------------------Insertion Sort------------------------------------------
WordCountNode* insertSortWordCounts(WordCountNode* head) {
    WordCountNode* sorted = nullptr;

    while (head != nullptr) {
        WordCountNode* current = head;
        head = head->next;

        if (!sorted || current->count >= sorted->count) {
            current->next = sorted;
            sorted = current;
        }
        else {
            WordCountNode* temp = sorted;
            while (temp->next && temp->next->count > current->count) {
                comparisonCount++;
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
    }

    return sorted;
}

//-------------------Merge Sort----------------------------------

// Split linked list into two halves
void splitList(WordCountNode* source, WordCountNode** front, WordCountNode** back) {
    WordCountNode* slow = source;
    WordCountNode* fast = source->next;

    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = source;
    *back = slow->next;
    slow->next = nullptr;
}

// Merge two sorted lists by descending count
WordCountNode* mergeSortedLists(WordCountNode* a, WordCountNode* b) {
    if (!a) return b;
    if (!b) return a;

    WordCountNode* result = nullptr;
	comparisonCount++;

    if (a->count >= b->count) {
        result = a;
        result->next = mergeSortedLists(a->next, b);
    }
    else {
        result = b;
        result->next = mergeSortedLists(a, b->next);
    }

    return result;
}

// Merge sort main function
WordCountNode* mergeSortWordCounts(WordCountNode* head) {
    if (!head || !head->next) return head;

    WordCountNode* front;
    WordCountNode* back;

    splitList(head, &front, &back);

    front = mergeSortWordCounts(front);
    back = mergeSortWordCounts(back);

    return mergeSortedLists(front, back);
}

//-------------------Bubble Sort------------------------------------------
WordCountNode* bubbleSortWordCounts(WordCountNode* head) {
    if (!head || !head->next) return head; 

    bool swapped;
    WordCountNode* ptr1;
    WordCountNode* lptr = nullptr;

    do {
        swapped = false;
        ptr1 = head;
        WordCountNode* prev = nullptr;

        while (ptr1->next != lptr) {
			comparisonCount++;
            if (ptr1->count < ptr1->next->count) {
                // Swap nodes
                WordCountNode* tmp = ptr1->next;
                ptr1->next = tmp->next;
                tmp->next = ptr1;

                if (prev == nullptr) {
                    head = tmp;
                }
                else {
                    prev->next = tmp;
                }

                prev = tmp;
                swapped = true;
            }
            else {
                prev = ptr1;
                ptr1 = ptr1->next;
            }
        }
        lptr = ptr1;
    } while (swapped);

    return head;
}