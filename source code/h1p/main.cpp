#include <iostream>
#include <cmath>
#include "bitstring.hpp"

using namespace pservice;

static long double f(long double number)
{
	return pow(number, 3) - 60 * pow(number, 2) + 900 * number + 100;
}

long double convert(const bitstring& b)
{
	size_t index_frst_bit = 0;
	size_t index_last_bit = 5;

	long double value = 0;
	for (size_t index_bit = index_frst_bit; index_bit < index_last_bit; index_bit++)
	{
		value *= 2;
		value += b[index_bit];
	}

	return value;
}

int main()
{
	bitstring b(5);
	long double number = convert(b);
	b.print(); std::cout << number << ' ' << f(number) << "\n\n";

	for (size_t i = 0; i < 5; i++)
	{
		b[i] = !b[i];

		number = convert(b);
		b.print(); std::cout << number << ' ' << f(number) << '\n';

		b[i] = !b[i];
	}

	return 0;
}
