#ifndef MANAGE_QUIZ_H
#define MANAGE_QUIZ_H

#include <fstream>
#include <string>
#include <vector>
using namespace std;

//---------------------------------------------------------------------------------------------------------
// Struct for a question
struct Question {
    string text;
    string optA;
    string optB;
    string optC;
    char correctOption; // Store the correct option (A, B, or C)
};

// Struct for a topic
struct Topic {
    string name;
    int maxQues;
    int highScore;
    vector<Question> questions;
};

//---------------------------------------------------------------------------------------------------------
// Function declarations

// Function to add a new quiz topic
// void addTopic();

// Function to manage quizzes (main menu for admin operations)
void manageQuiz();
// void manageQuiz_();

#endif // MANAGE_QUIZ_H
