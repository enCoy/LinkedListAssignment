#include <iostream>
#include <cstring>
#include "LibrarySystem.h"
#include <string>
#include <cstddef>
#include "Book.h"
#include "Student.h"

using namespace std;

//default constructor
LibrarySystem::LibrarySystem(){}

//destructor deletes all the students and the books of the library
LibrarySystem::~LibrarySystem()
{
    deleteStudentList(headStudent, studentlistSize);
    deleteBookList(headBook, booklistSize);
}

/**
  * @desc adds a book to the library
  * @param int bookId - ID of the new book
  * @param string name - name of the new book
  * @param int year - publish year of the new book
*/
void LibrarySystem::addBook(const int bookId, const std::string name, const int year)
{
    Book newBook(bookId, name, year); // construct the new book
    BookList* newPtr = new BookList();
    newPtr -> book = newBook; //put the book into the pointer object
    if(booklistSize == 0)//if empty use head directly
    {
        headBook = newPtr;
        tailBook = headBook;//note that tail book is fixed, only the point it points changed
        booklistSize++;
        cout << "Book " << newBook.getId() << " has been added" <<endl;
    }
    else  //if size is other than 0
    {
        bool found = false;
        BookList* curPtr = headBook;// current pointer is head, traverse until find tail
        do
        {
            if(curPtr->book.getId() == bookId)
            {
                found = true;
                std::string stringToThrow ="Book " + to_string(bookId) + " already exists";
                cout << stringToThrow << endl;
                delete newPtr;
            }
            if(booklistSize != 1)
                curPtr = curPtr -> next;
        }
        while((curPtr  != headBook) && !found);
        if(!found)
        {
            newPtr->next = headBook;
            headBook = newPtr;
            tailBook ->next = headBook;
            booklistSize++;
            cout << "Book " << newBook.getId() << " has been added" <<endl;
        }
    }
}

/**
  * @desc adds a new student to the library
  * @param int studentId - ıd of the new student
  * @param string name - name of the newstudent
*/
void LibrarySystem::addStudent(const int studentId, const std::string name)
{
    Student newStudent(studentId, name); // construct the new student
    StudentList* newPtr = new StudentList();
    newPtr -> student = newStudent;
    if(studentlistSize == 0)//if empty use head directly
    {
        headStudent = newPtr;
        tailStudent = newPtr; //note that tail book is fixed, only the point it points changed
        studentlistSize++;
        cout << "Student " << newStudent.getId() << " has been added" <<endl;
    }
    else  //if size is other than 0
    {
        bool found = false;
        StudentList* curPtr = tailStudent;
        // current pointer is head, traverse until find tail
        do
        {
            if(curPtr->student.getId() == studentId)
            {
                found = true;
                std::string stringToThrow ="Student " + to_string(studentId) + " already exists";
                cout << stringToThrow << endl;
                delete newPtr;
            }
            if(studentlistSize != 1)
                curPtr = curPtr -> prev;
        }
        while((curPtr != tailStudent));

        if(!found)
        {
            newPtr->next = headStudent;
            headStudent -> prev = newPtr; //doubly linked
            headStudent = newPtr;
            tailStudent ->next = headStudent;
            headStudent ->prev = tailStudent;
            studentlistSize++;
            cout << "Student " << newStudent.getId() << " has been added" <<endl;
        }
    }
}

/**
  * @desc deletes the book from the library system - generally the same logic with deleting
  * a book or student but they are some helper methods and other issues so that it looks a little bit complicated
  * @param int bookId - the book that will be deleted
*/
void LibrarySystem::deleteBook( const int bookId )
{
    bool found = false;
    if(booklistSize != 0)
    {
        BookList* prevBook;
        BookList* curPtr;

        if(booklistSize > 1)
        {
            prevBook = headBook;
            curPtr = headBook->next; // start the loop from head book until head book
            if(curPtr ->book.getId() == bookId) //for the first book
            {

                if(curPtr->book.status == 'C') //if checked out remove from students list and books list
                {
                    Student* theStudent;
                    bool isStudentValid = findStudent(curPtr->book.checkedOutID, theStudent,studentlistSize);
                    returnBook(bookId);
                    if(curPtr == tailBook)
                        tailBook = headBook;
                    prevBook->next = curPtr->next;
                    curPtr->next= NULL;
                    delete curPtr;
                    curPtr =NULL;
                    found = true;
                    booklistSize--;
                }
                else  //if book is not checked out
                {
                    cout << "Book " << bookId << " has not been checked out"<< endl;
                    if(curPtr == tailBook)
                        tailBook = headBook;
                    prevBook ->next = curPtr ->next;
                    curPtr -> next = NULL;
                    delete curPtr;
                    curPtr = NULL;
                    found = true;
                    booklistSize--;
                }
            }
            else  // if the first book is not the book we look for search until end up in first book too
            {
                prevBook = prevBook -> next;
                curPtr = curPtr -> next;
                while(curPtr != headBook->next && found == false)
                {
                    if(curPtr ->book.getId() == bookId)
                    {
                        if(curPtr == headBook)  //if head is removed
                        {
                            if(curPtr->book.status == 'C') //if checked out remove from students list
                            {
                                Student* theStudent;
                                bool isStudentValid = findStudent(curPtr->book.checkedOutID, theStudent,studentlistSize);
                                returnBook(bookId);
                                tailBook->next = curPtr->next;
                                headBook = curPtr->next;
                                curPtr->next= NULL;
                                delete curPtr;
                                curPtr =NULL;
                                found = true;
                                booklistSize--;
                            }
                            else
                            {
                                tailBook ->next = curPtr ->next;
                                headBook = curPtr->next;
                                curPtr -> next = NULL;
                                delete curPtr;
                                curPtr = NULL;
                                found = true;
                                booklistSize--;
                            }
                        }

                        else if(curPtr == tailBook)
                        {
                            if(curPtr->book.status == 'C') //if checked out remove from students list
                            {

                                Student* theStudent;
                                bool isStudentValid = findStudent(curPtr->book.checkedOutID, theStudent,studentlistSize);
                                //theStudent->deleteBook(bookId);
                                returnBook(bookId);
                                prevBook ->next = headBook;
                                curPtr -> next = NULL;
                                tailBook = prevBook;
                                delete curPtr;
                                curPtr = NULL;
                                found = true;
                                booklistSize--;

                            }
                            else
                            {
                                prevBook ->next = headBook;
                                curPtr -> next = NULL;
                                delete curPtr;
                                curPtr = NULL;
                                found = true;
                                booklistSize--;
                                tailBook = prevBook;
                            }
                        }
                        else  //if another element
                        {
                            if(curPtr->book.status == 'C') //if checked out remove from students list
                            {
                                Student* theStudent;
                                bool isStudentValid = findStudent(curPtr->book.checkedOutID, theStudent,studentlistSize);
                                //theStudent->deleteBook(bookId);
                                returnBook(bookId);
                                prevBook ->next = curPtr ->next;
                                curPtr -> next = NULL;
                                delete curPtr;
                                curPtr = NULL;
                                booklistSize--;
                                found = true;
                            }
                            else
                            {
                                prevBook ->next = curPtr ->next;
                                curPtr -> next = NULL;
                                delete curPtr;
                                curPtr = NULL;
                                found = true;
                                booklistSize--;
                            }
                        }
                    }
                    else
                    {
                        prevBook = prevBook -> next;
                        curPtr = curPtr -> next;
                    }
                }
            }
        }

        if(booklistSize == 1)
        {
            BookList* curPtr = headBook;
            if(curPtr ->book.getId() == bookId)
            {
                curPtr -> next = NULL;
                delete curPtr;
                curPtr = NULL;
                found = true;
                booklistSize--;
                headBook = NULL;
            }
        }
    }
    if(found == false)
        cout << "Book " << bookId << " does not exist" <<endl;
    else
        cout << "Book " << bookId << " has been deleted" <<endl;
}

/**
  * @desc deletes a student - like book - same logic
  * @param studentId - student to be deleted
*/
void LibrarySystem::deleteStudent( const int studentId )
{
    bool found = false;
    if(studentlistSize != 0)
    {
        if(studentlistSize > 1)
        {
            StudentList* curPtr = headStudent->next;
            if(curPtr ->student.getId() == studentId)
            {
                if(curPtr ->student.getBookListStuSize() != 0){ //if student has books checked out, return them to library

                    //return all
                    int numberOfIterations = curPtr ->student.getBookListStuSize();
                    BookListOfStudents* currPtr = curPtr->student.headBook;
                    int i = 0;
                    while(i < numberOfIterations){
                        int idNum = currPtr->book.getId();
                        returnBook(idNum);
                        i++;
                        currPtr = currPtr->next;
                    }
                }

                curPtr ->prev-> next = curPtr ->next;
                curPtr ->next->prev = curPtr -> prev;
                curPtr ->next = NULL;
                curPtr ->prev = NULL;
                delete curPtr;
                curPtr = NULL;
                found = true;
                studentlistSize--;
            }
            else  // if the first student is not the student we look for search until end up in first student too
            {

                curPtr = curPtr -> next;
                while(curPtr != headStudent->next && found == false)
                {
                    if(curPtr ->student.getId() == studentId)
                    {

                        if(curPtr == headStudent)  //if head is removed
                        {
                            int numberOfIterations = curPtr ->student.getBookListStuSize();
                            BookListOfStudents* currPtr = curPtr->student.headBook;
                            int i = 0;

                            while(i < numberOfIterations){
                            int idNum = currPtr->book.getId();
                            returnBook(idNum);
                            i++;
                            currPtr = currPtr->next;
                            }

                            curPtr ->prev-> next = curPtr ->next;
                            curPtr ->next->prev = curPtr -> prev;
                            headStudent = curPtr ->next;
                            curPtr -> next = NULL;
                            curPtr -> prev = NULL;
                            delete curPtr;
                            curPtr = NULL;
                            found = true;
                            studentlistSize--;

                        }
                        else if(curPtr == tailStudent)
                        {
                            int numberOfIterations = curPtr ->student.getBookListStuSize();
                            BookListOfStudents* currPtr = curPtr->student.headBook;
                            int i = 0;
                            while(i < numberOfIterations){
                            int idNum = currPtr->book.getId();
                            returnBook(idNum);
                            i++;
                            currPtr = currPtr->next;
                            }

                            curPtr ->prev-> next = curPtr ->next;
                            curPtr ->next->prev = curPtr -> prev;
                            tailStudent = curPtr ->next;
                            curPtr -> next = NULL;
                            curPtr -> prev = NULL;
                            delete curPtr;
                            curPtr = NULL;
                            found = true;
                            studentlistSize--;

                        }
                        else  //if another element
                        {

                            int numberOfIterations = curPtr ->student.getBookListStuSize();
                            BookListOfStudents* currPtr = curPtr->student.headBook;
                            int i = 0;
                            while(i < numberOfIterations){ //buradan cýkamýyor

                            int idNum = currPtr->book.getId();
                            currPtr = currPtr->next;
                            returnBook(idNum); //bura cok sýkýntý
                            i++;
                            }

                            curPtr ->prev-> next = curPtr ->next;
                            curPtr ->next->prev = curPtr -> prev;
                            curPtr -> next = NULL;
                            curPtr -> prev = NULL;
                            delete curPtr;
                            curPtr = NULL;
                            found = true;
                            studentlistSize--;
                        }
                    }
                    else
                    {
                        curPtr = curPtr -> next;
                    }
                }
            }
        }
        else if(studentlistSize == 1)
        {
            StudentList* curPtr = headStudent;
            if(curPtr ->student.getId() == studentId)
            {
                curPtr ->next = NULL;
                curPtr ->prev = NULL;
                delete curPtr;
                curPtr = NULL;
                found = true;
                studentlistSize--;
            }
        }
    }
    if(found == false)
        cout << "Student " << studentId << " does not exist" <<endl;
    else
        cout << "Student " << studentId << " has been deleted" <<endl;
}



/**
  * @desc shows all the books in the system
*/
void LibrarySystem::showAllBooks()
{
    if(booklistSize == 0)
    {
        cout << "No books to show" << endl;
    }
    else
    {
        cout << "Book id    " << "Book Name         " << "Year      "<< "   Status"<<endl; //status ekle
        BookList* curPtr = headBook;
        cout << curPtr->book.getId() << "       " << curPtr->book.getTitle() <<"     " <<curPtr ->book.getYear() << "        "<<  curPtr -> book.getStatus()<<endl;
        if(booklistSize > 1){
        curPtr = curPtr -> next;
        while(curPtr != headBook)
        {
            cout << curPtr->book.getId() << "       " << curPtr->book.getTitle() <<"            " <<curPtr ->book.getYear() << "        "<<  curPtr -> book.getStatus()<< endl;
            curPtr = curPtr -> next;
        }
       }
    }
}

/**
  * @desc with this method a student checks out a particular book
  * @param int bookId - book to be checked out
  * @param int studentId - student that checks out
*/
void LibrarySystem::checkoutBook( const int bookId, const int studentId )
{
    Book *theBook; //the book who has the related id
    Student *theStudent; // the student who has the related id
    bool control = false;
    bool isBookValid = findBook(bookId, theBook,booklistSize);
    bool isStudentValid = findStudent(studentId, theStudent,studentlistSize);
    if(!isBookValid)
    {
        std::string stringToThrow ="Book " + to_string(bookId) + " does not exist for checkout";
        cout << stringToThrow << endl;
        control = true;
    }
    else if(!isStudentValid)
    {
        std::string stringToThrow ="Student " + to_string(studentId) + " does not exist for checkout";
        cout << stringToThrow << endl;
        control = true;
    }
    if(!control)  // if book is valid, check if checkedout or not
    {
        if(theBook->status == 'V')
        {
            theBook->changeStatus();
            theBook->checkedOutID = studentId;
            theStudent->addBook(theBook->getId(),theBook->getTitle(),theBook->getYear()); //add the book to the student
            cout << "Book " << to_string(bookId) << " has been checked out by student " << to_string(studentId) << endl;
        }
        else if(theBook->status == 'C')
        {
            std::string stringToThrow2 ="Book " + to_string(bookId) + " has been already checked out by another student";
            cout << stringToThrow2 << endl;
        }
    }
}

/**
  * @desc with this method a book is returned to the library
  * @param int bookId - book the be returned
*/
void LibrarySystem::returnBook( const int bookId )
{
    bool control = false;
    Book *theBook; //the book which has the related id
    bool isBookValid = findBook(bookId, theBook,booklistSize);
    if(!isBookValid)
    {
        std::string stringToThrow ="Book " + to_string(bookId) + " does not exist for returning";
        cout << stringToThrow << endl;
        control = true;
    }
    else if(theBook->checkedOutID == -1) //if the book is not checked out
    {
        std::string stringToThrow2 = "Book " + to_string(bookId) + " has not been checked out";
        cout << stringToThrow2 << endl;
        control =true;
    }
    if(!control) //other wise carry out the operation
    {
        theBook->changeStatus();
        int studentID = theBook->checkedOutID;
        theBook->checkedOutID = -1;
        Student* studentToDeleteTheBook;
        findStudent(studentID, studentToDeleteTheBook,studentlistSize);
        studentToDeleteTheBook->deleteBook(bookId);
        std::string stringToThrow3 = "Book " +to_string(bookId) + " has been returned";
        cout << stringToThrow3 << endl;
    }
}
/**
  * @desc shows detailed information about a particular book
  * @param int bookId - book to be displayed
*/
void LibrarySystem::showBook( const int bookId )
{
    bool control = false;
    Book *theBook; //the book who has the related id
    bool isBookValid = findBook(bookId, theBook,booklistSize);
    if(!isBookValid)
    {
        std::string stringToThrow ="Book " + to_string(bookId) + " does not exist";
        cout << stringToThrow << endl;
        control = true;
    }
    if(!control)  //if book exist
    {
        cout <<  theBook ->getId() << "     " << theBook ->getTitle() << "          " << theBook ->getYear() << "    ";
        if(theBook ->status == 'V')
        {
            cout <<  " Not checked out." << endl;
        }
        else if(theBook ->status == 'C')
        {
            Student *whoChecked;
            findStudent(theBook->checkedOutID, whoChecked, studentlistSize); //find the student
            cout << "Checked out by " << whoChecked->getId() << endl;
        }
    }

}
/**
  * @desc shows detailed information about a particular student
  * @return int studentId - student to be displayed
*/
void LibrarySystem::showStudent( const int studentId )
{
    bool control = false;
    Student *theStudent; //the book who has the related id

    bool isStudentValid = findStudent(studentId, theStudent,studentlistSize);
    if(!isStudentValid)
    {
        std::string stringToThrow ="Student " + to_string(studentId) + " does not exist";
        cout << stringToThrow << endl;
        control = true;
        //delete theStudent;
    }
    if(!control)  //if STUDENT exist
    {
        cout << "Student ID: " << theStudent ->getId() << "   ";
        cout << "Student name: " << theStudent->getName() << endl;
        if(theStudent ->booklistStuSize == 0)
        {
            cout << "Student " << to_string(studentId) << " has no books" << endl;
        }
        else if(theStudent ->booklistStuSize != 0)  //if student has checkedout books
        {
            Student *whoChecked;
            findStudent(studentId, whoChecked, studentlistSize); //find the student
            cout <<  "Student " << studentId << " has checked out the following books:" << endl;
            theStudent->showAllBooks();
        }
    }

}

/**
 below this line there will be helper functions to solve some problems
*/

/**
  * @desc finds a student if exist
  * @param studentId - student to search for
  * @param Student*& studentToReturn - pointer for the student that is found
  * because we need to change something upon returning we used *&
  * @param int sizeStudent - how many students are there
  * @return bool - true if student is found
*/
bool LibrarySystem::findStudent(const int studentId, Student *&studentToReturn, int sizeStudent)
{
    if(sizeStudent == 0)
    {
        return false;
    }
    else
    {
        StudentList* curPtr = headStudent;
        if(curPtr -> student.getId() == studentId)  //if head is the wanted student
        {
            studentToReturn = &(curPtr ->student);
            return true;
        }

        else
        {
            if(sizeStudent > 1){
            curPtr = curPtr -> next;
            while(curPtr != headStudent)
            {
                if(curPtr -> student.getId() == studentId)
                {
                    studentToReturn = &(curPtr ->student);
                    return true;
                }
                curPtr = curPtr -> next;
            }
            }
        }
    }
    return false;
}

/**
  * @desc finds a book if exist
  * @param bookId - book to search for
  * @param Book*& bookToReturn - pointer for the book that is found
  * because we need to change something upon returning we used *&
  * @param int sizeBook - how many books are there
  * @return bool - true if book is found
*/
bool LibrarySystem::findBook (const int bookId, Book *&bookToReturn, int sizeBook)
{
    if(sizeBook == 0)
    {
        return false;
    }
    else
    {
        BookList* curPtr = headBook;
        if(curPtr -> book.getId() == bookId)  //if head is the wanted student
        {
            bookToReturn = &(curPtr ->book);
            return true;
        }

        else
        {
            curPtr = curPtr -> next;
            while(curPtr != headBook)
            {
                if(curPtr -> book.getId() == bookId)
                {
                    bookToReturn = &(curPtr ->book);
                    return true;
                }
                curPtr = curPtr -> next;
            }
        }
    }
    return false;
}

/**
  * @desc deletes the whole list
  * @param BookList*& headbook2 - beginning from head, delete books
  * @param int &booklistSize - booklistsize to be updated
*/
void LibrarySystem::deleteBookList(BookList *&headBook2,int &booklistSize){
    if(headBook != NULL){
        BookList* curPtr = headBook2;
        if(booklistSize == 1){
            curPtr ->next = NULL;
            delete curPtr;
            headBook = NULL;
            tailBook = NULL;
            booklistSize--;
        }

        if(booklistSize > 1){
        while(curPtr != tailBook){
            BookList* tempPtr = curPtr;
            curPtr = curPtr ->next;
            tempPtr ->next = NULL;
            delete tempPtr;
            tempPtr = NULL;
            booklistSize--;
        }
        delete tailBook;
        booklistSize--;
        tailBook = NULL;
        headBook = NULL;
        }
    }
}

/**
  * @desc deletes the whole list of students
  * @param StudentList*& headstudent2 - beginning from head, delete students
  * @param int &studentlistSize - studentlistsize to be updated
*/
void LibrarySystem::deleteStudentList(StudentList *&headStudent2,int &studentlistSize){
    if(headStudent != NULL){
        StudentList* curPtr = headStudent2;
        while(curPtr  != tailStudent){
            StudentList* tempPtr = curPtr;
            curPtr = curPtr ->next;
            tempPtr->student.deleteAllBooks();
            deleteStudent2(tempPtr->student.getId());
        }
        tailStudent->student.deleteAllBooks();
        deleteStudent2(tailStudent ->student.getId());
        studentlistSize--;
        headStudent = NULL;
    }
}
/**
  * @desc the only difference of this method from the one above this will not print some additional lines
  * there is no other difference and actually this is a copy paste
  * @param int studentId - student to be deleted
*/
void LibrarySystem::deleteStudent2( const int studentId )
{
    bool found = false;
    if(studentlistSize != 0)
    {

        if(studentlistSize > 1)
        {

            StudentList* curPtr = headStudent->next;
            if(curPtr ->student.getId() == studentId)
            {
                if(curPtr ->student.getBookListStuSize() != 0){ //if student has books checked out, return them to library

                    //return all
                    int numberOfIterations = curPtr ->student.getBookListStuSize();
                    BookListOfStudents* currPtr = curPtr->student.headBook;
                    int i = 0;
                    while(i < numberOfIterations){
                        int idNum = currPtr->book.getId();
                        returnBook(idNum);
                        i++;
                        currPtr = currPtr->next;
                    }
                }

                curPtr ->prev-> next = curPtr ->next;
                curPtr ->next->prev = curPtr -> prev;
                curPtr ->next = NULL;
                curPtr ->prev = NULL;
                delete curPtr;
                curPtr = NULL;
                found = true;
                studentlistSize--;
            }
            else  // if the first student is not the student we look for search until end up in first student too
            {

                curPtr = curPtr -> next;
                while(curPtr != headStudent->next && found == false)
                {
                    if(curPtr ->student.getId() == studentId)
                    {

                        if(curPtr == headStudent)  //if head is removed
                        {
                            int numberOfIterations = curPtr ->student.getBookListStuSize();
                            BookListOfStudents* currPtr = curPtr->student.headBook;
                            int i = 0;

                            while(i < numberOfIterations){
                            int idNum = currPtr->book.getId();
                            returnBook(idNum);
                            i++;
                            currPtr = currPtr->next;
                            }

                            curPtr ->prev-> next = curPtr ->next;
                            curPtr ->next->prev = curPtr -> prev;
                            headStudent = curPtr ->next;
                            curPtr -> next = NULL;
                            curPtr -> prev = NULL;
                            delete curPtr;
                            curPtr = NULL;
                            found = true;
                            studentlistSize--;

                        }
                        else if(curPtr == tailStudent)
                        {
                            int numberOfIterations = curPtr ->student.getBookListStuSize();
                            BookListOfStudents* currPtr = curPtr->student.headBook;
                            int i = 0;
                            while(i < numberOfIterations){
                            int idNum = currPtr->book.getId();
                            returnBook(idNum);
                            i++;
                            currPtr = currPtr->next;
                            }

                            curPtr ->prev-> next = curPtr ->next;
                            curPtr ->next->prev = curPtr -> prev;
                            tailStudent = curPtr ->next;
                            curPtr -> next = NULL;
                            curPtr -> prev = NULL;
                            delete curPtr;
                            curPtr = NULL;
                            found = true;
                            studentlistSize--;

                        }
                        else  //if another element
                        {

                            int numberOfIterations = curPtr ->student.getBookListStuSize();
                            BookListOfStudents* currPtr = curPtr->student.headBook;
                            int i = 0;
                            while(i < numberOfIterations){ //buradan cýkamýyor

                            int idNum = currPtr->book.getId();
                            currPtr = currPtr->next;
                            returnBook(idNum); //bura cok sýkýntý
                            i++;
                            }

                            curPtr ->prev-> next = curPtr ->next;
                            curPtr ->next->prev = curPtr -> prev;
                            curPtr -> next = NULL;
                            curPtr -> prev = NULL;
                            delete curPtr;
                            curPtr = NULL;
                            found = true;
                            studentlistSize--;
                        }
                    }
                    else
                    {
                        curPtr = curPtr -> next;
                    }
                }
            }
        }
        else if(studentlistSize == 1)
        {
            StudentList* curPtr = headStudent;
            if(curPtr ->student.getId() == studentId)
            {
                curPtr ->next = NULL;
                curPtr ->prev = NULL;
                delete curPtr;
                curPtr = NULL;
                found = true;
                studentlistSize--;
            }
        }
    }
}


/**
  * @desc gets booklist size
  * @return int booklistSize - return size of the booklist
*/
int LibrarySystem::getBookListSize()
{
    return booklistSize;
}
/**
  * @desc gets studentlist size
  * @return int studentlistSize - return size of the studentlist
*/
int LibrarySystem::getStudentListSize()
{
    return studentlistSize;
}


