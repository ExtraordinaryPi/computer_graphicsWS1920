#define _USE_MATH_DEFINES

#include<iostream>
#include<cmath>

int main(){

    float radius;

    while (true){
        std::cout << "Radius of circle: ";

        std::cin >> radius;

        if (radius >= 0 && std::cin)
            break;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "incorrect input.\n";
    }

    std::cout << "Area: " << radius * radius * M_PI << "\nCircumference: " << 2 * radius * M_PI << "\n";

    return 0;
}