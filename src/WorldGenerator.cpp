#include "WorldGenerator.hpp"
#include <stdlib.h>
#include <time.h>

void WorldGenerator::GenerateWhiteNoise(float (*noise)[GENERATOR_SIZE][GENERATOR_SIZE])
{
    for (int i = 0; i < GENERATOR_SIZE; i++)
    {
        for (int j = 0; j < GENERATOR_SIZE; j++)
        {
            (*noise)[i][j] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        }
    }
}

void WorldGenerator::GenerateSmoothNoise(float (*smoothNoise)[GENERATOR_SIZE][GENERATOR_SIZE], float (*baseNoise)[GENERATOR_SIZE][GENERATOR_SIZE], int octave)
{
   int width = GENERATOR_SIZE;
   int height = GENERATOR_SIZE;

   int samplePeriod = 1 << octave; // calculates 2 ^ k
   float sampleFrequency = 1.0f / samplePeriod;

   for (int i = 0; i < width; i++)
   {
      //calculate the horizontal sampling indices
      int sample_i0 = (i / samplePeriod) * samplePeriod;
      int sample_i1 = (sample_i0 + samplePeriod) % width; //wrap around
      float horizontal_blend = (i - sample_i0) * sampleFrequency;

      for (int j = 0; j < height; j++)
      {
         //calculate the vertical sampling indices
         int sample_j0 = (j / samplePeriod) * samplePeriod;
         int sample_j1 = (sample_j0 + samplePeriod) % height; //wrap around
         float vertical_blend = (j - sample_j0) * sampleFrequency;

         //blend the top two corners
         float top = Interpolate(
            (*baseNoise)[sample_i0][sample_j0],
            (*baseNoise)[sample_i1][sample_j0],
            horizontal_blend
        );

         //blend the bottom two corners
         float bottom = Interpolate(
            (*baseNoise)[sample_i0][sample_j1],
            (*baseNoise)[sample_i1][sample_j1],
            horizontal_blend
        );

         //final blend
         (*smoothNoise)[i][j] = Interpolate(top, bottom, vertical_blend);
      }
   }
}

float WorldGenerator::Interpolate(float x0, float x1, float alpha)
{
   return x0 * (1 - alpha) + alpha * x1;
}

void WorldGenerator::GeneratePerlinNoise(float (*perlinNoise)[GENERATOR_SIZE][GENERATOR_SIZE], float (*baseNoise)[GENERATOR_SIZE][GENERATOR_SIZE], int octaveCount)
{
   int width = GENERATOR_SIZE;
   int height = GENERATOR_SIZE;

   float (*smoothNoise)[GENERATOR_SIZE][GENERATOR_SIZE] = new float[octaveCount][GENERATOR_SIZE][GENERATOR_SIZE]; //an array of 2D arrays containing
   float persistance = 0.5f;

   //generate smooth noise
   for (int i = 0; i < octaveCount; i++)
   {
       WorldGenerator::GenerateSmoothNoise(&smoothNoise[i], baseNoise, i);
   }

    float amplitude = 1.0f;
    float totalAmplitude = 0.0f;

    //blend noise together
    for (int octave = octaveCount - 1; octave >= 0; octave--)
    {
       amplitude *= persistance;
       totalAmplitude += amplitude;

       for (int i = 0; i < width; i++)
       {
          for (int j = 0; j < height; j++)
          {
             (*perlinNoise)[i][j] += smoothNoise[octave][i][j] * amplitude;
          }
       }
    }

   //normalisation
   for (int i = 0; i < width; i++)
   {
      for (int j = 0; j < height; j++)
      {
         (*perlinNoise)[i][j] /= totalAmplitude;
      }
   }
}


void  WorldGenerator::GenerateMap(float(**ret)[GENERATOR_SIZE][GENERATOR_SIZE], int octaveCount) {
    float (*noise)[GENERATOR_SIZE][GENERATOR_SIZE] = (float (*)[GENERATOR_SIZE][GENERATOR_SIZE]) new float[GENERATOR_SIZE][GENERATOR_SIZE];
    WorldGenerator::GenerateWhiteNoise(noise);
    *ret = (float (*)[GENERATOR_SIZE][GENERATOR_SIZE]) new float[GENERATOR_SIZE][GENERATOR_SIZE];
    WorldGenerator::GeneratePerlinNoise(*ret, noise, 7);
}
