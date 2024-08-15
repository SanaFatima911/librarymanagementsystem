#include <iostream>
#include "Library.h"
#include "User.h"

using namespace std;

int main() {
	Library library;

    int choice;
	while (true) {
		cout<< "Library Management System" << endl;
		cout<< "1. Add new book" << endl;
		cout<< "2. Check out book" << endl;
		cout<< "3. Return book or check-in " << endl;
		cout<< "4. Remove book" << endl;
		cout<< "5. Search for book" << endl;
		cout<< "6. Display all books" << endl;
		cout<< "7. Display available books" << endl;
		cout<< "8. Exit" << endl;

		cout<< "Enter Your Choice " << endl;
        while (!(cin >> choice) || choice < 1 || choice > 8) {
            cout << "Invalid choice! Please re-enter: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

		switch (choice) {
		case 1: {
			string title, author, isbn;
			cout << "Enter book title: ";
			cin.ignore(); // Clear the newline character from the buffer
			getline(cin, title);
			cout << "Enter book author: ";
			getline(cin, author);
			cout << "Enter book ISBN: ";
			getline(cin, isbn);

			Book book(title, author, isbn);
			library.addBook(book);
            library.WriteToFile("output.txt");
			break;
		}
		case 2: {
			string isbn,name;
			cout << "Enter book ISBN to check out: ";
			cin >> isbn;
			cout << "Enter your name: ";
			cin.ignore(); // Clear the new line character from the buffer
			getline(cin, name);
			// Created a new User object with the entered name
			User currentUser(name, 0); 

			Book* book = library.findBookByISBN(isbn);
			if (book) {
				currentUser.borrowBook(book);
				 currentUser.WriteUserToFile("user.txt"); // Save the user 
			} else {
				cout << "Book not found." << endl;
			}
			break;
		}
		case 3: {
			string isbn,name;
			cout << "Enter book ISBN to return: ";
			cin >> isbn;
			 cout << "Enter your name: ";
            cin.ignore();
            getline(cin, name);

        	User currentUser(name, 0);
			Book* book = library.findBookByISBN(isbn);
			if (book) {
				currentUser.returnBook(book);
				currentUser.WriteUserToFile("user.txt"); // Save the user 
			} else {
				cout << "Book not found." << endl;
			}
			break;
		}
		case 4: {
			string isbn;
			cout << "Enter book ISBN to remove: ";
			cin >> isbn;

			library.removeBook(isbn);
			break;
		}
		case 5: {
			string isbn;
			cout << "Enter book ISBN to search: ";
			cin >> isbn;

			Book* book = library.findBookByISBN(isbn);
			if (book) {
				cout << "Found: " << book->title << " by " << book->author << " (ISBN: " << book->ISBN << ")" << endl;
			} else {
				cout << "Book not found." << endl;
			}
			break;
		}
		case 6:
			library.displayAllBooks();
			break;
		case 7:
			library.displayAvailableBooks();
			break;
		case 8:
			// Exiting the program
			return 0;
		default:
			cout << "Invalid choice, try again." << endl;
		}
	}
}

