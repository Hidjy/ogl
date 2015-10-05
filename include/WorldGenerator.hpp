#pragma once

#include "Chunk.hpp"

#define GENERATOR_SIZE (32 * 11)

#include "Chunk.hpp"

namespace WorldGenerator
{
	void GenerateWhiteNoise(float (*noise)[GENERATOR_SIZE][GENERATOR_SIZE]);
	void GenerateSmoothNoise(float (*smoothNoise)[GENERATOR_SIZE][GENERATOR_SIZE], float (*baseNoise)[GENERATOR_SIZE][GENERATOR_SIZE], int octave);
	float Interpolate(float x0, float x1, float alpha);
	void GeneratePerlinNoise(float (*perlinNoise)[GENERATOR_SIZE][GENERATOR_SIZE], float (*baseNoise)[GENERATOR_SIZE][GENERATOR_SIZE], int octaveCount);
	void GenerateMap(float(**ret)[GENERATOR_SIZE][GENERATOR_SIZE], int octaveCount);
}
