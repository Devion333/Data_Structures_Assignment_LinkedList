#pragma once
#include <string>
using namespace std;
struct Review {
    string productId;
    string customerId;
    int rating;
    string reviewText;
};

struct ReviewNode {
    Review data;
    ReviewNode* next;
};


ReviewNode* loadReviews(const string& filename);
void displayReviews(const ReviewNode* head);
void freeReviewList(ReviewNode* head);
int countReviews(const ReviewNode* head);
void analyzeOneStarWordFrequency(const ReviewNode* head, int sortChoice);