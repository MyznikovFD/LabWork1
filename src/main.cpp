#include <iostream>
#include <string>
#include "BMP.h"

int main() {
    const std::string base_path = "images/";
    
    {
        BMP bmp((base_path + "source.bmp").c_str());
        bmp.clockwiseRotate();
        bmp.write((base_path + "RotatedClockwise.bmp").c_str());
    }
    
    {
        BMP bmp((base_path + "source.bmp").c_str());
        bmp.CounterClockwiseRotate();
        bmp.write((base_path + "RotatedCounterClockwise.bmp").c_str());
    }

    {
        BMP bmp((base_path + "RotatedClockwise.bmp").c_str());
        bmp.GaussFiltr(25);  // Используйте нечетный размер ядра
        bmp.write((base_path + "GFiltr.bmp").c_str());
    }

    return 0;
}
