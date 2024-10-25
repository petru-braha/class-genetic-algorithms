#ifndef _0SETTING0_
#define _0SETTING0_

#include "constant.hpp"

struct setting
{
	static objective_type objective;
	static unsigned char precision;

	static bool change(double& current, double candidate)
	{
		if (objective_type::minimum_point == objective)
		{
			if (candidate < current)
			{
				current = candidate;
				return true;
			}

			return false;
		}

		if (candidate > current)
		{
			current = candidate;
			return true;
		}

		return false;
	}

	// special use!
	static bool change(double current, double candidate, double& worst)
	{
		if (objective_type::minimum_point == objective)
		{
			if (candidate < current && worst < candidate)
			{
				worst = candidate;
				return true;
			}

			return false;
		}

		if (candidate > current && worst > candidate)
		{
			worst = candidate;
			return true;
		}

		return false;
	}
};

#endif
