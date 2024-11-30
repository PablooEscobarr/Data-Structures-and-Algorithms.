#include <iostream>
using namespace std;

int main() {
    
    char option;
    float celsius, fahrenheit;

    cout << "Enter temperature(C, F): ";
    cin >> option;
 
    if (option == 'C') {
        cout << "Enter number: ";
        cin >> celsius;
        fahrenheit = (celsius * 9.0) / 5 + 32;
        cout << fahrenheit;

 

    } else {
        cout << "Enter number: ";
        cin >> fahrenheit;
        celsius = (fahrenheit - 32) * 5 / 9;
        cout << celsius;
    


    }



    return 0;



}
