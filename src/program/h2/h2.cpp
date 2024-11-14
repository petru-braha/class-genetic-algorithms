#include <stdlib.h>
#include <iostream>
#include <thread>

#include "constant.hpp"
#include "parameter.hpp"
#include "clock.hpp"
#include "printer.hpp"

#include "bitstring.hpp"
#include "function.hpp"
#include "execution.hpp"

using namespace pservice;

objective_type parameter::objective = objective_type::minimum_point;
int parameter::precision = 5;
int parameter::dimension = 100;
double parameter::mutation_probability = 0.01;
double parameter::creaxion_probability = 0.25;
fct_ptr parameter::fitness_function = fctptr_dejong1;

static void run(const function&);

int main()
{
    std::cout << "h1 program starts running.\n\n";
    srand((unsigned int)time(0));
    
    const function de_jong_1(-5.12, 5.12, fctptr_dejong1); 
    const function michalewicz(0, PI, fctptr_michalewicz);
    const function rastrigin(-5.12, 5.12, fctptr_rastrigin);
    const function schwefel(-500.0, 500.0, fctptr_schwefel);

    time_measurement clock;

    run(de_jong_1);
    //run(michalewicz);
    //run(rastrigin);
    //run(schwefel);

    std::cout << "the program ran for " 
        << clock.stop(time_unit::minute) << " minutes.\n";
    return EXIT_SUCCESS;
}

// for each dimension
static void run(const function& f)
{
    outcome sample[SAMPLE_NUMBER]{};
    printer file(f);
    
    parameter::dimension = 10;
    for (size_t i = 0; i < SAMPLE_NUMBER; i++)
    {
        sample[i] = genetic_algorithm(f);
        file << sample[i];
    }
    
    parameter::dimension = 30;
    for (size_t i = 0; i < SAMPLE_NUMBER; i++)
    {
        sample[i] = genetic_algorithm(f);
        file << sample[i];
    }
}