// RandomNumberGenerator.hpp
// Class Wrapping Radom Number Generator
// it returns positive integers from given range
// Karol Janic February 2023

#ifndef RANDOM_NUMBER_GENERATOR_HPP
#define RANDOM_NUMBER_GENERATOR_HPP

#include <random>

class RandomNumberGenerator {
private:
    std::mt19937 generator;
public:
    RandomNumberGenerator() : generator(std::random_device{}()) { }

    RandomNumberGenerator(int seed) : generator(seed) { }

    unsigned int get(unsigned int lowerBound, unsigned int upperBound) {
        std::uniform_int_distribution<unsigned int> dis(lowerBound, upperBound);

        return dis(generator);
    }
};

#endif // RANDOM_NUMBER_GENERATOR_HPP
