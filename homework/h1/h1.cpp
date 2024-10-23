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

struct outcome
{
    double local_minimum;
    long long time_measurement;
};

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

    /*run(de_jong_1);
    run(michalewicz);
    run(rastrigin);
    run(schwefel);*/

    std::cout << "the program ran for " << clock.stop(time_unit::second) << " seconds.\n";
    return EXIT_SUCCESS;
}
