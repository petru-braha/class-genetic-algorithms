#ifndef _0FUNCTION0_
#define _0FUNCTION0_

#include "constant.hpp"
#include "value.hpp"

class function
{
    // data members
    unsigned int N, id;
    const double minimum;
    const double maximum;
    fct_ptr f;

public:
    // constructors:
    ~function() = default;
    function() = delete;
    function(const double&, const double&, fct_ptr);
    
    // specific methods:
    double run(unsigned char) const;

    // constant methods:
    const unsigned int& get_N() const;
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


function::function(const double& min, const double& max, fct_ptr ptr) :
    N(0), id(unused_id++), minimum(min), maximum(max), f(ptr)
{
    unsigned int power = 10;
    unsigned int precision = PRECISION;
    while(precision)
    {
        power *= 10;
        precision--;
    }

    N = (unsigned int)(maximum - minimum) * power;
}

//------------------------------------------------
// specific methods:

double function::run(unsigned char dimension) const
{
    return f(minimum, maximum, dimension);
}

//------------------------------------------------
// constant methods:

const unsigned int& function::get_N() const
{
    return N;
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
