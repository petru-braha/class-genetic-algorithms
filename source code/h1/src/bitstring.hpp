#ifndef _0BITSTRING0_
#define _0BITSTRING0_

#include <pservice_base>
#include <vector>

#include "constant.hpp"

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
    bitstring() = delete;
    bitstring(size_t);

    // constant methods:
    const bool& operator [] (const size_t index) const;
    bool& operator [] (const size_t);
    size_t size() const;
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
// constant methods:

const bool& bitstring::operator [] (const size_t index) const
{
    return bits[index];
}

bool& bitstring::operator [] (const size_t index)
{
    return (bool&)bits[index];
}

size_t bitstring::size() const
{
    return bits.size();
}

#endif
