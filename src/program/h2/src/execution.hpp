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

random_generator g;

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

std::vector<double> population_fitness(POPULATION_SIZE);

double evaluate(const std::vector<chromosome>& population, const function& f)
{
    double fittest = parameter::poor_value();

    for (size_t i = 0; i < population.size(); i++)
    {
        double* numbers = convert(population.at(i), f, parameter::dimension);
        double candidate = f.exe(numbers);
        delete[]numbers;
        
        if (parameter::is_better(candidate, fittest))
            fittest = candidate;

        population_fitness[i] = candidate;
    }
    
    return fittest;
}

void select(std::vector<chromosome>& population, function fitness)
{
    // greater chance for those with a better fitness value
    double total_fitness = 0;
    for (size_t i = 0; i < population.size(); i++)
        total_fitness += population_fitness.at(i);
    
    std::vector<double> probabilities(population.size());
    for (size_t i = 0; i < population.size(); i++)
        probabilities[i] = population_fitness.at(i) / total_fitness;

    std::vector<double> roulette(probabilities);
    for (size_t i = 1; i < population.size(); i++)
        roulette[i] += roulette.at(i - 1);

    // find next generation
    std::vector<size_t> index_presence(population.size());
    for (size_t i = 0; i < population.size(); i++)
    {
        double probability = g(0.0, 1.0);
        size_t spot = 0;
        while (spot < roulette.size() &&
            probability > roulette.at(spot))
            spot++;
        index_presence[spot]++;
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

void cross_over(std::vector<chromosome>& population)
{
    std::vector<size_t> indexes;
    for (size_t index_chromosome = 0;
        index_chromosome < population.size(); index_chromosome++)
        if (g(0.0, 1.0) < parameter::creaxion_probability)
            indexes.emplace_back(index_chromosome);

    // odd number of chromosomes fix 
    // random decision to add / remove
    if (indexes.size() % 2 && g((size_t)0, (size_t)1))
    {
        size_t index_chromosome = 0;
        
        bool condition = true; // don't repeat any index
        do
        {
            condition = true;
            index_chromosome = g(0, population.size() - 1);
            
            for(size_t i = 0; i < indexes.size(); i++)
                if (indexes.at(i) == index_chromosome)
                {
                    condition = false;
                    break;
                }
        } while (false == condition);
        
        indexes.emplace_back(index_chromosome);
    }

    size_t gene_number = population.at(0).size();
    size_t nr_c = indexes.size();
    if (0 == nr_c % 2) // there is one chromosome left out
        nr_c--; // it was refused to accept another one
    // in this case: at the end of the loop |indexes| = 1

    for (size_t it_c = 0; it_c < nr_c; it_c += 2)
    {
        // random mate
        size_t index_frst = 0, index_last = 0;
        index_frst = g(0, indexes.size() - 1);
        index_last = g(0, indexes.size() - 1);
        while(index_frst == index_last)
            index_last = g(0, indexes.size() - 1);
        indexes.erase(indexes.begin() + index_frst);
        indexes.erase(indexes.begin() + index_last);

        // for more redable code
        chromosome& x = population.at(indexes[index_frst]);
        chromosome& y = population.at(indexes[index_last]);

        // temp = x; x = y; y = temp;
        gene temp_gene;
        size_t index_gene = g(0, gene_number - 2);
        for (size_t i = index_gene + 1; i < gene_number; i++)
        {
            temp_gene = x[i];
            x[i] = y[i];
            y[i] = temp_gene;
        }
    }
}

void mutate(std::vector<chromosome>& population)
{
    size_t gene_number = population.at(0).size();
    for (chromosome& c : population)
        for (size_t index_gene = 0; index_gene < gene_number; index_gene++)
            if (g(0.0, 1.0) < parameter::mutation_probability)
                c[index_gene] = !c[index_gene];
}

//------------------------------------------------
// genetic algorithm:

outcome genetic_algorithm(const function& f, const size_t generations)
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
        
        // operators
        select(population, f);
        cross_over(population);
        mutate(population);
        local_optimum = evaluate(population, f);

        // another halting condition
        if (previous_optimum >= local_optimum)
        {
            local_optimum = previous_optimum;
            stagnation++;
            if (GA_MAX_STAGNATION == stagnation)
                break;
        }
        else
            stagnation = 0;
    }

    return { local_optimum, clock.stop(time_unit::millisecond) };
}

// stochastic error in sampling - chapter 4

STD_PSERVICE_END
#endif
