#include "BMP.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

void BMP::GaussFiltr(float kernelSize)
{
    float sigma = (bmp_info_header.width + bmp_info_header.height - 2 * kernelSize)/4;
    
    
    std::vector<std::vector<float>> ratio(kernelSize, std::vector<float>(kernelSize));
    double sum = 0.0;
    

    for (int x = 0; x < kernelSize; x++)
    {
        for (int y = 0; y < kernelSize; y++)
        {
            int mutX = x - kernelSize / 2;
            int mutY = y - kernelSize / 2;
        
            float GaussFun = (1 / (2 * M_PI * pow(sigma, 2))) * std::exp(-( pow(mutX, 2) + pow(mutY, 2)) / (2 * pow(sigma, 2)));
            ratio[x][y]= GaussFun;
            sum += GaussFun;
        
        }
    };
    for (int x = 0; x < kernelSize; x++)
    {
        for (int y = 0; y < kernelSize; y++)
        {
            ratio[x][y] /= sum;
        }
    }
    std::vector<uint8_t> new_data(data.size());

    for (int i = kernelSize / 2; i < bmp_info_header.width - kernelSize / 2; i++)
    {
        for (int j = kernelSize / 2; j < bmp_info_header.height - kernelSize / 2; j++)
        {
            float redSum = 0, greenSum = 0, blueSum = 0;
            for (int k = 0; k < kernelSize; k++)
            {
                for (int l = 0; l < kernelSize; l++)
                {
                    int pixelIndex = ((j + k - kernelSize / 2) * bmp_info_header.width + (i + k - kernelSize / 2)) * 3;
                    redSum += data[pixelIndex] * ratio[k][l];
                    greenSum += data[pixelIndex + 1] * ratio[k][l];
                    blueSum += data[pixelIndex + 2] * ratio[k][l];
                }
            };
            int newIndex = (j * bmp_info_header.width + i) * 3;
            new_data[newIndex] = std::min(255, std::max(0, static_cast<int>(redSum)));
            new_data[newIndex + 1] = std::min(255, std::max(0, static_cast<int>(greenSum)));
            new_data[newIndex + 2] = std::min(255, std::max(0, static_cast<int>(blueSum)));
        }
    }

    data.swap(new_data);
};
