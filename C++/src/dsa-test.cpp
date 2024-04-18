#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    const char* exec[] = {
        "start ./Lab2/build/DSALab2.exe",
        "start ./Lab3/build/DSALab3.exe",
        "start ./Lab4/build/DSALab4.exe",
        "start ./Lab5/build/DSALab5.exe",
        "start ./Lab6/build/DSALab6.exe",
    };
#else
    const char* exec[] = {
        "./Lab2/build/DSALab2",
        "./Lab3/build/DSALab3",
        "./Lab4/build/DSALab4",
        "./Lab5/build/DSALab5",
        "./Lab6/build/DSALab6",
    };
#endif

#include <iostream>

int main() {
    for (int i = 0; i < 6; i++) {
        std::cout << "\n\n\033[3;95mLab" << i << " tests\033[0m" << std::endl;
        std::cout << exec[i] << std::endl;
        system(exec[i]);
    }
}