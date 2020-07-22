#include<iostream>
#include<array>
#include"/Users/mac/Desktop/Mobile_robot/C++_Basic_practice/functions.cpp"
using namespace std;

int main(){
     cout << "hangover:\n";
     hangover("Henry",24); hangover_birthday(11,26);
     hangover("Allen",25); hangover_birthday(10,2);
     hangover("Jacky",25); hangover_birthday(1,31);
     hangover("Tommy",26);
     hangover("Bryan",23);
     hangover("Alice",23); hangover_birthday(7,12);
     hangover("Shirley",23); hangover_birthday(10,6);
     hangover("Yodii",22); hangover_birthday(10,14);
     hangover("Irene",19); hangover_birthday(10,27);
     hangover("Tina",20); hangover_birthday(12,7);
     hangover("Chloe",22);
     hangover("Joy",24); hangover_birthday(6,15);
     hangover("Kay",21); 
     hangover("Monica",23);


     array<string,5> couple;
     cout << "\nhangover couples:\n";
     couple[0] = hangover_couples("Jacky","Shirley");
     couple[1] = hangover_couples("Allen","Alice");
     for (int k=0 ; k < couple.size() ; k++){
          cout << k+1 << endl;
          cout << couple[k] << endl;
     }

     return 0;
}