/**
 * @file randomizer.h
 * @brief Class holding random number generator setup.
*/


#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include <random>
#include <chrono>

/**
 * @class `RandomNumberGenerator`
 * @brief A class holding random number generator functionality.
*/

class RandomNumberGenerator {
public:
    RandomNumberGenerator();
    int get_random_number(int min, int max);
private:
    std::mt19937 gen;
};

#endif //RANDOMIZER_H
