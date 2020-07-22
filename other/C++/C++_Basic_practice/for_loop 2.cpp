#include<iostream>
using namespace std;

// When you know exactly how many times you want to loop through a block of code, use the for loop instead of a while loop:

int main(){
     for (int i = 0; i < 5 ; i++){
          cout << i << "\n";
     }
     // show 01234
     for (int j = 3 ; j >= 0 ; j--){
          cout << j << "\n";
     }
     // show 3210
}