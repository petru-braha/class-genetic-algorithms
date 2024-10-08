#ifndef _0MICHAELWICZ0_
#define _0MICHAELWICZ0_

#include <cmath>
#include "../dependencies/function.hpp"
#include "../dependencies/value.hpp"

struct michalewicz : public function
{
    static const double minimum;
    static const double maximum;
    static double exe(unsigned char) noexcept;
};

const double michalewicz::minimum = 0;
const double michalewicz::maximum = PI;

double michalewicz::exe(unsigned char n) noexcept
{
    const int m = 10;
    double s = 0;
    value x(minimum, maximum, n);

    for(unsigned char i = 0; i < n; i++)
        s = s + sin(x[i]) * pow( (sin( i * x[i] * x[i] / PI )), (2 * m));
    
    return -s;
}

#endif
