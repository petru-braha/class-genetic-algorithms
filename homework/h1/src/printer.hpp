#ifndef _0PRINTER0_
#define _0PRINTER0_

#include <iostream>
#include "function.hpp"

//------------------------------------------------
// methods:

void print_analysis_header(const function& f, unsigned char dimension, 
    improvement improvement_type, std::ostream& out = std::cout)
{
    out << "function: id " << f.get_id() << ", ";
    out << (int)dimension << "-dimensional, using ";
    switch (improvement_type)
    {
    case improvement::best:
        out << "best ";
        break;
    case improvement::first:
        out << "first ";
        break;
    default:
        out << "worst ";
        break;
    }

    out << "improvement.\n\n";
}

void print_iteration(unsigned int index, std::ostream& out = std::cout)
{
    if (0 == index % 100)
        out << index << "iterations.\n";
}

//------------------------------------------------
// classes:
/*
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
*/

#endif
