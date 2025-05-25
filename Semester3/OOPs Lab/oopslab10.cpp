#include <iostream>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <string>
using namespace std;

int main() {
    set<int> s = {1, 2, 4, 3, 6, 2}; // Set automatically removes duplicates
    cout << "Contents of set: ";
    for (int val : s) {
        cout << val << " ";
    }
    cout << endl;

    unordered_set<int> us = {1, 2, 4, 3, 6, 2}; // unordered_set removes duplicates
    cout << "Contents of unordered_set: ";
    for (int val : us) {
        cout << val << " ";
    }
    cout << endl;

    unordered_map<string, int> record;

    // b) Inserting records of 3 students
    record["John"] = 101;
    record["Alice"] = 102;
    record["Bob"] = 103;

    // Displaying all student records
    cout << "\nStudent Records:\n";
    for (const auto &entry : record) {
        cout << "Name: " << entry.first << ", Roll Number: " << entry.second << endl;
    }

    // c) Performing a search to retrieve the roll number of one of the students
    string name_to_search = "Alice";
    if (record.find(name_to_search) != record.end()) {
        cout << "\nRoll number of " << name_to_search << " is " << record[name_to_search] << endl;
    } else {
        cout << name_to_search << " not found in the records." << endl;
    }

    return 0;
}
