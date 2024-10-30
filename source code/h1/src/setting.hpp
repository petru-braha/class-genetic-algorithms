#ifndef _0SETTING0_
#define _0SETTING0_

#include "constant.hpp"

struct setting
{
	static objective_type objective;
	static int precision;

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

objective_type setting::objective = objective_type::minimum_point;
int setting::precision = 0;

#endif
