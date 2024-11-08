#include <stdlib.h>
#include <iostream>
#include <thread>

#include "constant.hpp"
#include "setting.hpp"
#include "clock.hpp"
#include "printer.hpp"

#include "bitstring.hpp"
#include "function.hpp"
#include "f_pointer.hpp"
#include "execution.hpp"

#include "t_infinity.hpp"
#include "t_printer.hpp"
#include "t_normalize.hpp"
#include "t_clock.hpp"

using namespace pservice;

static void analysis(const function&, improvement_type, size_t);
static void run(const function&);

//------------------------------------------------
// start:

int main()
{
    std::cout << "h1 program starts running.\n\n";
    srand((unsigned int)time(0));
    setting::objective = objective_type::minimum_point;
    setting::precision = PRECISION;

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

static void analysis(const function& f, improvement_type imprv, size_t dimension)
{
    print_analysis_header(f, imprv, dimension, std::cout);
    
    local_outcome sample_outcome[SAMPLE_NUMBER]{};
    for (size_t index_sample = 0; index_sample < SAMPLE_NUMBER; index_sample++)
    {
        std::cout << "sample " << index_sample << '\n';
        sample_outcome[index_sample] = iterated_hillclimbing(f, imprv, dimension, 5);
    }
    std::cout << '\n';
    
    printer file(f, imprv, dimension);
    for (size_t index_sample = 0; index_sample < SAMPLE_NUMBER; index_sample++)
        file << sample_outcome[index_sample];
}

static void run(const function& f)
{
    size_t d = 5; 
    analysis(f, improvement_type::best, d);
    analysis(f, improvement_type::first, d);
    analysis(f, improvement_type::worst, d);
}
