#ifndef _0BITSTRING0_
#define _0BITSTRING0_

#include <stdlib.h>
#include <utility>
#include <thread>
#include <random>
#include <time.h> 
#include "constant.hpp"

#include <vector>

//------------------------------------------------
// methods:

class random_generator
{
    std::mt19937 generator;

public:
    inline random_generator() {
        std::mt19937 random_seed;
        random_seed.seed(time(0) + clock() * 1000 + 10000 *
            std::hash<std::thread::id>{}(std::this_thread::get_id()));
        random_seed.discard(31337);

        generator.seed(random_seed());
    }

    inline unsigned int operator () () { return generator(); }
};

//------------------------------------------------
// class:

class bitstring
{
    std::vector<bool> bits;

public:
    // constructors:
    ~bitstring() = default;
    bitstring(const size_t&);
    
    // specific methods:
    double convert() const;
    
    // specific methods:
    bool operator [] (const size_t&) const;
    size_t size() const;
    void  print() const;
};

//------------------------------------------------
// constructors:

bitstring::bitstring(const size_t& N) : bits(N)
{
    random_generator g;
    for (size_t i = 0; i < N; i++)
        bits[i] = g() % 2;
    // consider minimum, maximum, precision
}

//------------------------------------------------
// constant methods

bool bitstring::operator [] (const size_t& index) const
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
