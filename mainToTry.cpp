/**
  * This basic program is studied as a lab homework to understand linked lists
  * by avoiding any memory leak
  * @author Cem Okan Yaldız - Bilkent University EEE student
*/



#include <iostream>
#include "LibrarySystem.h"
#include <string>
using namespace std;

int main(){
    //LibrarySystem ls;
    //ls.showAllBooks();
    //ls.deleteBook(1610);
    //ls.addBook(1110, "naber", 1196);
    //ls.deleteBook(1110);
    //ls.addBook(1410, "iyidir", 1964);
    //ls.addBook(1610, "iyi deðildir", 1967);
    //ls.addBook(1610, "iyidir", 1964);
    //ls.showAllBooks();
    //cout << ls.getBookListSize() << endl;
    //ls.deleteBook(1610);
    //ls.showAllBooks();
    //cout << ls.getBookListSize() << endl;
    //ls.deleteBook(1110);
    //ls.showAllBooks();
    //cout << ls.getBookListSize() << endl;
    //ls.deleteBook(1110);
    //ls.showAllBooks();
    //cout << ls.getBookListSize() << endl;
    //ls.showBook(1410);
    //ls.addStudent(1524,"Cem Okan Yaldiz");
    //ls.addStudent(1624,"Nazım Hikmet");
    //ls.addStudent(1724,"Nazım Hikmet");
    //ls.addStudent(1724,"Nazım Hikmet");
    //ls.addStudent(1624,"Nazım Hikmet");
    //ls.addStudent(1624,"Nazım Hikmet");
    //ls.addStudent(1524,"Kazım Hikmet");
    //ls.addStudent(1624,"Nazım Hikmet");
    //ls.deleteStudent(1624);
    //ls.deleteStudent(1624);
    //ls.showStudent(1524);
    //ls.checkoutBook(1410,1524);
    //ls.showStudent(1524);
    //cout << "************" << endl;
    //ls.showAllBooks();
    //ls.returnBook(1610);
   // ls.returnBook(1410);
    //ls.showBook(1410);
    //ls.showStudent(1524);
    //cout << "************" << endl;
    //ls.showAllBooks();
//
LibrarySystem LS;
   LS.addBook( 1000, "Machine Learning", 2017 );
LS.addBook( 1200, "Data Mining", 2015 );
LS.addBook( 1300, "Problem S. with C++", 2015 );
LS.addBook( 1400, "C++ How to Program", 2016 );
LS.addBook( 1200, "Data Mining", 2015 );
LS.deleteBook( 1300 );
LS.deleteBook( 2000 );
LS.addBook( 1500, "Pattern Recognition", 2000 );
cout << endl;
LS.addStudent( 21900000, "Furkan Huseyin" );
LS.addStudent( 21900011, "Aynur Dayanik" );
LS.addStudent( 21900011, "Cigdem Gunduz Demir" );
LS.addStudent( 21900020, "Gokhan Akcay" );
LS.addStudent( 21900001, "Cihan Akcay" );
LS.addStudent( 21900005, "Gozde Nur Gunesli" );
LS.deleteStudent( 21900011 );
LS.deleteStudent( 21900050 );
cout << endl;
LS.checkoutBook( 1200, 21900000 );
LS.checkoutBook( 1400, 21900020 );
LS.checkoutBook( 2050, 21900011 );
LS.checkoutBook( 1000, 21900444 );
LS.checkoutBook( 1500, 21900000 );
LS.checkoutBook( 1400, 21900001 );
cout << endl;
LS.showStudent( 21900000 );
cout << endl;
LS.showStudent( 21900005 );
cout << endl;
LS.showStudent( 21900011 );
cout << endl;
LS.showBook( 1000 );
LS.showBook( 1200 );
cout << endl;
LS.showAllBooks();
cout << endl;
LS.returnBook( 1200 );
LS.returnBook( 1000 );
cout << endl;
LS.checkoutBook( 1200, 21900020 );
LS.checkoutBook( 1000, 21900000 );
cout << endl;
LS.showAllBooks();
cout << endl;
LS.deleteStudent( 21900020 );
cout << endl;
LS.deleteBook( 1000 );
cout << endl;
LS.showStudent( 21900000 );
cout << endl;
LS.showAllBooks();
return 0;

//    LS.addBook( 1968, "Ama olmaz ki", 2017);
//    LS.addBook( 2012, "Olur Olur", 2017);
//    LS.addBook( 2013, "Olur asdf", 2017);
//     cout << endl;
//    LS.addStudent(21601586,"Cem Okan YAldiz");
//    LS.checkoutBook(1968, 21601586);
//    LS.checkoutBook(2012,21601586);
//    cout << endl;
//    LS.showStudent(21601586);
//    cout << endl;
//    LS.returnBook(1968);
//    LS.showStudent(21601586);
//    LS.checkoutBook(1968, 21601586);
//    LS.checkoutBook(2013, 21601586);
//    LS.showStudent(21601586);
    //Note: Delete book 1000 de book delete edilmemiş, delete koduna iyice bak;
}
