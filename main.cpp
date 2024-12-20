#include <iostream>
#include <string>
#include "BMP.h"


int main()
{
     
    {
        BMP bmp("source.bmp");
        bmp.clockwiseRotate();
        bmp.write("RotatedClockwise.bmp");
    }
     
    {
        BMP bmp("source.bmp");
        bmp.CounterClockwiseRotate();
        bmp.write("RotatedCounterClockwise.bmp");
    }
};
