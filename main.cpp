#include <iostream>
#include <string>
#include "BMP.h"


int main()
{
    BMP bmp("source.bmp");
    bmp.write("source_copy.bmp");

};
