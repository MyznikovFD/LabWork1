#include "BMP.h"

#include <fstream>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <string>


void BMP::write(const char *fname)
{
    std::ofstream of{ fname, std::ios_base::binary };
    if (of)
    {
        if (bmp_info_header.bit_count == 32)
        {
            write_headers_and_data(of);
        }
        else if (bmp_info_header.bit_count == 24)
        {
            if (bmp_info_header.width % 4 == 0)
            {
                write_headers_and_data(of);
            }
            else
            {
                uint32_t new_stride = make_stride_aligned(4);
                std::vector<uint8_t> padding_row(new_stride - row_stride);

                write_headers(of);

                for (int y = 0; y < bmp_info_header.height; ++y)
                {
                    of.write((const char*)(data.data() + row_stride * y), row_stride);
                    of.write((const char*)padding_row.data(), padding_row.size());
                }
            }
        }
        else
        {
            std::cout <<"The program can treat only 24 or 32 bits per pixel BMP files";
        }
    }
    else
    {
        std::cout << "Unable to open the output image file.";
    }
}


void write_headers(std::ofstream &of)
{
    of.write((const char*)&file_header, sizeof(file_header));
    of.write((const char*)&bmp_info_header, sizeof(bmp_info_header));
    if(bmp_info_header.bit_count == 32)
    {
        of.write((const char*)&bmp_color_header, sizeof(bmp_color_header));
    }
}

void write_headers_and_data(std::ofstream &of)
{
    write_headers(of);
    of.write((const char*)data.data(), data.size());
}

// Add 1 to the row_stride until it is divisible with align_stride
uint32_t make_stride_aligned(uint32_t align_stride)
{
    uint32_t new_stride = row_stride;
    while (new_stride % align_stride != 0)
    {
        new_stride++;
    }
    return new_stride;
}

