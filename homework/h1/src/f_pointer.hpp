#ifndef _0FUNCTION_POINTER0_
#define _0FUNCTION_POINTER0_

#include <cmath>
#include <vector>

#include "constant.hpp"

// fctptr_ == function pointer

double fctptr_dejong1(const std::vector<double>& x)
{
    double s = 0;
    for(size_t i = 0; i < x.size(); i++)
        s += x[i] * x[i];
    
    return s;
}

double fctptr_michalewicz(const std::vector<double>& x)
{
    const int m = 10;
    double s = 0;

    for(size_t i = 0; i < x.size(); i++)
        s = s + sin(x[i]) * pow( (sin( i * x[i] * x[i] / PI )), (2 * m));
    
    return -s;
}

double fctptr_rastrigin(const std::vector<double>& x)
{
    double s = 0.0;

    for(unsigned char i = 0; i < x.size(); i++)
        s = s + (x[i]*x[i] - 10*cos(2*PI * x[i]));

    return 10 * x.size() + s;
}

double fctptr_schwefel(const std::vector<double>& x)
{
    double s = 0;
    for(unsigned char i = 0; i < x.size(); i++)
        s += (-x[i] * sin(sqrt(abs(x[i]))));
    
    return s + 418.9829 * x.size();
}

#endif
