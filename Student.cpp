/**
    Class for student objects
*/

#include <iostream>
#include "Student.h"
#include <cstring>
#include <string>
using namespace std;
Student::Student(){
}
/**
  * @desc constructor
  * @param int newId - ID of the student
  * @param string newName - name of the student
  * @return int id - ID
*/
Student::Student(int newId, std::string newName){
    id = newId;
    name = newName;
    BookListOfStudents booklistStu; //list object for individual booklists of student
}
// destructor that will delete all the books of a particular student
Student::~Student(){ // delete dynamically allocated array
    deleteAllBooks();
}

/**
  * @desc adds a book to the list of the student
  * @param int bookId - ID of the book
  * @param string name - name of the book
  * @param int year - year of publish
*/
void Student::addBook(const int bookId, const std::string name, const int year){
    Book newBook(bookId, name, year); // construct the new book object with given parameters
    BookListOfStudents* newPtr = new BookListOfStudents(); // pointer for the book
    newPtr -> book = newBook; //assign the book to the pointer
    if(booklistStuSize == 0)//if empty use head directly
    {
        headBook = newPtr;
        tailBook = headBook;//note that tail book is fixed, only the point it points changed
        booklistStuSize++;
    }
    else{ //if size is other than 0
        bool found = false; // will be used to check if the book already exists
        BookListOfStudents* curPtr = headBook; // current pointer is head, traverse until find tail
        do{
            if(curPtr->book.getId() == bookId){ // if the book is already found basically
                found = true;
                std::string stringToThrow ="Book " + to_string(bookId) + " already exists";
                delete newPtr; // avoid memory leak, if book already exists delete the one you created
                cout << stringToThrow << endl;
            }
            if(booklistStuSize > 1 && !found){ // traverse
                curPtr = curPtr -> next;
            }
        }while((curPtr  != headBook) && !found); //until reaching headbook

        if(!found){ // ifyou cannot find, add the book - note that we are adding from the beginning of the circular list
            newPtr->next = headBook;
            headBook = newPtr;
            tailBook ->next = headBook;
            booklistStuSize++;
        }
    }
}
/**
  * @desc deletes the book given as parameter from the list of the student
  * @param bookID - Id of the book that will be deleted from the list
  * @return int id - ID
*/
void Student::deleteBook( const int bookId ){
    bool found = false; // same logic with adding a book
    if(booklistStuSize >1){
    BookListOfStudents* prevBook =  headBook; // prev book will help us
    BookListOfStudents* curPtr = headBook->next;;

    // start the loop from head book until head book
    //following code segment is for the first book
    if(curPtr ->book.getId() == bookId){ //if found
        prevBook ->next = curPtr ->next;
        curPtr -> next = NULL;
        if(booklistStuSize == 2)
          tailBook = prevBook;
        delete curPtr; // delete the ptr object to avoid leak
        curPtr = NULL;
        found = true;
        booklistStuSize--;
    }
    else{ // if the first book is not the book we look for search until end up in first book too
        prevBook = prevBook -> next; //update pointers
        curPtr = curPtr -> next;

        while(curPtr != headBook->next && found == false){

            if(curPtr ->book.getId() == bookId){// if found

                if(curPtr == headBook){ //if head is removed
                 tailBook ->next = curPtr ->next;
                 headBook = curPtr->next;
                 curPtr -> next = NULL;
                 delete curPtr; //burasý yeni
                 curPtr = NULL;
                 found = true;
                 booklistStuSize--;
                }
                else{ //if another element
                    prevBook ->next = curPtr ->next;
                    curPtr -> next = NULL;
                    delete curPtr;
                    curPtr = NULL;
                    found = true;
                    booklistStuSize--;
                }
            }
            else{
                prevBook = prevBook -> next;
                curPtr = curPtr -> next;
            }
        }
      }
    }
    else if(booklistStuSize == 1){ // if there is just one book in the list
        BookListOfStudents* curPtr = headBook;
        if(curPtr ->book.getId() == bookId){
            curPtr -> next = NULL;
            delete curPtr; //burasý da yeni
            curPtr = NULL;
            found = true;
            booklistStuSize--;
            headBook = NULL;
        }
        else
            found = false;
    }
    else{
        headBook = NULL;
    }
}

void Student::deleteAllBooks(){
    BookListOfStudents* curPtr = headBook;
    if(headBook != NULL){//if list is not empty
        while(curPtr != tailBook){
            BookListOfStudents* tempPtr = curPtr;
            curPtr = curPtr ->next;
            deleteBook(tempPtr->book.getId());
            delete tempPtr;
            headBook = curPtr;
        }
        deleteBook(tailBook ->book.getId());
        //delete tailBook;
        tailBook = NULL;
        headBook = NULL;
    }

}

/**
  * @desc prints information of the books of a student
*/
void Student::showAllBooks(){
    if(booklistStuSize == 0){
        cout << "No books to show" << endl;
    }
    else{
        cout << "Book id    " << "Book Name         " << "Year      "<<endl;
        BookListOfStudents* curPtr = headBook;
        cout << curPtr->book.getId() << "       " << curPtr->book.getTitle() <<"     " <<curPtr ->book.getYear() <<endl;
        if(booklistStuSize >1 )
            curPtr = curPtr -> next;
        int i = 0;
        while(i < booklistStuSize-1){
            cout << curPtr->book.getId() << "       " << curPtr->book.getTitle() <<"            " <<curPtr ->book.getYear() << endl;
            curPtr = curPtr -> next;
            i++;
    }

  }
}
/**
  * @desc gets the booklist size
  * @return int bookListStuSize - size of the booklist of a student
*/
int Student::getBookListStuSize(){
    return booklistStuSize;
}

/**
  * @desc gets the name of the student
  * @return string name
*/
std::string Student::getName(){
    return name;
}

/**
  * @desc gets the Id of the student
  * @return int id - ID
*/
int Student::getId(){
    return id;
}
