#include<iostream>
using namespace std;

/**You have already seen the break statement used in an earlier chapter of this tutorial. It was used to "jump out" of a switch statement.

The break statement can also be used to jump out of a loop.

This example jumps out of the loop when i is equal to 5: */

 
/**The continue statement breaks one iteration (in the loop), if a specified condition occurs, and continues with the next iteration in the loop.

This example skips the value of 5: */

int main(){
     for (int i = 0 ; i < 10 ; i++){
          if (i == 5){
          break;
          }
     cout << i << "\n";
     }
     // showing 01234
     cout << "\n";

     for (int j = 0 ; j < 10 ; j++){
          if (j == 5){
          continue;     
          } 
     cout << j << "\n";
     }
     // showing 012346789
}