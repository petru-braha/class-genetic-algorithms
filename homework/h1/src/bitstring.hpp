#ifndef _0BITSTRING0_
#define _0BITSTRING0_

#include <pservice_base>
#include <stdlib.h>
#include <utility>
#include <thread>
#include <random>
#include <time.h> 
#include "constant.hpp"

#include <vector>

/* comments:
* it don't have to consider here the minimum, maximum and precision
* it's a task for the developer from future
*/

class bitstring
{
    std::vector<bool> bits;

public:
    // constructors:
    ~bitstring() = default;
    bitstring(size_t);
    
    // specific methods:
    double convert() const;
    
    // specific methods:
    bool operator [] (size_t) const;
    size_t size() const;
    void  print() const;
};

//------------------------------------------------
// constructors:

bitstring::bitstring(size_t n) : bits(n)
{
    random_generator g;
    for (size_t i = 0; i < n; i++)
        bits[i] = g() % 2;
}

//------------------------------------------------
// constant methods

bool bitstring::operator [] (size_t index) const
{
    if (index >= bits.size()); // error
        
    return bits[index];
}

size_t bitstring::size() const
{
    return bits.size();
}

void bitstring::print() const
{
    size_t n = bits.size();
    for (size_t i = 0; i < n; i++)
        std::cout << bits[i];
    std::cout << '\n';
}

#endif
