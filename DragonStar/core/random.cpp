// ================================================================
//
// random.cpp
//
// ================================================================

#include "random.hpp"

uint64_t Random::RandomSeed() {
	std::random_device rd;
	uint64_t seed = static_cast<uint64_t>(rd()) << 32 | rd();
	return seed;
}

uint64_t Random::RandomSeed(std::mt19937_64& mt) {
	std::uniform_int_distribution<uint64_t> dist(0);
	return dist(mt);
}

int Random::RandomInt(int min, int max) {
	std::random_device rd;
	std::mt19937_64 mt(rd());
	std::uniform_int_distribution<int> dist(min, max);
	return dist(mt);
}

int Random::RandomInt(int min, int max, std::mt19937_64& mt) {
	std::uniform_int_distribution<int> dist(min, max);
	return dist(mt);
}

size_t Random::RandomSizeT(size_t min, size_t max) {
	std::random_device rd;
	std::mt19937_64 mt(rd());
	std::uniform_int_distribution<size_t> dist(min, max);
	return dist(mt);
}

size_t Random::RandomSizeT(size_t min, size_t max, std::mt19937_64& mt) {
	std::uniform_int_distribution<size_t> dist(min, max);
	return dist(mt);
}

double Random::RandomDouble(double min, double max) {
	std::random_device rd;
	std::mt19937_64 mt(rd());
	std::uniform_real_distribution<double> dist(min, max);
	return dist(mt);
}

double Random::RandomDouble(double min, double max, std::mt19937_64& mt) {
	std::uniform_real_distribution<double> dist(min, max);
	return dist(mt);
}