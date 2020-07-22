#include<iostream>
using namespace std;

/** C++ is an object-oriented programming language.

Everything in C++ is associated with classes and objects, along with its attributes and methods. 

For example: in real life, a car is an object. The car has attributes, such as weight and color, 

and methods, such as drive and brake. */

class car{                   // The class
     public:                 // Access specifier
          string model;      // Attribute (string variable)
          string color;      // Attribute
          int year;          // Attribute (int variable)

          // Define a function inside the class
          void dream_car(){  // Method (function)
               cout << "This is my dream car!!\n\n" ;
          }
          // Declare a function inside the class
          void not_dream_car();

          // Define a function with the name same with the class inside
          car (string brand){ // Constructor
               cout << "This is the of class of car (constructor) " ;
               cout << brand << " \n";
          }

          // // Declare a function with the name same with the class inside
          // car (string brand);
};

// Define a function outside the class
void car::not_dream_car(){
     cout << "This is not my dream car!!\n\n";
}

// // Define a constructor outside the class
// car::car (string brand){ // Constructor
//           cout << "This is the of class of car (constructor) " ;
//           cout << brand << " \n";
// }

int main(){
     car object1("BMW");         // Object of car
     object1.model = "X6";       // Call the object
     object1.color = "White";
     object1.year = 2015;

     cout << object1.model << " " << object1.color << " " << object1.year << endl;
     object1.not_dream_car();     // Call the method

     car object2("Toyota");
     object2.model = "Supra";
     object2.color = "Red";
     object2.year = 2019;

     cout << object2.model << " " << object2.color << " " << object2.year << endl;
     object2.dream_car();

     car object3("Nissan");
     object3.model = "370Z";
     object3.color = "Black";
     object3.year = 2016;

     cout << object3.model << " " << object3.color << " " << object3.year << endl;
     object3.dream_car();


}