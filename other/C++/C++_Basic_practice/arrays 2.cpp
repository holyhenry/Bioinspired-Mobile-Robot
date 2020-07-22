#include<iostream>
#include<array>
using namespace std;

/**Arrays are used to store multiple values in a single variable, instead of declaring separate variables for each value.

To declare an array, define the variable type, specify the name of the array followed by square brackets and specify the number 

of elements it should store: */

// Array indexes start with 0: [0] is the first element. [1] is the second element, etc.

array<int,2> weekend = {6,7}; // This is an globle array
array<int,100> globle_zero_initialized; // This is an globle array with all zero initialized

int main(){

     array<int,20> local_array; // Local array is not initialized with zeros

     // Declare arrays (easy one, no need to include <array>) ******************************
     string hangovers[14] = {"Henry","Allen","Jacky","Tommy","Bryan","Alice","Irene","Yodi","Tina","Monica","Kay","Chloe","Joy","Shirley"};
     int weekday[5] = {1,2,3,4,5};

     // Print out specific array member 
     cout << hangovers[12] << "\n";
     cout << weekday << "\n";

     // For loop print out whole array
     for(int i=0 ; i <= 12 ; i++){
          cout << hangovers[i] << " ";
     }

     // Declare arrays using different way (std::array) ************************************
     array<string,5> hangover_plus = {"Vincent","Christine"};

     // For loop print out whole array
     for(int j=0 ; j <= 5 ; j++){
          cout << hangover_plus[j] << " ";
     }

     // For loop print out whole array
     for(auto x:hangover_plus) cout << " " << x;

     // Print out the size of the array
     cout << endl << "size of hangover_plus: " << hangover_plus.size() << endl;

      //returns the array size in bytes
     cout << "sizeof(hangover_plus): " << sizeof(hangover_plus) << endl;

     // Assign some value into array using for loop
     cout << "local_array: ";
     for(int k=0 ; k <= local_array.size() ; k++){
          local_array[k] = k;
          cout << local_array[k] << " ";
     } 
}