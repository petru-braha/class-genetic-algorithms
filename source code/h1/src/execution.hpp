#ifndef _0EXECTION0_
#define _0EXECTION0_

#include <pservice_base>
#include <limits>
#include <vector>
#include "printer.hpp"
#include "exception.hpp"

#include "generator.hpp"
#include "constant.hpp"
#include "bitstring.hpp"
#include "function.hpp"

#include "local_outcome.hpp"

STD_PSERVICE_BEGIN

double* convert(const bitstring& b, const function& f, size_t dimension)
{
    size_t bits_per_number = b.size() / dimension;

    double* numbers = new double[dimension] {};
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
        final_value += value * (f.get_maximum() - f.get_minimum()) / (pow(2, bits_per_number) - 1);

        numbers[index_number] = final_value;
    }

    return numbers;
}

bool improve(bitstring& candidate, const function& f, 
    improvement_type imprv, size_t dimension)
{
    double* numbers = convert(candidate, f, dimension);
    double value_current = f.exe(numbers, dimension);
    delete[]numbers;

    double value_imprv = value_current;
    long long index_bit = -1;

    for (size_t i = 0; i < candidate.size(); i++)
    {
        candidate[i] = !candidate[i];

        numbers = convert(candidate, f, dimension);
        double value_neighborhood = f.exe(numbers, dimension);
        delete[]numbers;

        if (setting::is_better(value_current, value_neighborhood))
        {
            index_bit = i;

            switch (imprv)
            {
            case improvement_type::best:
                if (value_neighborhood > value_imprv)
                    value_imprv = value_neighborhood;
                break;
            case improvement_type::worst:
                if(value_imprv == value_current || 
                    value_neighborhood < value_imprv)
                    value_imprv = value_neighborhood;
                break;
            default: // first
                return true;
            }
        }

        candidate[i] = !candidate[i];
    }

    if (value_imprv != value_current)
    {
        candidate[index_bit] = !candidate[index_bit];
        return true;
    }

    return false;
}

local_outcome iterated_hillclimbing(const function& f, 
    improvement_type imprv, size_t dimension)
{
    // start clock and act
    time_measurement clock;
    double local_minimum = std::numeric_limits<double>::infinity();
    if (setting::objective == objective_type::maximum_point)
        local_minimum *= -1;

    for (size_t i = 0; i < ITERATIONS_NUMBER; i++)
    {
        // improve
        bitstring representation(f.get_n());
        while (improve(representation, f, imprv, dimension));

        // vc
        double* numbers = convert(representation, f, dimension);
        double value_candidate = f.exe(numbers, dimension);
        delete[]numbers;

        // update
        if (setting::is_better(local_minimum, value_candidate))
            local_minimum = value_candidate;
        print_iteration(i);
    }

    // stop clock
    long long milliseconds = clock.stop(time_unit::millisecond);
    if (0 == milliseconds)
        throw exception_null();

    return { local_minimum, milliseconds };
}

local_outcome simulated_annealing(const function& f, size_t dimension)
{
    // start clock and act
    time_measurement clock;
    double local_minimum = std::numeric_limits<double>::infinity();
    if (setting::objective == objective_type::maximum_point)
        local_minimum *= -1;

    for (size_t i = 0; i < ITERATIONS_NUMBER; i++)
    {
        // improve
        bitstring representation(f.get_n());
        while (improve(representation, f, improvement_type::best, 
            dimension));

        // vc
        double* numbers = convert(representation, f, dimension);
        double value_candidate = f.exe(numbers, dimension);
        delete[]numbers;

        // update
        if (setting::is_better(local_minimum, value_candidate))
            local_minimum = value_candidate;
        print_iteration(i);
    }

    // stop clock
    long long milliseconds = clock.stop(time_unit::millisecond);
    if (0 == milliseconds)
        throw exception_null();

    return { local_minimum, milliseconds };
}

STD_PSERVICE_END
#endif
