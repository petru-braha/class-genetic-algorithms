#include <iostream>
#include <thread>

#include <random>
#include <cmath>

#include "constant.hpp"
#include "value.hpp"
#include "function.hpp"
#include "f_pointer.hpp"

static const unsigned int thread_number = std::thread::hardware_concurrency();

static void print_available_functions()
{
    std::cout << "0. de_jong_1\n" 
        << "1. michalewicz\n" 
        << "2. rastrigin\n"
        << "3. schwefel\n";
}

void analysis(const function& f, unsigned char dimension);

void run(const function& f)
{
    analysis(f, 2);
    analysis(f, 10);
}

//------------------------------------------------
// start

int main()
{
    const function de_jong_1(-5.12, 5.12, fctptr_dejong1);
    de_jong_1.get_N(); 
    return 0;
    std::cout << "program starts running.\n\n";
    srand((unsigned int)time(0));

    //const function de_jong_1(-5.12, 5.12, fctptr_dejong1); 
    const function michalewicz(0, PI, fctptr_michalewicz); 
    const function rastrigin(-5.12, 5.12, fctptr_rastrigin);
    const function schwefel(-500.0, 500.0, fctptr_schwefel);    
    
    unsigned char decision = 'y';
    std::cout << "study all functions? (y/n) ";
    std::cin >> decision;
    std::cout << '\n';

    while(true){}
    if('y' == decision)
    {
        // on different threads
        run(de_jong_1);
        run(michalewicz);
        run(rastrigin);
        run(schwefel);
    }

    else
    {
        print_available_functions(); 
        std::cout << "please type the index of the function to be studied ";
        std::cin >> decision;
        std::cout << '\n';

        switch (decision)
        {
        case 0:
            run(de_jong_1);
            break;
        case 1:
            run(michalewicz);
            break;
        case 2:
            run(rastrigin);
            break;
        case 3:
            run(schwefel);
            break;
        
        default:
            // error 
            break;
        }
    }
    
    // choose run () 
    // choose function
    

    // choose dimension: 2 / 10
    // choose approach:  d / h
    

    // run

    // execution // calculate time
    
    // compare results with known 

    return 0;
}
