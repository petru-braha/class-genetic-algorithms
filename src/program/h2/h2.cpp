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

using namespace pservice;

static void run(const function&) {}

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
    run(michalewicz);
    run(rastrigin);
    run(schwefel);

    std::cout << "the program ran for " 
        << clock.stop(time_unit::minute) << " minutes.\n";
    return EXIT_SUCCESS;
}
