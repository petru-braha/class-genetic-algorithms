#ifndef _0SCHWEFEL0_
#define _0SCHWEFEL0_

#include <cmath>
#include "../dependencies/function.hpp"
#include "../dependencies/value.hpp"

struct schwefel : public function
{
    static const double minimum;
    static const double maximum;
    static double exe(unsigned char) noexcept;
};

const double schwefel::minimum = 500.0;
const double schwefel::maximum = 500.0;

double schwefel::exe(unsigned char n)
{
    double s = 0;
    value x(minimum, maximum, n);
    for(unsigned i = 0; i < n; i++)
        s += (-x[i] * sin(sqrt(abs(x[i]))));
    
    return s + 418.9829*n;
}

#endif
