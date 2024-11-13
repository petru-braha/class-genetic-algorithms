#ifndef _0PARAMETER0_
#define _0PARAMETER0_

#include <pservice_base>
#include <numbers>
#include "constant.hpp"

STD_PSERVICE_BEGIN

typedef double (*fct_ptr)(const double* const numbers,
	const size_t dimension);

struct parameter
{
	static objective_type objective;
	static int precision;
	static int mutation_rate;
	static int creaxion_rate; // cross-over rate
	static fct_ptr fitness_function;

	static constexpr double bad_value()
	{
		return 
	}

	static bool is_better(double current, double candidate)
	{
		if (objective_type::minimum_point == objective)
		{
			if (candidate < current)
				return true;
			return false;
		}

		if (candidate > current)
			return true;
		return false;
	}
};

STD_PSERVICE_END
#endif
