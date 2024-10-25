#ifndef _0CONSTANT0_
#define _0CONSTANT0_

#include <pservice_base>
#include <random>

#define ERROR_CODE -1

#define SAMPLE_NUMBER 30
#define ITERATIONS_NUMBER 10000

#define TO_PRECISION 100000
#define PRECISION 5
#define PI 3.14159

enum class objective_type // not now
{
    minimum_point, maximum_point
};

enum class improvement_type
{
    best, first, worst
};

enum class solution_type
{
    best, average, worst
};

void normalize(double& number)
{
    number = (double)((long long)(number * TO_PRECISION)) / TO_PRECISION;
}

class random_generator
{
    std::mt19937 generator;

public:
    inline random_generator() {
        size_t seed_of_seed = time(0) + clock() * 1000 + 10000 *
            std::hash<std::thread::id>{}(std::this_thread::get_id());
        
        std::mt19937 random_seed;
        random_seed.seed((unsigned int)seed_of_seed);
        random_seed.discard(31337);

        generator.seed(random_seed());
    }

    inline unsigned int operator () () { return generator(); }
};

#endif
