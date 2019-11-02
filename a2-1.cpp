#include <iostream>

#define SQUARE(a) a * a

int main(int, char**) {

    for (size_t x = 1; x < 11; x++)
    {
        std::cout << "f(" << x << ") = " << SQUARE(x) << std::endl;
        std::cout << "g(" << x << ") = " << SQUARE(1 - x) << std::endl;
        std::cout << "h(" << x << ") = " << 1 / SQUARE(x) << std::endl;
        std::cout << std::endl;
    }
    
    return 0;
}
