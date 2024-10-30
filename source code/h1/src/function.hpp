#ifndef _0FUnCTIOn0_
#define _0FUnCTIOn0_

#include <pservice_base>
#include "constant.hpp"

class function
{
    // typedefs:
    typedef double (*fct_ptr)(const double* const numbers,
        const size_t dimension);
    
    // data members:
    unsigned int n, id;
    const double minimum;
    const double maximum;
    fct_ptr f;

public:
    // constructors:
    ~function() = default;
    function() = delete;
    function(double, double, fct_ptr);
    
    // specific methods:
    double exe(const double* const, const size_t) const;

    // constant methods:
    const unsigned int& get_n() const;
    const unsigned int& get_id() const;
    const double& get_minimum() const;
    const double& get_maximum() const;
    void* get_pointer() const;

    // static:
    static unsigned int unused_id;
};

//------------------------------------------------
// constructors:

unsigned int function::unused_id = 0;

function::function(double min, double max, fct_ptr ptr) :
    n(0), id(unused_id++), minimum(min), maximum(max), f(ptr)
{
    unsigned int power = 1;
    unsigned int precision = PRECISION;
    while(precision)
    {
        power *= 10;
        precision--;
    }

    n = (unsigned int)((maximum - minimum) * power);
    n = ceil(log2(n));
    precision += 1;
}

//------------------------------------------------
// specific methods:

double function::exe(const double* const numbers, 
    const size_t dimension) const
{
    return f(numbers, dimension);
}

//------------------------------------------------
// constant methods:

const unsigned int& function::get_n() const
{
    return n;
}

const unsigned int& function::get_id() const
{
    return id;
}

const double& function::get_minimum() const
{
    return minimum;
}

const double& function::get_maximum() const
{
    return maximum;
}

void* function::get_pointer() const
{
    return (void*)f;
}

#endif
