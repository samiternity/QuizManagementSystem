#include <iostream>
#include <fstream> // For file handling
#include <string>  // For basic string operations

#include "include/admin.h"
#include "include/player.h"

using namespace std;

// Function prototypes
void registerUser();
bool isUsernameUnique(const string &username);
void loginUser();
bool validateLogin(const string &username, const string &password, const string &accountType);
void forgotPassword();
void saveUserToFile(const string &userData);

int main() {
    cout << "Welcome to the Quiz Management System!\n";
    cout << "Please log in or register to continue.\n\n";

    while (true) {
        cout << "[1] Register\n";
        cout << "[2] Login\n";
        cout << "[3] Exit \n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore(); // Handle the newline character

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                cout << "Terminating the program...\n";
            return 0;
            default:
                cout << "Invalid selection. Please choose a valid option.\n";
        }
    }

    return 0;
}

void registerUser() {
    string username, password, accountType;
    int accountChoice;

    cout << "\n--- Registration ---\n";

    // Get and validate username
    bool unique;
    do {
        cout << "Enter Username: ";
        cin >> username;
        unique = isUsernameUnique(username);
        if (!unique) {
            cout << "Username already exists. Please try a different one.\n";
        }
    } while (!unique);

    // Get and validate password
    do {
        cout << "Enter Password (must include at least 8 characters): ";
        cin >> password;
        if (password.length() < 8) {
            cout << "Password must include at least 8 characters. Please try again.\n";
        }
    } while (password.length() < 8);

    // Get and validate account type
    do {
        cout << "Choose Account Type:\n[1] Admin\n[2] Player\nEnter choice: ";
        cin >> accountChoice;

        if (accountChoice == 1) {
            accountType = "Admin";
        } else if (accountChoice == 2) {
            accountType = "Player";
        } else {
            cout << "Invalid selection. Please choose a valid option.\n";
        }
    } while (accountChoice != 1 && accountChoice != 2);

    // Save user to file
    string userData = username + " " + password + " " + accountType;
    saveUserToFile(userData);
    cout << "Registration successful! Redirecting to the menu...\n\n";
}

bool isUsernameUnique(const string &username) {
    ifstream inFile("userDatabase.txt");
    if (!inFile) {
        // File does not exist, assume unique
        return true;
    }

    string storedUsername, line;
    while (inFile >> storedUsername) {
        getline(inFile, line); // Read the rest of the line
        if (storedUsername == username) {
            return false;
        }
    }
    inFile.close();
    return true;
}

void saveUserToFile(const string &userData) {
    ofstream outFile("userDatabase.txt", ios::app); // Append mode
    if (!outFile) {
        cout << "Error: Unable to save user data.\n";
        return;
    }
    outFile << userData << "\n";
    outFile.close();
}

void loginUser() {
    string username, password, accountType;

    cout << "\n--- Login ---\n";
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;

    cout << "Enter Account Type (1 for admin / 2 for player): ";
    int accountChoice;
    cin >> accountChoice;

    if (accountChoice == 1) {
        accountType = "Admin";
    } else if (accountChoice == 2) {
        accountType = "Player";
    } else {
        cout << "Invalid account type. Login failed.\n";
        return;
    }

    if (validateLogin(username, password, accountType)) {
        cout << "Login successful! Redirecting to the menu...\n\n";
        if (accountType == "Admin") {
            cout << "Welcome, Admin!\n";
            // call admin interface
            admin();
        } else {
            cout << "Welcome, Player!\n";
            // call player interface
            player();
        }
    } else {
        cout << "Invalid username or password. Please try again.\n";
        cout << "Forgot Password? (y/n): ";
        char forgot;
        cin >> forgot;
        if (tolower(forgot) == 'y') {
            forgotPassword();
        }
    }
}

bool validateLogin(const string &username, const string &password, const string &accountType) {
    ifstream inFile("userDatabase.txt");
    if (!inFile) {
        cout << "Error: Unable to open the database file.\n";
        return false;
    }

    string storedUsername, storedPassword, storedAccountType;
    while (inFile >> storedUsername >> storedPassword >> storedAccountType) {
        if (storedUsername == username && storedPassword == password && storedAccountType == accountType) {
            inFile.close();
            return true;
        }
    }
    inFile.close();
    return false;
}

void forgotPassword() {
    string username, newPassword;

    cout << "\n--- Forgot Password ---\n";
    cout << "Enter Username: ";
    cin >> username;
    ifstream inFile("userDatabase.txt");
    ofstream tempFile("tempDatabase.txt");

    if (!inFile || !tempFile) {
        cout << "Error: Unable to access the database.\n";
        return;
    }

    string storedUsername, storedPassword, storedAccountType;
    bool userFound = false;

    while (inFile >> storedUsername >> storedPassword >> storedAccountType) {
        if (storedUsername == username) {
            userFound = true;

            do {
                cout << "Enter New Password (must include at least 8 characters): ";
                cin >> newPassword;
                if (newPassword.length() < 8) {
                    cout << "Password must contain at least 8 characters. Please try again.\n";
                }
            } while (newPassword.length() < 8);

            tempFile << storedUsername << " " << newPassword << " " << storedAccountType << "\n";
            cout << "Password reset successful! Redirecting to the login screen...\n\n";
        } else {
            tempFile << storedUsername << " " << storedPassword << " " << storedAccountType << "\n";
        }
    }

    inFile.close();
    tempFile.close();

    remove("userDatabase.txt");
    rename("tempDatabase.txt", "userDatabase.txt");

    if (!userFound) {
        cout << "Invalid username. Please try again.\n\n";
    }
}