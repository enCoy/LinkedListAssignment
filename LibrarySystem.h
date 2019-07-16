#ifndef LIBRARYSYSTEM_H_INCLUDED
#define LIBRARYSYSTEM_H_INCLUDED
#include "Book.h"
#include "Student.h"
#include <string>



class StudentList{
public:
    StudentList* prev;
    StudentList* next;
    Student student;
};
class BookList{
public:
    BookList* next;
    Book book;
};


class LibrarySystem {
public:
LibrarySystem();
~LibrarySystem();
void addBook( const int bookId, const std::string name, const int year );
void deleteBook( const int bookId );
void addStudent( const int studentId, const std::string name );
void deleteStudent( const int studentId );
void checkoutBook( const int bookId, const int studentId );
void returnBook( const int bookId );
void showAllBooks();
void showBook( const int bookId );
void showStudent( const int studentId );

//some required additional assets
//note that this list holds all the books and their information added before-delete does not affect this list
BookList* headBook = NULL;
// note that tail and head are connected to each other, tail does not mean that the list is not circular
BookList* tailBook = NULL;
int booklistSize = 0;
int getBookListSize();
StudentList* headStudent =NULL;
StudentList* tailStudent =NULL;
int studentlistSize = 0;
int getStudentListSize();
//helper methods for the assignment
bool findStudent(const int studentId, Student *&studentToReturn, int sizeStudent);
bool findBook (const int bookId, Book *&bookToReturn, int sizeBook);
void deleteBookList(BookList *&headBook, int &booklistSize);
void deleteStudentList(StudentList *&headStudent, int &studentlistSize);
void deleteStudent2( const int studentId ); //just the version delete student that does not print anything
};



#endif // LIBRARYSYSTEM_H_INCLUDED
