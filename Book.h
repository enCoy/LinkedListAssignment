#ifndef BOOK_H_INCLUDED
#define BOOK_H_INCLUDED
#include <cstring>
#include <string>


class Book {
public:
Book();
Book(int id, std::string title, int year);
~Book();
int getYear();
int getId();
std::string getTitle();
char status; //C if checked out, V if valid
void changeStatus();
int checkedOutID; //-1 if not checked out, student id if checked out
std::string getStatus();

private:
std::string title;
int id;
int year;
};

#endif // BOOK_H_INCLUDED
