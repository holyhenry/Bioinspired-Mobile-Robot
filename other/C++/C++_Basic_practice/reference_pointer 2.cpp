#include<iostream>
// #include <string> This may not be necessary
using namespace std;

/** And why is it useful to know the memory address?

References and Pointers are important in C++, because they give you the ability to manipulate the data in the computer's memory - which can reduce the code and improve the perfomance.

These two features are one of the things that make C++ stand out from other programming langues, like Python and Java. */

// "&" reference operator
// "*" dereference operator

int main(){
     string school = "UCSD";
     string &institution = school; // reference variable
     string* ptr = &school; // pointer variable, holds the address of school's address

     // we can use either the variable name school or the reference name institution to refer to the school variable:
     cout << "school:       " << school << endl;
     cout << "institution:  " << institution << endl;

     // output the address of school variable
     cout << endl << "Showing the address" << endl;
     cout << "&school:      " << &school << endl;
     cout << "&institution: " << &institution << endl;
     cout << "ptr:          " << ptr << endl; 

     // output the value of school variable
     cout << "*ptr:         " << *ptr << endl;


     double latte = 3.94;
     double &coffee = latte;

     cout << endl;
     cout << "latte:        " << latte << endl;
     cout << "coffee:       " << coffee << endl;
     
}

