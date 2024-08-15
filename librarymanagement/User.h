#include <fstream>
#include "Book.h"
#include <string>
using namespace std;
class User {
private:
    string name;
    int libraryCardNumber;
    Book* borrowedBooks[10];
    int listOfBorrowedBooks;
    static int cardNumberCounter;
public:
    User(string n, int cardNumber) : name(n), libraryCardNumber(++cardNumberCounter), listOfBorrowedBooks(0) {}

    void borrowBook(Book* book) {
        if (book->status) {
            book->checkOut(name);
            borrowedBooks[listOfBorrowedBooks] = book;
            listOfBorrowedBooks++;
            
        } else {
            cout<< "Book is already checked out."<< endl;
        }
    }
    int getlibraryCardNumber(){
        return libraryCardNumber;
    }

    void returnBook(Book* book) {
        if (book->borrower == name) {
            book->checkIn();
            for (int i = 0; i < listOfBorrowedBooks; i++) {
                if (borrowedBooks[i] == book) {
                    borrowedBooks[i] = borrowedBooks[listOfBorrowedBooks - 1];
                    listOfBorrowedBooks--;
                    return;
                }
            }
        } else {
            cout<< "You didn't borrow this book." << endl;
        }
    }
    void WriteUserToFile(const string& user) {
        ofstream ofile("user.txt", ios::app); // Append mode
        if (ofile.is_open()) {
            ofile<<"User name " << name << endl;
            ofile<<" LibraryCardNumber" << libraryCardNumber << endl;
            ofile<<"List " << listOfBorrowedBooks << endl;
            for (int i = 0; i < listOfBorrowedBooks; i++) {
                ofile<<"ISBN of borrowed Books"<< borrowedBooks[i]->ISBN << endl;
            }
            ofile.close();
            cout << "User " << name << " saved to " << user << endl;
        } else {
            cout << "Unable to open file for saving user." << endl;
        }
    }

    void ReadUserFromFile(const string& userinput) {
        ifstream ifile("userinput.txt");
        if (ifile.is_open()) {
            getline(ifile, name);
            ifile >> libraryCardNumber;
            ifile >> listOfBorrowedBooks;
            ifile.ignore(); // Ignore newline after number of books
            for (int i = 0; i < listOfBorrowedBooks; i++) {
                string isbn;
                getline(ifile, isbn);
                borrowedBooks[i] = 0; // Initialize to null or lookup the book from library
            }
            ifile.close();
            cout << "User " << name << " loaded from " << userinput << endl;
        } else {
            cout << "Unable to open file for loading user." << endl;
        }
    }
};
int User::cardNumberCounter =4400;
