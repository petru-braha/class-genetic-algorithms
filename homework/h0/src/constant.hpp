#ifndef _0CONSTANT0_
#define _0CONSTANT0_

#define SAMPLE_NUMBER 30

#define PRECISION 5
#define PI 3.14159

enum class problem_requirement // not now
{
    minimum_point, maximum_point
};

enum class improvement
{
    best, first, worst
};

enum class solution
{
    best, average, worst
};

typedef double (*fct_ptr)(const double&, const double&, unsigned char);
typedef unsigned long long int ull;
typedef double nr;

#endif
