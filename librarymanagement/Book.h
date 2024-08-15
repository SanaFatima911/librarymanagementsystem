#pragma once
#include <iostream>
#include <string>
using namespace std;

class Book {
public:
    string title, author, ISBN;
    bool status;
    string borrower;

    Book(string t, string a, string i)
    {
         title=t;
         author=a;
         ISBN=i; 
         status=true;
         borrower="";
    }

    void checkIn() {
        status = true;
        borrower = "";
    }

    void checkOut(string user) {
        if (status) {
            status = false;
            borrower = user;
            cout<<"book is checked out by "<<user<<endl;
        } else {
            cout << "Book is already checked out." << endl;
        }
    }
};
