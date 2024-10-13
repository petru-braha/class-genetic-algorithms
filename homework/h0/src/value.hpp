#ifndef _0VALUE0_
#define _0VALUE0_

#include <stdlib.h>
#include <time.h> 
#include "constant.hpp"

double rand(double minimum, double maximum, unsigned char precision = 5)
{
    // aiming to a evenly distributed values 
    double multiplier = 1.0;
    for(unsigned char i = 0; i < precision; i++)
        multiplier *= 10.0;

    // understand values
    ull mini((ull)(minimum * multiplier)), maxi((ull)(maximum * multiplier));
    ull difference = maxi - mini;
    
    // get digit number
    ull temp = difference;
    unsigned char digits = 0;
    while(temp)
    {
        digits++;
        temp /= 10;
    }

    // build random
    ull random = 0;
    for(unsigned char i = 0; i < digits; i++)
    {
        random *= 10;
        random += ull(rand() % 10);
    }
    
    random %= difference;
    ull result = mini + random;
    return ((double)result / multiplier);
}

class value
{
    unsigned char dimension;
    double* components;

public:
    // constructors:
    ~value();
    value(const double&, const double&, unsigned char);  

    // constant methods:
    double& operator [] (unsigned char);
    const double& get(unsigned char) const;
    const double* get_pointer() const;
    unsigned char get_dimension() const;
    void print() const;
};

//------------------------------------------------
// constructors:

// what if program crashes before?
value::~value() 
{
    delete[]components;
}

// initialize random values
value::value(const double& minimum, 
            const double& maximum, unsigned char dim = 2)
: dimension(dim), components(nullptr)
{
    components = new double[dimension]{};
    for(unsigned char i = 0; i < dimension; i++)
        components[i] = rand(minimum, maximum);
}

//------------------------------------------------
// constant methods

double& value::operator [] (unsigned char index)
{
    if(index >= dimension)
        throw -1;
    return components[index];
}

const double& value::get(unsigned char index) const
{
    if(index >= dimension)
        throw -1;
    return components[index];
}

const double* value::get_pointer() const
{
    return components;
}

unsigned char value::get_dimension() const
{
    return dimension;
}    

void value::print() const
{
    for(unsigned char i = 0; i < dimension; i++)
        std::cout << components[i] << ' ';
    std::cout << '\n';
}

#endif
