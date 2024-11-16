#include <stdlib.h>
#include <iostream>
#include <future>
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
int parameter::dimension = 10;
double parameter::mutation_probability = 0.01;
double parameter::creaxion_probability = 0.25;
fct_ptr parameter::fitness_function = fctptr_dejong1;

static void run(const function&);

int main()
{
    const function de_jong_1(-5.12, 5.12, fctptr_dejong1); 
    const function rastrigin(-5.12, 5.12, fctptr_rastrigin);
    const function schwefel(-500.0, 500.0, fctptr_schwefel);
    const function michalewicz(0, PI, fctptr_michalewicz);

    std::cout << "h2 program starts running.\n\n";
    time_measurement clock;

    run(de_jong_1);
    run(rastrigin);
    run(schwefel);
    run(michalewicz);

    std::cout << "the program ran for " 
        << clock.stop(time_unit::minute) << " minutes.\n";
    return EXIT_SUCCESS;
}

static void parallel_sampling(const function& f, 
    const size_t n_thread, printer& file)
{
    std::vector<std::future<outcome>> output(n_thread);
    for (size_t i_thread = 0; i_thread < n_thread; i_thread++)
        output[i_thread] = std::async(std::launch::async, 
            genetic_algorithm, f, GENERATIONS_NUMBER);

    for (size_t i_thread = 0; i_thread < n_thread; i_thread++)
    {
        outcome candidate = output[i_thread].get();
        file << candidate;
    }
}

// for each dimension
static void run(const function& f)
{
    parameter::dimension = 10;
    size_t n_thread = std::thread::hardware_concurrency();
    size_t it = 0;

    parameter::dimension = 10;
    printer file_10(f);
    ga_print_header(f);
    for (it = 0; it + n_thread <= SAMPLE_NUMBER; it += n_thread)
        parallel_sampling(f, n_thread, file_10);
    parallel_sampling(f, SAMPLE_NUMBER - it, file_10);

    parameter::dimension = 30;
    printer file_30(f);
    ga_print_header(f);
    for (it = 0; it + n_thread <= SAMPLE_NUMBER; it += n_thread)
        parallel_sampling(f, n_thread, file_30);
    parallel_sampling(f, SAMPLE_NUMBER - it, file_30);
}
