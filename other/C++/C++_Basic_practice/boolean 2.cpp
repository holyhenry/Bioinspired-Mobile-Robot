#include<iostream>
using namespace std;

int main() {
     int a = 5;
     int b = 10;
     cout << "please inpout a & b: \n";
     cin >> a >> b;
     cout << "1 = true \n0 = false\n";
     cout << "comparison between a = " << a << " & b = " << b << "\n";
     cout << "a is larger than b ---> " << (a > b) << "\n";
     cout << "a is larger equal than b ---> " << (a >= b) << "\n";
     cout << "a is equal to b ---> " << (a == b) << "\n";
     cout << "a is smaller equal than b ---> " << (a <= b) << "\n";
     cout << "a is smaller than b ---> " << (a < b) << "\n";
     return 0;
}
