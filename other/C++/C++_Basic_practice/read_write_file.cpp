#include<iostream>
#include<fstream>
using namespace std;

int main(){
     // Get the test file ready *****************************************************
     // fstream test_file("hangover_namelist.txt"); // Write to or read form a text file
     // ofstream test_file("hangover_namelist.txt"); // Get the test file ready to be written
     ifstream test_file("hangover_namelist.txt"); // Get the test file ready to be read

     while(true){
          string a;
          string namelist; 

          cout << "please enter r or w: \n";
          cin >> a;

          if ( a == "r" ){
               cout << "Starting to read form the test file... \n";
               // Use a while loop together with the getline() function to read the file line by line
               while(getline (test_file,namelist)){
                    cout << namelist << endl;
               }
               test_file.close();
               break;
          }
          // if ( a == "w" ){
          //      cout << "Starting to write to the test file... \n";
          //      test_file << "Henry, Allen, Jacky, Tomnmy, Bryan :)))\n"; 
          //      test_file << "Alice, Shirley, Irene, Yodi, Monica, Tina, Joy, Chloe, Kay\n";
          //      test_file.close();
          //      break;
          // }
          else {
               cout << "please make sure entering r or w... \n";
          }
     }
}