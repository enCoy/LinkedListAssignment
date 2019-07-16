#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED
#include "Book.h"
#include <string>
#include <cstring>


class BookListOfStudents{
public:
    BookListOfStudents* next;
    Book book;
};

class Student{
public:
Student();
Student(int id, std::string name);
~Student();
BookListOfStudents* booklistStu;
int getId();
std::string getName();
void addBook(const int bookId, const std::string name, const int year);
void deleteBook( const int bookId );
void deleteAllBooks();
void showAllBooks();
int booklistStuSize = 0;
int getBookListStuSize();
BookListOfStudents* headBook = NULL;
// note that tail and head are connected to each other, tail does not mean that the list is not circular
BookListOfStudents* tailBook =NULL;


private:
std::string name;
int id;
};

#endif // STUDENT_H_INCLUDED
