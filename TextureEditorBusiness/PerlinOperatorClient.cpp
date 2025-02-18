#include "PerlinOperatorClient.h"
#include "FastNoiseLite.h"
#include "DraftClient.h"

/*
* /Brief : Function to generate a Perlin noise texture using FastNoiseLite
* return : vector that contain perlin data (can be use by opengl)
*/
std::vector<unsigned char> PerlinOperatorClient::MakePerlin()
{
    std::vector<unsigned char> noiseData(width * height * 4);

    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);

    /* Generate a value for each pixel */
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            float value = noise.GetNoise((float)x, (float)y);
            value = (value + 1.0f) / 2.0f; // Normaliser entre 0 et 1
            unsigned char pixel = static_cast<unsigned char>(value * 255);

            /* Set RGBA value */
            int index = (y * width + x) * 4;
            noiseData[index] = pixel;
            noiseData[index + 1] = pixel;
            noiseData[index + 2] = pixel;
            noiseData[index + 3] = 255;
        }
    }
    return noiseData;
}

//void PerlinOperator::Activate(DraftClient* draft)
//{
//    Data test;
//    test-> = MakePerlin(128,128);
//    draft->images.push(res);
//
//}

