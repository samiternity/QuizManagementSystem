// Major file which contains reusable utility functions

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
using namespace std;

void listTopics() {

    // New code for displaying topics.
    ifstream file("../db/topics.txt");

    if(!file) {
        cout << "Failed to display list of topics.";
    }
    string name;
    int count = 0;

    while(getline(file, name)) {
        cout << ++count << ": " << name << "\n";
    }
}

void divider() {
    cout << "\n-------------------------------------------------------\n";
}

void divider2() {
    cout <<  "\n.....................................................\n";
}

void divider3() {
    cout << "\n=====================================================\n";
}
