#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

#define PI 3.1415926535
#define XRES 720
#define YRES 720

int sin_255(int index) {
    return abs((int)(sin(index * PI / 180) * 255));
}

int collatz_length_255(int n) {
    int counter = 1;
    if (!n) {
        return 0;
    }
    while (n != 1) {
        if (n % 2) {
            n = 3 * n + 1;
        }
        else {
            n = n / 2;
        }
        counter = counter + 1 % 255;
    }
    return counter;
}

int triangular_number_255(int n) {
    return (n * (n + 1) / 2) % 255;
}

int main() {
    ofstream pic("./cg1.ppm");

    pic << "P3 " << XRES << " " << YRES << " " << 255 << "\n";

    for (int i = 0 ; i < XRES ; i++) {
        for (int j = 0 ; j < YRES ; j++) {
            pic << sin_255(i + j - j * j) << " ";
            pic << collatz_length_255(i + j) << " ";
            pic << triangular_number_255(i * i + j) << " ";
            //cout << tan_255(i + j) << '\n';
        }
    }

    pic.close();

    return 0;
}
