#include "utilities.h"

#include <sstream>
#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;

steady_clock::time_point startTime;


int convertDateToInt(const string& dateStr) {
    int day, month, year;
    char sep1, sep2;
    istringstream ss(dateStr);
    ss >> day >> sep1 >> month >> sep2 >> year;


    if (sep1 != '/' || sep2 != '/' || day < 1 || month < 1 || year < 1) {
        return -1; // 
    }

    return year * 10000 + month * 100 + day;
}

void startTimer() {
    startTime = steady_clock::now();
}

void stopTimer() {
    steady_clock::time_point endTime = steady_clock::now();
    auto duration = duration_cast<milliseconds>(endTime - startTime).count();
    cout << "Completed in " << duration << " milliseconds." << endl;
}

string cleanWord(const string& word) {
    string cleaned;
    for (char c : word) {
        if (isalnum(c)) {
            cleaned += tolower(c);
        }
    }
    return cleaned;
}

