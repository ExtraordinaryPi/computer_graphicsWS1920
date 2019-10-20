//
// Created by christian on 17.10.19.
//

#include <iostream>
#include <limits>
#include "assignment1_1.h"

using namespace std;

double pi = 3.1415;


double circleCalculation() {

    double radius;
    string stringCheck;
    string checkSum;
    bool falseInput = true;

    cout << "Please enter a valid radius to calculate the circumflence of a circle." << endl;

    while (falseInput) {
        cin >> stringCheck;
        falseInput = false;
        try {
            radius = std::stod(stringCheck);
        }
        catch (std::invalid_argument &) {
            cout << "Invalid Entry\nOnly numbers from 0-9 and dots. Please enter a new one" << endl;
            falseInput = true;
        }

    }
    return radius * 2 * pi;
}