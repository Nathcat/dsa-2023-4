#include <iostream>

int main() {
    std::cout << "\n\n\033[3;95mLab2 tests\033[0m" << std::endl;
    system("./Lab2/build/DSALab2");

    std::cout << "\n\n\033[3;95mLab3 tests\033[0m" << std::endl;
    system("./Lab3/build/DSALab3");

    std::cout << "\n\n\033[3;95mLab4 tests\033[0m" << std::endl;
    system("./Lab4/build/DSALab4");

    std::cout << "\n\n\033[3;95mLab5 tests\033[0m" << std::endl;
    system("./Lab5/build/DSALab5");

    std::cout << "\n\n\033[3;95mLab6 tests\033[0m" << std::endl;
    system("./Lab6/build/DSALab6");
}