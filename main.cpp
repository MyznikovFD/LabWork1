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
        //parametr must not be odd
        //if its nessecary to make blur stronger, you may make perameter bigger
        bmp.GaussFiltr(8);
        bmp.write("GFiltr.bmp");
        
    }


};
