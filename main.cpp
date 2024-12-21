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

    {
        BMP bmp("source.bmp");
        bmp.clockwiseRotate();
        bmp.GaussFiltr(1, 9);
        bmp.write("GFiltr.bmp");
        
    }


};
