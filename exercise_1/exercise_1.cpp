#include <iostream>
#include "assignment1_1.h"
#include "assignment1_2.h"
#include <vector>
#include <string>

using namespace std;

bool assignment = true;
string input;

int exercise_1() {
    while (assignment) {
        cout << "Which assignment you want to check? \n1 Assignment 1.1: Circle Calculation \n2 Assignment 1.2: Scene Manager Class\nto exit press anything else."<< endl;
        cin >> input;
        if(input == "1"){
            cout << "The radius is "<< circleCalculation() << endl;
        }
        if(input == "2"){
            assignment2();
        }


        if (!(input == "1" || input == "2")) {
            assignment = false;
        }
    }

    return 0;
}