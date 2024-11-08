#ifndef _0EXECTION0_
#define _0EXECTION0_

#include <pservice_base>
#include <future>
#include <vector>

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

//------------------------------------------------
// component methods:

size_t decimal(const bitstring& b, const size_t i0, const size_t i1)
{
    size_t value = 0;
    for (size_t i = i0; i < i1; i++)
    {
        value *= 2;
        value += b[i];
    }

    return value;
}

double convert(const size_t decimal, const function& f)
{
    double value = f.get_minimum();
    value += decimal * (f.get_maximum() - f.get_minimum()) / 
        (pow(2, f.get_n()) - 1);
    return value;
}

double* convert(const bitstring& b, const function& f, 
    const size_t dimension)
{
    double* numbers = new double[dimension] {};
    for (size_t index_number = 0; index_number < dimension; index_number++)
    {
        size_t index_frst_bit = f.get_n() * index_number;
        size_t index_last_bit = f.get_n() * (index_number + 1);
        size_t value = decimal(b, index_frst_bit, index_last_bit);
        numbers[index_number] = convert(value, f);
    }

    return numbers;
}

bool improve(bitstring& candidate, const function& f,
    const improvement_type imprv, const size_t dimension)
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
                if (setting::is_better(value_imprv, value_neighborhood))
                    value_imprv = value_neighborhood;
                break;
            case improvement_type::worst:
                if (value_imprv == value_current ||
                    setting::is_better(value_neighborhood, value_imprv))
                    value_imprv = value_neighborhood;
                break;
            default: // first
                return true;
            }
        }

        candidate[i] = !candidate[i];
    }


    if (value_imprv != value_current) // -1 != index_bit
    {
        candidate[index_bit] = !candidate[index_bit];
        return true;
    }

    return false;
}

//------------------------------------------------
// default method:

local_outcome hillclimbing(const function& f, 
    const improvement_type imprv, const size_t dimension)
{
    time_measurement clock;
    bitstring representation(dimension * f.get_n());
    while (improve(representation, f, imprv, dimension));

    double* numbers = convert(representation, f, dimension);
    double value_candidate = f.exe(numbers, dimension);
    delete[]numbers;

    long long time = clock.stop(time_unit::millisecond);
    if (0 == time)
        throw exception_null();
    
    return { value_candidate, time };
}

//------------------------------------------------
// thread manipulation:

void parallel_iteration(local_outcome& o,
    const size_t n_thread, const function& f, 
    const improvement_type& imprv, const size_t dimension)
{
    // async execution
    std::vector<std::future<local_outcome>> output(n_thread);
    for (size_t i_thread = 0; i_thread < n_thread; i_thread++)
        output[i_thread] = std::async(std::launch::async,
            hillclimbing, f, imprv, dimension);
    
    // query of the data
    for (size_t i_thread = 0; i_thread < n_thread; i_thread++)
    {
        local_outcome candidate = output[i_thread].get();
        if (setting::is_better(o.minimum, candidate.minimum))
            o.minimum = candidate.minimum;
        o.time_measurement += candidate.time_measurement;
    }
}

//------------------------------------------------
// iterated methods:

/* returns the average time per iteration */
local_outcome iterated_hillclimbing(const function& f, 
    const improvement_type imprv, 
    const size_t dimension, 
    const size_t it_nr)
{
    //if (it_nr < 100) // weak statistical significance
        //throw exception_null();

    const unsigned int n_thread = std::thread::hardware_concurrency();
    double value_init = std::numeric_limits<double>::infinity();
    if (setting::objective == objective_type::maximum_point)
        value_init *= -1;

    local_outcome outcome{ value_init, 0 };
    size_t it = 0;

    for (; it + n_thread < it_nr; it += n_thread)
        parallel_iteration(outcome, n_thread, f, imprv, dimension);
    parallel_iteration(outcome, it_nr - it, f, imprv, dimension);
    
    outcome.time_measurement /= it_nr;
    return outcome;
}

/* returns the total time of all iterations */ 
[[deprecated("slow sequential execution")]]
local_outcome iterated_hillclimbing(const function& f,
    const improvement_type imprv, 
    const size_t dimension)
{
    return { 0, 0 };
    // start clock and act
    time_measurement clock;
    double local_minimum = std::numeric_limits<double>::infinity();
    if (setting::objective == objective_type::maximum_point)
        local_minimum *= -1;

    for (size_t i = 0; i < ITERATIONS_NUMBER; i++)
    {
        // improve
        bitstring representation(dimension * f.get_n());
        while (improve(representation, f, imprv, dimension));

        // vc
        double* numbers = convert(representation, f, dimension);
        double value_candidate = f.exe(numbers, dimension);
        delete[]numbers;

        // update
        if (setting::is_better(local_minimum, value_candidate))
            local_minimum = value_candidate;
    }

    // stop clock
    long long milliseconds = clock.stop(time_unit::millisecond);
    if (0 == milliseconds)
        throw exception_null();

    return { local_minimum, milliseconds };
}

local_outcome simulated_annealing(const function& f, const size_t dimension)
{
    // start clock and act
    time_measurement clock;
    double local_minimum = std::numeric_limits<double>::infinity();
    if (setting::objective == objective_type::maximum_point)
        local_minimum *= -1;

    // previouserature
    size_t previouserature = 0;

    for (size_t i = 0; i < ITERATIONS_NUMBER; i++)
    {
        // improve
        bitstring representation(f.get_n());
        if (improve(representation, f, improvement_type::best,
            dimension));
        //else if (true);
            // accept bad result
        
        // vc
        double* numbers = convert(representation, f, dimension);
        double value_candidate = f.exe(numbers, dimension);
        delete[]numbers;

        // update
        if (setting::is_better(local_minimum, value_candidate))
            local_minimum = value_candidate;

        // previouserature update (i)
    }

    // stop clock
    long long milliseconds = clock.stop(time_unit::millisecond);
    if (0 == milliseconds)
        throw exception_null();

    return { local_minimum, milliseconds };
}

STD_PSERVICE_END
#endif
