#include "BMP.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>


void BMP::clockwiseRotate()
{
    int new_width = bmp_info_header.height;
    int new_height = bmp_info_header.width;
    
    std::vector<uint8_t> new_data(new_width * new_height * 3);

    for (int y = 0; y < bmp_info_header.height; ++y)
    {
        for (int x = 0; x < bmp_info_header.width; ++x)
        {
            int old_index = (y * bmp_info_header.width + x) * 3;

            
            int new_x, new_y;
            new_x = y;
            new_y = new_height - 1 - x;
            
            
            int new_index = (new_y * new_width + new_x) * 3;

            new_data[new_index] = data[old_index];
            new_data[new_index + 1] = data[old_index + 1];
            new_data[new_index + 2] = data[old_index + 2];
        }
    }

    bmp_info_header.width = new_width;
    bmp_info_header.height = new_height;
    data.swap(new_data);
};

void BMP::CounterClockwiseRotate()
{
    int new_width = bmp_info_header.height;
    int new_height = bmp_info_header.width;
    
    std::vector<uint8_t> new_data(new_width * new_height * 3);

    for (int y = 0; y < bmp_info_header.height; ++y)
    {
        for (int x = 0; x < bmp_info_header.width; ++x)
        {
            int old_index = (y * bmp_info_header.width + x) * 3;


            int new_x, new_y;
            new_x = new_width - 1 - y;
            new_y = x;
            
            
            int new_index = (new_y * new_width + new_x) * 3;

            new_data[new_index] = data[old_index];
            new_data[new_index + 1] = data[old_index + 1];
            new_data[new_index + 2] = data[old_index + 2];
        }
    }

    bmp_info_header.width = new_width;
    bmp_info_header.height = new_height;
    data.swap(new_data);
}
