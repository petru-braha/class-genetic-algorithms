#ifndef _0DE_JONG_10_
#define _0DE_JONG_10_

#include <cmath>
#include "../dependencies/function.hpp"
#include "../dependencies/value.hpp"

struct de_jong_1 : public function
{
    static const double minimum;
    static const double maximum;
    static double exe(unsigned char) noexcept;
};

const double de_jong_1::minimum = -5.12;
const double de_jong_1::maximum =  5.12;

double de_jong_1::exe(unsigned char n)
{
    double s = 0;
    value x(minimum, maximum, n);
    for(unsigned char i = 0; i < n; i++)
        s += x[i]*x[i];
    
    return s;
}

#endif
