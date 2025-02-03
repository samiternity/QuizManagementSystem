/* Display list of topics
 * input a topic name
 * load the selected topic's question
 * start the quiz
 * display one question at a time along with its options
 */
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <filesystem>
#include "../include/utility.h"
#include "../include/manageQuiz.h"
using namespace std;

void player();

void play() {
    // List all topics
    cout << "Here's a list of available topics: \n";
    listTopics();

    // Input a topic name
    string topicName;
    cout << "Enter a topic name: ";
    cin.ignore();
    getline(cin, topicName);

    // Load topic
    string filePath = "../db/" + topicName + ".txt";

    ifstream file(filePath);
    if (file.fail()) {
        cout << "Couldn't open the file. Please ensure the topic name is correct.\n";
        return;
    }

    Question q;
    Topic t;

    // STORING AND DISPLAYING DATA
    char ans;
    int score = 0;
    int qNum = 1;

   // cin.ignore();
    getline(file, t.name);
    file >> t.maxQues;
    file >> t.highScore;
    file.ignore();

    // Start the quiz
    divider();
    cout << "\nStarting quiz for " << t.name << "\n";
 //   << "Highest score: " << t.highScore << "\n";

    divider3();

    // Reading and displaying data
    for(int i=0; i<t.maxQues; i++) {

        // storing into struct variable
        file.ignore();
        getline(file, q.text);
        getline(file, q.optA);
        getline(file, q.optB);
        getline(file, q.optC);
        file >> q.correctOption;
        file.ignore(numeric_limits<streamsize>::max(), '\n');

        // displaying question and options and taking input and validating it
        // divider2();
        cout << "\nQuestion " << qNum++ << ": " << q.text << "\n"
             << "a. " << q.optA << "\n"
             << "b. " << q.optB << "\n"
             << "c. " << q.optC << "\n";

        // Validate answer
        do {
            cout << "Answer (a, b, or c): ";
            cin >> ans;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (ans != 'a' && ans != 'b' && ans != 'c' &&
                ans != 'A' && ans != 'B' && ans != 'C') {
                cout << "Invalid input. Please enter a, b, or c.\n";
                } else {
                    break; // Valid input
                }
        } while (true);

        // Live score
        if (toupper(ans) == toupper(q.correctOption)) {
            ++score;
            cout << "Correct answer! Your Score = " << score << endl;
        } else {
            cout << "Incorrect answer! Your Score = " << score << endl;
        }

        divider();
    }

    cout << "Quiz completed! Final Score: " << score << "\n";
    player();

   /* HIGH SCORE SYSTEM

    if(score > t.highScore) {
        cout << "NEW HIGH SCORE!!! \n";
        divider3();

        // updating topic's file with the new score.
        ifstream read(filePath);
        ofstream write("../db/temp.txt");

        if(!read || !write) {
            cout << "Unable to open files to update the high score.";
        }

        string temp;
        string high = to_string(t.highScore);
        while(getline(read, temp)) {

            if(temp == high) {
                write << score << "\n";
            }
            else {
                write << temp << "\n";
            }
        }
        read.close();
        write.close();

        filesystem::remove(filePath);
        filesystem::rename("../db/temp.txt", filePath);
    } */

}


void player(){

 divider();
 int choice;

 cout << "\n\n"
 << "Welcome! Please select an option: \n"
 << "1. Play Quiz \n"
 << "2. Logout \n\n";


 while(true){

  cin >> choice;

  switch(choice){

   case 1:
    play();
   break;

   case 2:
       return;
      break;

      default:
      cout << "Invalid selection. Try again";
   continue;
  }

  break;
 }

}