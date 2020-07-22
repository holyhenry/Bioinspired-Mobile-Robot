#include<iostream>
using namespace std;

int main(){

     int a, b;
     cout << "plese enter a\n";
     cin >> a;
     cout << "please enter b\n";
     cin >> b;

     // method 1******************************************************************************
     // if (a > b){
     //      cout << "a is larger than b\n";
     // }
     // else if (a <= b){
     //      cout << "a is smaller than or equal to b\n";
     // }

     // method 2******************************************************************************
     string result = (a > b) ? "a is larger than b\n" : "a is smaller than or equal to b\n" ;
     cout << result;

}
