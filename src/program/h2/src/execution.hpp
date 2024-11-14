#ifndef _0EXECTION0_
#define _0EXECTION0_

#include <pservice_base>
#include <future>

#include <limits>
#include <vector>
#include <array>
#include "printer.hpp"
#include "exception.hpp"

#include "outcome.hpp"
#include "generator.hpp"
#include "constant.hpp"
#include "bitstring.hpp"
#include "function.hpp"

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

double* best_fitness_values = nullptr;

double evaluate(std::vector<chromosome>& population, const function& f)
{
    double fittest = parameter::poor_value();

    for (size_t i = 0; i < population.size(); i++)
    {
        double* fitness_values = convert(population.at(i), f, parameter::dimension);
        double candidate = f.exe(fitness_values);
        if (parameter::is_better(candidate, fittest))
        {
            fittest = candidate; 
            best_fitness_values ? delete[]best_fitness_values : (void)0;
            best_fitness_values = fitness_values;
        }
        else
            delete[]fitness_values;
    }
    
    return fittest;
}

void select(std::vector<chromosome>& population, function fitness)
{
    // greater chance for those with a better fitness value
    double total_fitness = 0;
    for (size_t i = 0; i < population.size(); i++)
        total_fitness += best_fitness_values[i];
    
    std::vector<double> probabilities(population.size());
    for (size_t i = 0; i < population.size(); i++)
        probabilities[i] = best_fitness_values[i] / total_fitness;

    std::vector<double> roulette(probabilities);
    for (size_t i = 1; i < population.size(); i++)
        roulette[i] += roulette.at(i - 1);

    // find next generation
    random_generator g;
    std::vector<size_t> index_presence(population.size());
    for (size_t i = 0; i < population.size(); i++)
        for (size_t spot = 0; spot < roulette.size(); spot++)
            if (g(0, 1) <= roulette.at(spot))
            {
                index_presence[spot]++;
                break;
            }

    std::vector<size_t> index_list_null;
    std::vector<size_t> index_list_real;
    for (size_t i = 0; i < index_presence.size(); i++)
    {
        if (0 == index_presence[i])
            index_list_null.emplace_back(i);
        else
            while (index_presence[i])
            {
                index_list_real.emplace_back(i);
                index_presence[i]--;
            }
    }

    size_t index_index_p = 0;
    for (size_t i = 0; i < index_list_null.size(); i++)
    {
        population[index_list_null[i]] = 
            population[index_list_real[index_index_p]];
        index_index_p++;
    }
}

void mutate(std::vector<chromosome>& population)
{

}

void cross_over(std::vector<chromosome>& population)
{

}

//------------------------------------------------
// genetic algorithm:

outcome genetic_algorithm(const function& f, const size_t generations = 100)
{
    time_measurement clock;

    std::vector<chromosome> population;
    for (size_t i = 0; i < POPULATION_SIZE; i++)
        population.emplace_back(f.get_n() * parameter::dimension);
    
    double local_optimum = evaluate(population, f);

    size_t stagnation = 0;
    for (size_t index_g = 0; index_g < generations; index_g++)
    {
        double previous_optimum = local_optimum;
        
        // operation
        select(population, f);
        mutate(population);
        cross_over(population);
        local_optimum = evaluate(population, f);

        // another halting condition
        if (previous_optimum >= local_optimum)
            stagnation++;
        else
            stagnation = 0;
        if (stagnation == GA_MAX_STAGNATION)
        {
            local_optimum = previous_optimum;
            break;
        }
    }

    return { local_optimum, clock.stop(time_unit::millisecond) };
}

STD_PSERVICE_END
#endif
