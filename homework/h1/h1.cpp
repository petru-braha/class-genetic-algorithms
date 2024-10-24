#include <stdlib.h>
#include <iostream>
#include <thread>
#include <vector>

#include <random>
#include <cmath>
#include "clock.hpp"
#include "printer.hpp"

#include "constant.hpp"
#include "bitstring.hpp"
#include "function.hpp"
#include "f_pointer.hpp"
#include "execution.hpp"

//using namespace pservice;

static void analysis(const function&, unsigned char, improvement);
static void run(const function&);

//------------------------------------------------
// start:

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
    run(michalewicz);
    run(rastrigin);
    run(schwefel);

    std::cout << "the program ran for " << clock.stop(time_unit::second) << " seconds.\n";
    return EXIT_SUCCESS;
}

void print_analysis_header(const function&, unsigned char, improvement, std::ostream&);
static void analysis(const function& f, unsigned char dimension, improvement improvement_type)
{
    // ux
    print_analysis_header(f, dimension, improvement_type);
    
    // act
    local_outcome sample_outcome[SAMPLE_NUMBER];

    //for (unsigned char index_sample = 0; index_sample < SAMPLE_NUMBER; index_sample++)
        //sample_local_outcome[index_sample] = iterated_hillclimbing(f, dimension, improvement_type);

    // print to ../output/primitive results
    // file per function
    // chapter per dimension
    // bullet points for each improvement type and time
    // solution analysis is done using r
}

static void run(const function& f)
{
    analysis(f, 30, improvement::best);
    analysis(f, 30, improvement::first);
    analysis(f, 30, improvement::worst);
}

// for(iteration) 
    // generate a bitstring
    // divide it by the number of dimensions
    // compute function of bitstring
    // compute function of neigborhood
