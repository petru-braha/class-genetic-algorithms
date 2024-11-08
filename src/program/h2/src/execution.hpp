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


STD_PSERVICE_END
#endif
