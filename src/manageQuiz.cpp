#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include "../include/utility.h"
using namespace std;
// ---------------------------------------------------------------------------------

/*
Manage quiz for admin
- Add a new quiz topic and it's questions
- Delete a quiz topic
*/

// Declaring a struct for a question
struct Question {
    string text;
    string optA;
    string optB;
    string optC;
    char ans;
};

struct Topic {
    string name;
    int maxQues;
    int highScore;
   // vector<Question> questions;
};

void addTopic() {
    Topic t;
    Question q;

    cout << "Enter a topic name: ";
    cin.ignore();
    getline(cin, t.name);

    // const int maxQues = 3;
    // cout << "Enter the amount of questions for this topic: ";
    // cin >> t.maxQues;
    // code with error handling
    while (true) {
        cout << "Enter the amount of questions for this topic: ";
        cin >> t.maxQues;

        // Validate input
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please try again.\n";
        } else {
            break;
            // exit loop when input is valid
        }
    }

    cin.ignore();

    cout << "\nEnter data for " << t.name << ", questions are limited to only " << t.maxQues << "\n\n";

    string filepath = "../db/" + t.name + ".txt";
    ofstream fout(filepath);

    // writing topic name, maxQues, and highScore in the topic's txt file
    fout << t.name << "\n"
    << t.maxQues << "\n"
    << "0 \n";

    // saving topic name in topics.txt, append mode
    ofstream file("../db/topics.txt" ,ios::app);

    if(!file) {
        cout << "Error: Unable to save topic name \n";
    }

    file << t.name << "\n";
    file.close();

    // Taking input for each question and then writing it in the topic's txt file
    // loop until maxQues
    for(int i = 0; i < t.maxQues; i++) {

        cout << "\nQuestion " << i+1 << ": ";
        getline(cin, q.text);

        cout << "a: ";
        getline(cin, q.optA);

        cout << "b: ";
        getline(cin, q.optB);

        cout << "c: ";
        getline(cin, q.optC);

        cout << "Correct option (a,b,c): ";
        cin >> q.ans;
        cin.ignore();

        // Validate answer
        while (q.ans != 'a' && q.ans != 'b' && q.ans != 'c') {
            cout << "Invalid option. Please enter a, b, or c: ";
            cin >> q.ans;
            cin.ignore();
        }

        // save to file
        fout << q.text << "\n"
            << q.optA << "\n"
            << q.optB << "\n"
            << q.optC << "\n"
            << q.ans << "\n";

       // t.questions.push_back(q);
    }

    if (!fout) {
        cerr << "Error: Unable to create file " << filepath << endl;
        return;
    }

    fout.close();
    cout << "Data saved successfully!\n";
}

/* Function to delete a topic
 * display topics
 * choose a topic
 * delete its file
 * show status message
 */

void delTopic() {

    // List all topics from utility.cpp
    cout << "Here's a list of available topics: \n";
    listTopics();

    string tName;
    cout << "Enter topic name which you want to delete: ";
    cin.ignore();
    getline(cin, tName);

    string filePath = "../db/" + tName + ".txt";

    if (!filesystem::exists(filePath)) {
        cout << "Error: Topic does not exist.\n";
        return;
    }

    try {
        if (filesystem::remove(filePath)) {
            cout << "Topic deleted successfully!\n";

            // Update topics.txt
            // remove deleted topic name

            ifstream read("../db/topics.txt");
            ofstream write("../db/tempTopics.txt");

            if(!read || !write) {
                cout << "Error: Unable to open topics or tempTopics file.";
            }

            string temp;

            // searching for the topic name in the file
            while(getline(read, temp)) {

                if(temp == tName) {
                    // do nothing?
                   // cout << "";
                }
                else {
                    write << temp << "\n";
                }
            }
            cout << "Topics list has been updated";

            read.close();
            write.close();
            filesystem::remove("../db/topics.txt");
            filesystem::rename("../db/tempTopics.txt", "../db/topics.txt");


        } else {
            cout << "Error: Unable to delete topic.\n";
        }
    } catch (const filesystem::filesystem_error& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void manageQuiz() {
    while(true) {
        cout << "\nManage Quiz\n\n"
             << "1. Add a topic\n"
             << "2. Delete a topic\n"
             << "3. Exit\n\n"
             << "Select an option: ";

        int choice;
        cin >> choice;

        switch(choice) {
            case 1:
                addTopic();
                break;
            case 2:
                delTopic();
                break;
            case 3:
                return;
            default:
                cout << "Invalid selection. Please try again.\n";
                cin.clear();// Clear error flags
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear invalid input
        }
    }
}

