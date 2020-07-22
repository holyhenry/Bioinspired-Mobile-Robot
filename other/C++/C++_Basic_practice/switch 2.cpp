#include<iostream>
using namespace std;

int main(){  
     int day;
     cout << " What day is today?? \n";
     cin >> day;
     switch (day){
          case 6:
               cout << " It is Saturday, have fun and be drunk. :) \n ";
               break;
          case 7:
               cout << " It is Sunday, get your big ass prepared hahaha \n ";
               break;
          default:
               cout << " Sorry, please work hard :(( \n ";
     }
}

// A break can save a lot of execution time because it "ignores" the execution of all the rest of the code in the switch block.

//  The default keyword must be used as the last statement in the switch, and it does not need a break.
