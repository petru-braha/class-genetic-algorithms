#ifndef _0PRINTER0_
#define _0PRINTER0_

#include <iostream>

//------------------------------------------------
// methods:

void print_available_functions()
{
	std::cout << "0. de_jong_1\n"
		<< "1. michalewicz\n"
		<< "2. rastrigin\n"
		<< "3. schwefel\n\n";
}


//------------------------------------------------
// classes:

class printer
{
public:
	~printer() = default;
	printer() = default;
	printer(const char*);
};

class proposition : public printer
{
public:
	proposition() = delete;
	proposition(const char*);
};

class file_printer : public printer
{
	//std::ofstream file;

public:
	// constructors:
	file_printer() = delete;
	file_printer(const char*);
};

#endif
