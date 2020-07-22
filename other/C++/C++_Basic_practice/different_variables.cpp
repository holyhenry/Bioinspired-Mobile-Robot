#include<iostream>
using namespace std;

/*
<different types of variables>
int-------integers (whole number), without decimals ex: 123, -123
long------larger integers
double----floating point numbers, with dicimals ex: 20.11, -20.11
float-----more decimal digits than double
char------single characters (surrounded by single quotes), ex: 'a', 'B' 
string----text (surrounded by double quotes), ex: "hello world"
bool------value with two states: true, false
*/

int mynumber = 10948, mynumberer = 12812;
const int mynumber_unchangable = 12923;
long mynumber_too_large = 10949812378;
long sum = mynumber + mynumber_too_large;

double mynumber2 = -12983.52313;
float mynumber3 = -12312.127362918;

char myletter = 'D';
string myword = "hey bitch";

bool myboolean = false;

int main(){
     cout << mynumber << " is an integer " << "\n";
     cout << mynumber_unchangable << " this integer is unchangable" << "\n" ;
     cout << mynumber_too_large << " is long integer " << "\n";
     cout << "sum of mynumber + mynumber_too_large is equal to: " << sum << "\n\n";  

     cout << mynumber2 << " is number with decimals " << "\n\n";

     cout << myletter << " is a letter " << "\n";
     cout << myword << " is a string " << "\n";
     // string length
     cout << "the length of above string is: " << myword.length() << "\n";
     // access string
     cout << "output the first word of this string: " << myword[0] << "\n";
     // change sting characters
     myword[0] = 'P';
     cout << "change the first letter of this string: "<< myword << "\n\n";

     cout << myboolean << " boolean is equal to either 0 or 1"<< "\n";

}