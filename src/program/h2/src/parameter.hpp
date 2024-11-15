#ifndef _0PARAMETER0_
#define _0PARAMETER0_

#include <pservice_base>
#include "constant.hpp"

STD_PSERVICE_BEGIN

typedef double (*fct_ptr)(const double* const numbers,
	const size_t dimension);

struct parameter
{
	static objective_type objective;
	static int precision;
	static int dimension;
	static double mutation_probability;
	static double creaxion_probability; // cross-over rate
	static fct_ptr fitness_function;

	static constexpr double poor_value()
	{
		return (objective == objective_type::maximum_point ?
			-1 : 1) * std::numeric_limits<double>::infinity();
	}

	static bool is_better(double candidate, double current)
	{
		if (objective_type::minimum_point == objective)
		{
			if (candidate < current)
				return true;
			return false;
		}

		if (candidate > current) // maximum_point
			return true;
		return false;
	}
};

STD_PSERVICE_END
#endif
