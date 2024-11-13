#ifndef _0EXECTION0_
#define _0EXECTION0_

#include <pservice_base>
#include <future>

#include <limits>
#include <vector>
#include <array>
#include "printer.hpp"
#include "exception.hpp"

#include "generator.hpp"
#include "constant.hpp"
#include "bitstring.hpp"
#include "function.hpp"

#include "outcome.hpp"

STD_PSERVICE_BEGIN

typedef bitstring chromosome;
typedef bool gene;

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

//------------------------------------------------
// operators:

std::vector<double> fitness_values;

void evaluate(std::vector<chromosome>& population, fct_ptr fitness)
{

}

void select(std::vector<chromosome>& population, fct_ptr fitness)
{
    // greater chance for those with a better fitness value
    double total_fitness = 0;
    for (size_t i = 0; i < population.size(); i++)
        total_fitness += fitness_values.at(i);
    
    std::vector<double> probabilities(population.size());
    for (size_t i = 0; i < population.size(); i++)
        probabilities[i] = fitness_values.at(i) / total_fitness;

    std::vector<double> prob_roulette(probabilities);
    for (size_t i = 1; i < population.size(); i++)
        prob_roulette[i] += prob_roulette.at(i - 1);

    // generate number 

}


//------------------------------------------------
// genetic algorithm:

outcome genetic_algorithm(const function& f, const size_t generations)
{
    std::vector<chromosome> population;
    for (size_t i = 0; i < 50; i++)
        population.emplace_back(5);

    return { 0, 0 };

    // evaluate
    f.get_pointer();
    
    for (size_t index_g = 0; index_g < generations; index_g++)
    {
        // select
        // mutate
        // cross-over
        // evaluate
    }

    // evaluate return the best
}

// ask professor 

STD_PSERVICE_END
#endif
