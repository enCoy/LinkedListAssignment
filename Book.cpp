/**
    * The class for book objects in the library
*/

#include <iostream>
#include "Book.h"
#include <cstring>
#include <string>
using namespace std;
Book::Book(){
}

/**
    * Constructor for the class
    @param id : ID of a book
    @param title : title of the book
    @param year : year of publishment of the book
    @param status : V represents valid, C represents checked - basically situation of a book in the system
*/
Book::Book(int newId, std::string newTitle, int newYear){
    id = newId;
    title = newTitle;
    year = newYear;
    status = 'V';
    checkedOutID = -1;
}
// Destructor
Book::~Book(){ // delete dynamically allocated array
}

/**
  * @desc gets the variable year
  * @return int year - year of the publish
*/
int Book::getYear(){
    return year;
}

/**
  * @desc gets the variable title of book
  * @return string title - title of the book
*/
std::string Book::getTitle(){
    return title;
}

/**
  * @desc gets the variable ID of book
  * @return int id - ID
*/
int Book::getId(){
    return id;
}

/**
  * @desc gets the status of the book
  * @return string stringToReturn - basically the status of the book whether "checked out" or "valid"
*/
std::string Book::getStatus(){
    std::string stringToReturn;
    if(status == 'V'){
        stringToReturn = "Not checked out";
    }
    else if(status == 'C'){
        stringToReturn = "Checked out by student " + to_string(checkedOutID);
    }
    return stringToReturn;
}
/**
  * @desc changes the status of the book between C and V
*/
void Book::changeStatus(){
    if(status == 'C')
        status = 'V';
    else if(status =='V')
       status = 'C';
}
