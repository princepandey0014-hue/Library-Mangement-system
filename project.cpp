#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Book {
    int bookID;
    string title, author;

public:
    void getData() {
        cout << "\nEnter Book ID: ";
        cin >> bookID;
        cin.ignore(); // clear input buffer
        cout << "Enter Book Title: ";
        getline(cin, title);
        cout << "Enter Author Name: ";
        getline(cin, author);
    }

    void showData() const {
        cout << "\nBook ID: " << bookID;
        cout << "\nTitle: " << title;
        cout << "\nAuthor: " << author << endl;
    }

    int getBookID() const { return bookID; }

    // Function to save data in text format
    void writeToFile(ofstream &outFile) const {
        outFile << bookID << "|" << title << "|" << author << "\n";
    }

    // Function to read data from text file
    bool readFromFile(ifstream &inFile) {
        string line;
        if (getline(inFile, line)) {
            size_t pos1 = line.find('|');
            size_t pos2 = line.rfind('|');
            if (pos1 != string::npos && pos2 != string::npos && pos1 != pos2) {
                bookID = stoi(line.substr(0, pos1));
                title = line.substr(pos1 + 1, pos2 - pos1 - 1);
                author = line.substr(pos2 + 1);
                return true;
            }
        }
        return false;
    }
};

void addBook() {
    Book b;
    ofstream outFile("library.txt", ios::app);
    if (!outFile) {
        cout << "\nError opening file for writing!\n";
        return;
    }
    b.getData();
    b.writeToFile(outFile);
    outFile.close();
    cout << "\nBook record added successfully!\n";
}

void displayBooks() {
    Book b;
    ifstream inFile("library.txt");
    if (!inFile) {
        cout << "\nNo records found!\n";
        return;
    }

    cout << "\n===== BOOK RECORDS =====\n";
    while (b.readFromFile(inFile)) {
        b.showData();
        cout << "-----------------------------\n";
    }

    inFile.close();
}

int main() {
    int choice;
    do {
        cout << "\n===== LIBRARY MANAGEMENT SYSTEM =====";
        cout << "\n1. Add Book";
        cout << "\n2. Display All Books";
        cout << "\n3. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: cout << "\nThank you for using the system.\n"; break;
            default: cout << "\nInvalid choice!\n";
        }
    } while (choice != 3);

    return 0;
}
