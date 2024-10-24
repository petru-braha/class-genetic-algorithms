#ifndef _0EXECTION0_
#define _0EXECTION0_

#include <vector>
#include "printer.hpp"

#include "constant.hpp"
#include "bitstring.hpp"
#include "function.hpp"

struct local_outcome
{
    double minimum;
    long long time_measurement;
};

bool improve(bitstring& candidate, improvement improvement_type)
{
    // compute the neigbohood
    for (size_t i = 0; i < candidate.size(); i++)
    {
        // negation
        
        // code
        
        // negation
    }
    /*
    if (improvement::best == improvement_type)
    {
        for (const double& value : hood)
            if (value < original)
                original = value;

        return original;
    }

    if (improvement::first == improvement_type)
    {
        for (const double& value : hood)
            if (value < original)
            {
                original = value;
                break;
            }

        return original;
    }

    // worst
    bool first_execution = true;
    double better_value = original;
    for (const double& value : hood)
        if (value < original)
        {
            if (first_execution)
            {
                better_value = value;
                first_execution = false;
            }
            else if (value > better_value)
                better_value = value;
        }

    original = better_value;
    return original;
    */
    return false;
}

const std::vector<double>& convert(const function& f,
    const bitstring& representation)
{
    const size_t dimension = 1;
    size_t bits_per_number = representation.size() / dimension;

    //double numbers[dimension];
    std::vector<double> numbers(dimension);
    for (size_t index_number = 0; index_number < dimension; index_number++)
    {
        size_t index_frst_bit = bits_per_number * index_number;
        size_t index_last_bit = bits_per_number * (index_number + 1);

        size_t value = 0;
        for (size_t index_bit = index_frst_bit; index_bit < index_last_bit; index_bit++)
        {
            value *= 2;
            value += representation[index_bit];
        }

        double final_value = f.get_minimum();
        final_value += f.get_minimum() + f.get_maximum() * value / (pow(2, bits_per_number) - 1);

        numbers[index_number] = final_value;
    }

    return numbers;
}

local_outcome iterated_hillclimbing(const function& f, 
    unsigned char dimension, improvement improvement_type)
{
    // start clock and act
    time_measurement clock;
    double local_minimum = 0.0;

    for (unsigned int i = 0; i < ITERATIONS_NUMBER; i++)
    {
        bitstring representation(f.get_n());
        while (improve(representation, improvement_type));
            
        double canditate = f.exe(convert(f, representation)); // vc

        if (canditate > local_minimum)
                local_minimum = canditate;
        print_iteration(i);
    }

    // stop clock
    long long milliseconds = clock.stop(time_unit::millisecond);
    if (0 == milliseconds); // error

    return { local_minimum, milliseconds };
}

struct setting
{
    int precision;
    int dimension;
    int objective;


    //mission m;
    solution s;
    improvement i;

};

#endif
