#ifndef _0FUNCTION0_
#define _0FUNCTION0_

#define PI 3.14159

struct function
{
    static const double minimum;
    static const double maximum;
    static double exe();
};

const double function::minimum = 0.0;
const double function::maximum = 0.0;
double function::exe() {return 0.0;}

#endif
