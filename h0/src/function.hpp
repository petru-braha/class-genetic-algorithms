#ifndef _0FUNCTION0_
#define _0FUNCTION0_

#include "constant.hpp"
#include "value.hpp"

class function
{
    // data members:
    const double minimum;
    const double maximum;
    double (*f)(const double&, const double&, unsigned char);
    unsigned int N;
    
public:
    // constructors:
    ~function() = default;
    function() = delete;
    function(const double&, const double&, auto);
    
    // specific methods:
    double run(unsigned char);

    // constant methods:
    const unsigned int& get_N() const;
    const double& get_minimum() const;
    const double& get_maximum() const;
    void* get_pointer() const;
};

//------------------------------------------------
// constructors:

function::function(const double& min, const double& max, auto ptr) :
    minimum(min), maximum(max), f((decltype(f))ptr), N(0) 
{
    double power = 10.0;
    unsigned int precision = PRECISION;
    while(precision)
    {
        power *= 10;
        precision--;
    }

    N = (maximum - minimum) * power;
}

//------------------------------------------------
// specific methods:

double function::run(unsigned char dimension)
{
    return f(minimum, maximum, dimension);
}

//------------------------------------------------
// constant methods:

const unsigned int& function::get_N() const
{
    return N;
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
