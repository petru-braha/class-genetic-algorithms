#include <iostream>
#include <limits>

void t_infinity() 
{
	std::cout << std::numeric_limits<double>::max() << '\n'
			<< std::numeric_limits<double>::infinity() << '\n';
	
	double var = std::numeric_limits<double>::infinity() * -1;
	std::cout << var;

	exit(EXIT_SUCCESS);
}
