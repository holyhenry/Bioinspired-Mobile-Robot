// Include cmath library
#include<cmath>
#include<iostream>
using namespace std;

int main(){
     // Max and min
     int a = 5, b = 10;
     cout << "Maximum of " << a << " and " << b << " is " << max(a,b) << "\n";
     cout << "minimum of " << a << " and " << b << " is " << min(a,b) << "\n\n";
     
     int c = 64;
     float d = 5.56;
     // cout << "Please input number here: " << "\n";
     // cin >> c;
     cout << "Following function need cmath library" << "\n";
     cout << "square root of " << c << " is " << sqrt(c) << "\n";
     cout << "round up " << d << " would be " << round(d) << "\n";
     cout << "logarithm of " << c << " would be " << log(c) << "\n";
     return 0;
}
