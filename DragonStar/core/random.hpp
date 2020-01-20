// ================================================================
//
// random.hpp
// 
// Functions used to generate random values.
//
// ================================================================

#pragma once

#include <random>

namespace Random {
	// Returns a random seed.
	uint64_t RandomSeed();

	// Returns a random seed using an MT.
	uint64_t RandomSeed(std::mt19937_64& mt);

	// Returns a random int value. Values are inclusive.
	int RandomInt(int min, int max);

	// Returns a random int value. Values are inclusive.
	int RandomInt(int min, int max, std::mt19937_64& mt);

	// Returns a random size_t value. Values are inclusive.
	size_t RandomSizeT(size_t min, size_t max);

	// Returns a random size_t value. Values are inclusive.
	size_t RandomSizeT(size_t min, size_t max, std::mt19937_64& mt);

	// Returns a random double value. Min is inclusive, max is exlusive.
	double RandomDouble(double min, double max);

	// Returns a random double value. Min is inclusive, max is exlusive.
	double RandomDouble(double min, double max, std::mt19937_64& mt);

}
