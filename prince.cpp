#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

class Book {
    int bookID;
    string title, author;

public:
    void input() {
        cout << "\nEnter Book ID: ";
        cin >> bookID;
        cin.ignore();
        cout << "Enter Book Title: ";
        getline(cin, title);
        cout << "Enter Author Name: ";
        getline(cin, author);
    }

    void display() const {
        cout << "\nBook ID: " << bookID
             << "\nTitle: " << title
             << "\nAuthor: " << author << endl;
    }

    int getID() const { return bookID; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
};

// Function to add a new book
void addBook() {
    Book book;
    ofstream file("library.txt", ios::app);
    if (!file) {
        cerr << "\nError opening file!\n";
        return;
    }
    book.input();
    file << book.getID() << "|" << book.getTitle() << "|" << book.getAuthor() << "\n";
    file.close();
    cout << "\nBook added successfully!\n";
}

// Function to display all books
void displayBooks() {
    ifstream file("library.txt");
    if (!file) {
        cout << "\nNo books found!\n";
        return;
    }

    cout << "\n======================\n";
    cout << left << setw(10) << "Book ID"
         << setw(30) << "Title"
         << setw(25) << "Author" << "\n";
    cout << "========================\n";

    string line;
    while (getline(file, line)) {
        size_t pos1 = line.find('|');
        size_t pos2 = line.rfind('|');

        if (pos1 != string::npos && pos2 != string::npos) {
            int id = stoi(line.substr(0, pos1));
            string title = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string author = line.substr(pos2 + 1);

            cout << left << setw(10) << id
                 << setw(30) << title
                 << setw(25) << author << "\n";
        }
    }
    cout << "========================\n";
    file.close();
}

// Function to delete a book by ID
void deleteBook() {
    int id;
    cout << "\nEnter Book ID to delete: ";
    cin >> id;

    ifstream in("library.txt");
    ofstream out("temp.txt");
    if (!in) {
        cout << "\nNo records found!\n";
        return;
    }

    bool found = false;
    string line;
    while (getline(in, line)) {
        size_t pos = line.find('|');
        if (pos != string::npos) {
            int currentID = stoi(line.substr(0, pos));
            if (currentID != id)
                out << line << "\n";
            else
                found = true;
        }
    }
    in.close();
    out.close();

    remove("library.txt");
    rename("temp.txt", "library.txt");

    if (found)
        cout << "\nBook deleted successfully!\n";
    else
        cout << "\nBook with ID " << id << " not found!\n";
}

// Function to issue a book
void issueBook() {
    int id;
    string borrower;
    cout << "\nEnter Book ID to issue: ";
    cin >> id;
    cin.ignore();

    ifstream in("library.txt");
    ofstream out("issued_books.txt", ios::app);
    if (!in) {
        cout << "\nNo books found!\n";
        return;
    }

    string line;
    bool found = false;
    while (getline(in, line)) {
        size_t pos1 = line.find('|');
        size_t pos2 = line.rfind('|');

        if (pos1 != string::npos && pos2 != string::npos) {
            int currentID = stoi(line.substr(0, pos1));
            string title = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string author = line.substr(pos2 + 1);

            if (currentID == id) {
                found = true;
                cout << "\nBook Found!\n";
                cout << "Book ID: " << currentID
                     << "\nTitle: " << title
                     << "\nAuthor: " << author
                     << "\nEnter Borrower's Name: ";
                getline(cin, borrower);
                out << currentID << "|" << title << "|" << author << "|" << borrower << "\n";
                cout << "\nBook issued successfully to " << borrower << "!\n";
                break;
            }
        }
    }

    if (!found)
        cout << "\nBook with ID " << id << " not found!\n";

    in.close();
    out.close();
}

// Function to display issued books
void displayIssuedBooks() {
    ifstream file("issued_books.txt");
    if (!file) {
        cout << "\nNo issued books found!\n";
        return;
    }

    cout << "\n======================\n";
    cout << left << setw(10) << "Book ID"
         << setw(25) << "Title"
         << setw(20) << "Author"
         << setw(20) << "Borrower" << "\n";
    cout << "=========================\n";

    string line;
    while (getline(file, line)) {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        size_t pos3 = line.find('|', pos2 + 1);

        if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
            int id = stoi(line.substr(0, pos1));
            string title = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string author = line.substr(pos2 + 1, pos3 - pos2 - 1);
            string borrower = line.substr(pos3 + 1);

            cout << left
                 << setw(10) << id
                 << setw(25) << title
                 << setw(20) << author
                 << setw(20) << borrower << "\n";
        }
    }
    cout << "=========================\n";
    file.close();
}

// Main Menu
int main() {
    int choice;
    do {
        cout << "\n===== LIBRARY MANAGEMENT SYSTEM =====";
        cout << "\n1. Add Book";
        cout << "\n2. Display All Books";
        cout << "\n3. Delete Book";
        cout << "\n4. Issue Book";
        cout << "\n5. Display Issued Books";
        cout << "\n6. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: deleteBook(); break;
            case 4: issueBook(); break;
            case 5: displayIssuedBooks(); break;
            case 6: cout << "\nThank you for using the system.\n"; break;
            default: cout << "\nInvalid choice! Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}