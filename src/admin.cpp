#include <iostream>
#include "../include/admin.h" 
#include "../include/manageQuiz.h"
using namespace std;

void admin(){

    int choice;

    cout << "Please select an option: \n"
    << "1. Manage quizzes \n"
    << "2. Logout \n";

while(true){

        cin.ignore();
        cin >> choice;

    switch(choice){

        case 1:
        manageQuiz();
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