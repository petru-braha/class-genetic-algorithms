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

double* convert(const bitstring& b, const function& f, size_t dimension)
{
    size_t bits_per_number = b.size() / dimension;

    double* numbers = new double[dimension];
    for (size_t index_number = 0; index_number < dimension; index_number++)
    {
        size_t index_frst_bit = bits_per_number * index_number;
        size_t index_last_bit = bits_per_number * (index_number + 1);

        size_t value = 0;
        for (size_t index_bit = index_frst_bit; index_bit < index_last_bit; index_bit++)
        {
            value *= 2;
            value += b[index_bit];
        }

        double final_value = f.get_minimum();
        final_value += f.get_minimum() + f.get_maximum() * value / (pow(2, bits_per_number) - 1);

        numbers[index_number] = final_value;
    }

    return numbers;
}

bool improve(const function& f, unsigned char dimension, 
    improvement_type imprv, bitstring& candidate)
{
    double* numbers = convert(candidate, f, dimension);
    double value_current = f.exe(numbers, dimension);
    delete[]numbers;
    
    // compute neighborhood
    switch (imprv)
    {
    case improvement_type::best:
        double value_best_imprv = value_current;
        size_t index_bit = 0;
        
        for (size_t i = 0; i < candidate.size(); i++)
        {
            candidate[i] = !candidate[i];

            numbers = convert(candidate, f, dimension);
            double value_neighborhood = f.exe(numbers, dimension);
            delete[]numbers;

            if (setting::change(value_best_imprv, value_neighborhood))
                index_bit = i;

            candidate[i] = !candidate[i];
        }

        if (value_best_imprv != value_current)
        {
            b[index_bit] = !b[index_bit];
            return true;
        }

        break;

    case improvement_type::first:
        for (size_t i = 0; i < candidate.size(); i++)
        {
            candidate[i] = !candidate[i];

            numbers = convert(candidate, f, dimension);
            double value_neighborhood = f.exe(numbers, dimension);
            delete[]numbers;

            if (setting::change(value_best_imprv, value_neighborhood))
                return true;

            candidate[i] = !candidate[i];
        }

        break;

    case improvement_type::worst:
        double value_wrst_imprv = value_current;
        size_t index_bit = 0;
        
        for (size_t i = 0; i < candidate.size(); i++)
        {
            candidate[i] = !candidate[i];

            numbers = convert(candidate, f, dimension);
            double value_neighborhood = f.exe(numbers, dimension);
            delete[]numbers;

            if (setting::change(value_best_imprv, value_neighborhood))
                index_bit = i;

            candidate[i] = !candidate[i];
        }

        if (value_best_imprv != value_current)
        {
            b[index_bit] = !b[index_bit];
            return true;
        }

        break;

    default:
        break;
    }

    return false;
}

local_outcome iterated_hillclimbing(const function& f, 
    unsigned char dimension, improvement_type imprv)
{
    // start clock and act
    time_measurement clock;
    double local_minimum = 0;

    for (unsigned int i = 0; i < ITERATIONS_NUMBER; i++)
    {
        // improve
        bitstring representation(f.get_n());
        while (improve(f, dimension, imprv, representation));

        // vc
        double* numbers = convert(representation, f, dimension);
        double value_candidate = f.exe(numbers, dimension);
        delete[]numbers;

        // update
        if (value_candidate > local_minimum)
                local_minimum = value_candidate;
        print_iteration(i);
    }

    // stop clock
    long long milliseconds = clock.stop(time_unit::millisecond);
    if (0 == milliseconds); // error

    return { local_minimum, milliseconds };
}

#endif
