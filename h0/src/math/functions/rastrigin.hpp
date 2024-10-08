#ifndef _0RASTRIN0_
#define _0RASTRIN0_

#include <cmath>
#include "../dependencies/function.hpp"
#include "../dependencies/value.hpp"

struct rastrigin : public function
{
    static const double minimum;
    static const double maximum;
    static double exe(unsigned char) noexcept;
};

const double rastrigin::minimum = -5.12;
const double rastrigin::maximum =  5.12;

double rastrigin::exe(unsigned char n) noexcept
{
    double s = 0.0;
    value x(minimum, maximum, n);

    for(unsigned i = 0; i < n; i++)
        s = s + (x[i]*x[i] - 10*cos(2*PI * x[i]));

    return 10*n + s;
}

#endif
