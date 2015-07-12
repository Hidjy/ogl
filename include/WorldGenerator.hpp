#pragma once

#include "Chunk.hpp"

#define GENERATOR_SIZE (32*4)

void GenerateWhiteNoise(float noise[GENERATOR_SIZE][GENERATOR_SIZE]);
void GeneratePerlinNoise(float perlinNoise[GENERATOR_SIZE][GENERATOR_SIZE], float baseNoise[GENERATOR_SIZE][GENERATOR_SIZE], int octaveCount);
float Interpolate(float x0, float x1, float alpha);
void GeneratePerlinNoise(float perlinNoise[GENERATOR_SIZE][GENERATOR_SIZE], float baseNoise[GENERATOR_SIZE][GENERATOR_SIZE], int octaveCount);
