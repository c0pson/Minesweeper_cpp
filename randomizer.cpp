/**
 * @file randomizer.cpp
 * @brief Implementation of `RandomNumberGenerator` class and related functions.
*/

#include "randomizer.h"

/**
 * @brief Initializes the RandomNumberGenerator object.
 * The `seed` variable uses `std::chrono::high_resolution_clock::now()` to get current time, 
 * then `.time_since_epoch()` to get the lowest possible state of the clock for current operating system,
 * and then .count() to convert duration of this time to large integer which will be used for seed of this
 * random number generator.
 * 
 * The `gen` variable uses std::mt19937(seed) which is commonly used algorithm for generating random numbers with provided seed.
*/

RandomNumberGenerator::RandomNumberGenerator() {
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    gen = std::mt19937(seed);
}

/**
 * @brief Generates a random number within a specified range.
 * 
 * @param min - The minimum value that can be generated.
 * @param max - The maximum value that can be generated.
 * 
 * @return Random value in range of `min` and `max`.
*/

int RandomNumberGenerator::get_random_number(int min, int max) {
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}
