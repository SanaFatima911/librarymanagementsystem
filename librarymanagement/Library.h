#pragma once
#include "Book.h"
#include <string>
#include <fstream>
using namespace std;
class Library {
private:
	Book* collectionOfBooks[100];
	int numberOfBooks;

public:
	Library() {
		numberOfBooks = 0;
	}

	void addBook(Book book) {
		if (numberOfBooks < 100) {
			collectionOfBooks[numberOfBooks] = new Book(book);
			numberOfBooks++;
		} else {
			cout<< "Library is full."<<endl;
		}
	}

	void removeBook(string isbn) {
		for (int i = 0; i < numberOfBooks; i++) {
			if (collectionOfBooks[i]->ISBN == isbn) {
				delete collectionOfBooks[i];
				collectionOfBooks[i] = collectionOfBooks[numberOfBooks - 1];
				numberOfBooks--;
				return;
			}
		}
		cout<< "Book not found." <<endl;
	}

	Book* findBookByISBN(string isbn) {
		for (int i = 0; i < numberOfBooks; i++) {
			if (collectionOfBooks[i]->ISBN == isbn) {
				return collectionOfBooks[i];
			}
		}
		return 0;
	}

	void displayAllBooks() {
		for (int i = 0; i < numberOfBooks; i++) {
			cout<<collectionOfBooks[i]->title<< " by "<< collectionOfBooks[i]->author<< " (ISBN: "<< collectionOfBooks[i]->ISBN << ")"<<endl;
		}
	}

	void displayAvailableBooks() {
		for (int i = 0; i < numberOfBooks; i++) {
			if (collectionOfBooks[i]->status) {
				cout<<collectionOfBooks[i]->title<< " by "<<collectionOfBooks[i]->author<<" (ISBN: " << collectionOfBooks[i]->ISBN<< ")"<<endl;
			}
		}
	}
	void WriteToFile(const string& output) {
		ofstream ofile("output.txt");
		if (ofile.is_open()) {
			ofile<<"Number of books- " << numberOfBooks << endl;
			for (int i = 0; i < numberOfBooks; i++) {
				ofile<<"Title- " << collectionOfBooks[i]->title << endl;
				ofile<<"Author- " << collectionOfBooks[i]->author << endl;
				ofile<<"ISBN- " << collectionOfBooks[i]->ISBN << endl;
				ofile<<"Status- " << collectionOfBooks[i]->status << endl;
				ofile<<"Borrower- "<< collectionOfBooks[i]->borrower << endl;
			}
			ofile.close();
			cout << "Library saved to " << output << endl;
		} else {
			cout << "Unable to open file for saving." << endl;
		}
	}
	void ReadBookFromFile(const string& input)
	{
		ifstream ifile("input.txt");
		if (ifile.is_open()) {
			ifile >> numberOfBooks;
			ifile.ignore(); // Ignore newline after number of books
			for (int i = 0; i < numberOfBooks; i++) {
				string title, author, isbn, borrower;
				bool status;
				getline(ifile, title);
				getline(ifile, author);
				getline(ifile, isbn);
				ifile >> status;
				ifile.ignore();
				getline(ifile, borrower);

				Book* book = new Book(title, author, isbn);
				book->status = status;
				book->borrower = borrower;

				collectionOfBooks[i] = book;
			}
			ifile.close();
			cout << "Library loaded from " << input << endl;
		} else {
			cout << "Unable to open file for loading." << endl;
		}
	}
};
