#ifndef _0FUNCTION_POINTER0_
#define _0FUNCTION_POINTER0_

#include <cmath>
#include "constant.hpp"
#include "value.hpp"

// fctptr_ - function pointer

double fctptr_dejong1(const double& minimum, const double& maximum, unsigned char n)
{
    double s = 0;
    value x(minimum, maximum, n);
    for(unsigned char i = 0; i < n; i++)
        s += x[i]*x[i];
    
    return s;
}

double fctptr_michalewicz(const double& minimum, const double& maximum, unsigned char n)
{
    const int m = 10;
    double s = 0;
    value x(minimum, maximum, n);

    for(unsigned char i = 0; i < n; i++)
        s = s + sin(x[i]) * pow( (sin( i * x[i] * x[i] / PI )), (2 * m));
    
    return -s;
}

double fctptr_rastrigin(const double& minimum, const double& maximum, unsigned char n)
{
    double s = 0.0;
    value x(minimum, maximum, n);

    for(unsigned char i = 0; i < n; i++)
        s = s + (x[i]*x[i] - 10*cos(2*PI * x[i]));

    return 10*n + s;
}

double fctptr_schwefel(const double& minimum, const double& maximum, unsigned char n)
{
    double s = 0;
    value x(minimum, maximum, n);
    for(unsigned char i = 0; i < n; i++)
        s += (-x[i] * sin(sqrt(abs(x[i]))));
    
    return s + 418.9829*n;
}

#endif
