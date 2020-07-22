#include<iostream>
using namespace std;

/** C++ provides some pre-defined functions, such as main(), which is used to execute code. 

But you can also create your own functions to perform certain actions. */

/** void means that the function does not have a return value. 

You will learn more about return values later in the next chapter */

// int main(){
//      hangoverboys();
//      return 0;
// }

// void hangover(string name, int age); // Declaration: the function's name, return type, and parameters (if any)
// string hangover_couples(string boy_name, string girl_name);
// int hangover_birthday(int month, int day);

void hangover(string name, int age){ 
     cout << name << ", age: " << age << endl; // Definition: the body of the function (code to be executed)
}

/** When a parameter is passed to the function, it is called an argument. 

So, from the example above: string name is a parameter, while Henry, Jacky and Allen are arguments. */

string hangover_couples(string boy_name, string girl_name){
     // cout << "test\n";
     return boy_name + " " + girl_name;
}

int hangover_birthday(int month, int day){
     cout << "His/Her birthday is: " << month << "/" << day << endl;
     return 0;
}