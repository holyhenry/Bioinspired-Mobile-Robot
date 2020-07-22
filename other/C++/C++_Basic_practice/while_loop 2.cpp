#include<iostream>
using namespace std;

int main() {
     int i = 0;
     while (i < 5){
          cout << i << "\n";
          i++;
     }
     // show 01234
     
     i = i-1;

     // do something before while
     do {
          i--;
          cout << i << "\n";
     }
     while (i > 0);
     // show 3210
}