#include "BMP.h"

#include <fstream>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <string>


void read(const char *fname)
{
    std::ifstream inp{ fname, std::ios_base::binary };
    if (inp)
    {
        inp.read((char*)&file_header, sizeof(file_header));
        if(file_header.file_type != 0x4D42)
        {
            std::cout"Error! Unrecognized file format.";
        }
        inp.read((char*)&bmp_info_header, sizeof(bmp_info_header));


        if(bmp_info_header.bit_count == 32)
        {

            if(bmp_info_header.size >= (sizeof(BMPInfoHeader) + sizeof(BMPColorHeader)))
            {
                inp.read((char*)&bmp_color_header, sizeof(bmp_color_header));
                // Check if the pixel data is stored as BGRA and if the color space type is sRGB
                check_color_header(bmp_color_header);
            }
            else
            {
                std::cout << "Error! The file \"" << fname << "\" does not seem to contain bit mask information\n";
            }
        }

        //pixel data location
        inp.seekg(file_header.offset_data, inp.beg);

        // Adjust the header fields for output.
        // Some editors will put extra info in the image file, we only save the headers and the data.
        if(bmp_info_header.bit_count == 32)
        {
            bmp_info_header.size = sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
            file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
        }
        else
        {
            bmp_info_header.size = sizeof(BMPInfoHeader00);
            file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
        }
        file_header.file_size = file_header.offset_data;

        if (bmp_info_header.height < 0)
        {
            std::cout <<"The program can treat only BMP images with the origin in the bottom left corner!";
        }

        data.resize(bmp_info_header.width * bmp_info_header.height * bmp_info_header.bit_count / 8);

        // check if we need to take into account row padding
        if (bmp_info_header.width % 4 == 0)
        {
            inp.read((char*)data.data(), data.size());
            file_header.file_size += static_cast<uint32_t>(data.size());
        }
        else
        {
            row_stride = bmp_info_header.width * bmp_info_header.bit_count / 8;
            uint32_t new_stride = make_stride_aligned(4);
            std::vector<uint8_t> padding_row(new_stride - row_stride);

            for (int y = 0; y < bmp_info_header.height; ++y)
            {
                inp.read((char*)(data.data() + row_stride * y), row_stride);
                inp.read((char*)padding_row.data(), padding_row.size());
            }
            file_header.file_size += static_cast<uint32_t>(data.size()) + bmp_info_header.height * static_cast<uint32_t>(padding_row.size());
        }
    }
    else
    {
        std::cout("Unable to open the input image file.";
    }


    BMP::BMP(int32_t width, int32_t height, bool has_alpha = true)
    {
        if (width <= 0 || height <= 0)
        {
            std::cout <<"The image width and height must be positive numbers.";
        }
        bmp_info_header.width = width;
        bmp_info_header.height = height;
        if (has_alpha)
        {
            bmp_info_header.size = sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
            file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);

            bmp_info_header.bit_count = 32;
            bmp_info_header.compression = 3;

            row_stride = width * 4;
            data.resize(row_stride * height);
            file_header.file_size = file_header.offset_data + data.size();
        }
        else
        {
            bmp_info_header.size = sizeof(BMPInfoHeader);
            file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);

            bmp_info_header.bit_count = 24;
            bmp_info_header.compression = 0;

            row_stride = width * 3;
            data.resize(row_stride * height);

            uint32_t new_stride = make_stride_aligned(4);
            file_header.file_size = file_header.offset_data + static_cast<uint32_t>(data.size()) + bmp_info_header.height * (new_stride - row_stride);
        }
    };



    void check_color_header(BMPColorHeader &bmp_color_header)
    {
        BMPColorHeader expected_color_header;
        if(expected_color_header.red_mask != bmp_color_header.red_mask ||
                expected_color_header.blue_mask != bmp_color_header.blue_mask ||
                expected_color_header.green_mask != bmp_color_header.green_mask ||
                expected_color_header.alpha_mask != bmp_color_header.alpha_mask)
        {
            std::cout << "Unexpected color mask format! The program expects the pixel data to be in the BGRA format";
        }
        if(expected_color_header.color_space_type != bmp_color_header.color_space_type)
        {
            std::cout << "Unexpected color space type! The program expects sRGB values";
        }
    }
};
