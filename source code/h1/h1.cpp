#include <stdlib.h>
#include <iostream>
#include <vector>

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

using namespace pservice;
#pragma warning (disable :4996)

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
        << clock.stop(time_unit::second) << " seconds.\n";
    return EXIT_SUCCESS;
}

static void analysis(const function& f, improvement_type imprv, size_t dimension)
{
    // ux
    print_analysis_header(f, imprv, dimension, std::cout);
    
    // act
    local_outcome sample_outcome[SAMPLE_NUMBER]{};
    for (unsigned char index_sample = 0; index_sample < SAMPLE_NUMBER; index_sample++)
        sample_outcome[index_sample] = iterated_hillclimbing(f, imprv, dimension);

    // print acts
    printer file(f, imprv, dimension);
    for (unsigned char index_sample = 0; index_sample < SAMPLE_NUMBER; index_sample++)
        file << sample_outcome[index_sample];
}

static void run(const function& f)
{
    size_t d = 1; // 30
    analysis(f, improvement_type::first, d);
    //analysis(f, improvement_type::first, d);
    //analysis(f, d, improvement_type::worst);
}

// how much time did it took for the all iterations of a single sample
