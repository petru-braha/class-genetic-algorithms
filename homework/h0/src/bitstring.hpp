#ifndef _0BITSTRING0_
#define _0BITSTRING0_

#include <ostream>
#include <vector>
#include <array>

#include "constant.hpp"
#define DOUBLE_BIAS 1023
#define DOUBLE_BITS 64
#define DBINGR_BITS 11
#define DBFRAC_BITS DOUBLE_BITS - DBINGR_BITS - 1
#define UNDEF 2

//------------------------------------------------
// methods:

void normalize(double& number)
{
    number = (double)((long long)(number * TO_PRECISION)) / TO_PRECISION;
}

//------------------------------------------------
// class:

class bitstring // [index_int, index_frac)
{
public:
    // typedefs:
    typedef unsigned char bit;

    // constructors:
    bitstring(double);
    bitstring(const bitstring&);

    // specific methods:
    bit& operator [] (unsigned char);
    bitstring& negation(unsigned char);
    double convert();

    // constant methods:
    unsigned char get_size() const;
    std::vector<bit> get_bits() const;
    const std::array<bit, DBINGR_BITS>& get_integral() const;
    const std::array<bit, DBFRAC_BITS>& get_fractional() const;
    void dev_print() const;

    // friend functions:
    friend std::ostream& operator << (std::ostream&, const bitstring&);

private:
    // data members:
    static const bit undefined;
    unsigned char index_int, index_frc;

    bit sign_bit;
    std::array<bit, DBINGR_BITS> integral_part;
    std::array<bit, DBFRAC_BITS> fractional_part;

    // auxiliar utility:
    void insert_integral(long long&);
    void insert_fraction(double&);
};

//------------------------------------------------
// constructors:

const bitstring::bit bitstring::undefined = UNDEF;

bitstring::bitstring(double number) :
    index_int(DBINGR_BITS), index_frc(0),
    sign_bit(number < 0 ? 1 : 0)
{
    if (number < 0)
        number *= -1; 
    normalize(number);

    // insert
    long long integral = (long long)number;
    insert_integral(integral);
    insert_fraction(number);

    // scientific notation
    const unsigned char index_bit = DBINGR_BITS - 1;
    long long shifts = 0;
    
    // left shift
    while (index_bit > index_int)
    {
        // shift frac
        for (unsigned char i = DBFRAC_BITS - 1; i; i--)
            fractional_part[i] = fractional_part[i - 1];
        
        fractional_part[0] = integral_part[index_bit];
        
        // shift intg
        for (unsigned char i = index_bit; i > index_int; i--)
            integral_part[i] = integral_part[i - 1];
        
        integral_part[index_int] = undefined;
        index_int++;
        shifts++;
    }
    
    // right shift
    if (DBINGR_BITS == index_int)
    {
        while (0 == fractional_part[0])
        {
            for (unsigned char i = 0; i + 1 < index_frc; i++)
                fractional_part[i] = fractional_part[i + 1];
            
            index_frc--;
            fractional_part[index_frc] = undefined;
            shifts--;
        }
            
        integral_part[--index_int] = fractional_part[0];
        for (unsigned char i = 0; i + 1 < index_frc; i++)
            fractional_part[i] = fractional_part[i + 1];
        
        index_frc--;
        fractional_part[index_frc] = undefined;
        shifts--;
    }

    long long exponent = DOUBLE_BIAS + shifts;
    insert_integral(exponent);
}

bitstring::bitstring(const bitstring& str) :
    index_int(str.index_int), index_frc(str.index_frc),
    sign_bit(str.sign_bit), integral_part(str.integral_part), 
    fractional_part(str.fractional_part) {}

//------------------------------------------------
// specific methods:

bitstring::bit& bitstring::operator [] (unsigned char index)
{
    if (index >= this->get_size()); // error
    
    index += index_int;
    if (index >= DBINGR_BITS)
    {
        index -= DBINGR_BITS;
        return fractional_part[index];
    }

    return integral_part[index];
}

bitstring& bitstring::negation(unsigned char index)
{
    auto intg(integral_part);
    auto frac(fractional_part);
    
    bit& ref = this->operator[](index);
    bit value = ref;
    ref = value == 0 ? 1 : 0;
    return *this;
}

double bitstring::convert()
{
    // fraction
    double fraction = 1.0;
    double temp = 1.0;

    for (unsigned char index_bit = 0; index_bit < index_frc; index_bit++)
    {
        temp /= 2;

        bit b = fractional_part[index_bit];
        fraction += (b * temp);
    }

    // exponent
    long long exponent = 0;
    long long power = 1;

    for (unsigned char index_bit = DBINGR_BITS - 1;; index_bit--)
    {
        bit b = integral_part[index_bit];
        exponent += b * power;
        power *= 2;
        if (index_bit == index_int)
            break;
    }
    
    // multiplication
    double multiplier = 1;
    exponent -= DOUBLE_BIAS;

    while (exponent > 0)
    {
        multiplier *= 2;
        exponent--;
    }

    while (exponent < 0)
    {
        multiplier /= 2;
        exponent++;
    }

    fraction *= multiplier; 
    fraction *= sign_bit == 1 ? -1 : 1;
    return fraction;
}

//------------------------------------------------
// constant methods:

unsigned char bitstring::get_size() const
{
    return (DBINGR_BITS - index_int) + index_frc;
}

std::vector<bitstring::bit> bitstring::get_bits() const
{
    std::vector<bit> ret(this->get_size());
    
    unsigned char index_bit = index_int;
    
    for (; index_bit < DBINGR_BITS; index_bit++)
        ret[index_bit - index_int] = integral_part[index_bit];

    unsigned char offset = DBINGR_BITS - index_bit;
    index_bit = 0;
    for (; index_bit < index_frc; index_bit++)
        ret[index_bit + offset] = fractional_part[index_bit];
    
    return ret;
}

const std::array<bitstring::bit, DBINGR_BITS>& bitstring::get_integral() const
{
    return this->integral_part;
}

const std::array<bitstring::bit, DBFRAC_BITS>& bitstring::get_fractional() const
{
    return this->fractional_part;
}

void bitstring::dev_print() const
{
    std::cout << (int)sign_bit << '-';
    for (unsigned char i = 0; i < DBINGR_BITS; i++)
        std::cout << (int)integral_part[i];
    std::cout << '-';
    for (unsigned char i = 0; i < DBFRAC_BITS; i++)
        std::cout << (int)fractional_part[i];
    std::cout << ' ';
}

//------------------------------------------------
// friend functions:

std::ostream& operator << (std::ostream& out, const bitstring& str)
{
    if (1 == str.sign_bit)
        out << '-';
    for(unsigned char index_bit = str.index_int; index_bit < DBINGR_BITS; index_bit++)
        out << (int)str.integral_part[index_bit];
    
    if (0 == str.index_frc)
        return out;

    out << '.';
    for (unsigned char index_bit = 0; index_bit < str.index_frc; index_bit++)
        out << (int)str.fractional_part[index_bit];

    return out;
}

//------------------------------------------------
// auxiliar utility:

void bitstring::insert_integral(long long& number)
{
    index_int = DBINGR_BITS;
    integral_part.fill(undefined);

    while (number && index_int)
    {
        index_int--;

        bit remainder = number % 2;
        number /= 2;
        integral_part[index_int] = remainder;
    }
}

void bitstring::insert_fraction(double& number)
{
    index_frc = 0;
    fractional_part.fill(undefined);
    
    number -= (long long)number;
    while (1.0 != number && index_frc < DBFRAC_BITS)
    {
        bit b = 0;

        number *= 2;
        if (number >= 1.0)
        {
            b = 1;
            number -= 1.0;
        }

        fractional_part[index_frc] = b;
        index_frc++;
    }
}

#endif
