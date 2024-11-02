#include <iostream>
#include <cmath>

static long double f(long double number)
{
	return pow(number, 3) - 60 * pow(number, 2) + 900 * number + 100;
}

int main()
{
	std::cout << f(14);
	return 0;
}
