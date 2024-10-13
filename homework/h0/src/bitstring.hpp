#ifndef _0BITSTRING0_
#define _0BITSTRING0_

#include <ostream>

class bitstring
{
    // data members:
    std::vector<bool> integral_part;
    std::vector<bool> fractional_part;

public:
    // constructors:
    bitstring(double);
    bitstring(const std::vector<bool>&, const std::vector<bool>&);

    // specific methods:
    bitstring negation(unsigned char) const;
    double convert() const;

    // constant methods:
    const unsigned char& get_size() const;
    const std::vector<bool>& get_bits() const;
    const std::vector<bool>& get_integral() const;
    const std::vector<bool>& get_fractional() const;

    // friend functions:
    friend std::ostream& operator << (std::ostream&, const bitstring&);
};

//------------------------------------------------
// constructors:

bitstring::bitstring(double number) :
    integral_part(15), fractional_part(10)
{
    // integral part
    long long integral = (long long)number;
    while (integral)
    {
        bool remainder = integral % 2;
        integral /= 2;
        integral_part.insert(integral_part.begin(), remainder);
    }

    number -= integral;
    if (0.0 == number)
        return;

    while (1.0 != number)
    {
        bool bit = false;

        number *= 2;
        if (number >= 1.0)
        {
            bit = true;
            number -= 1.0;
        }

        fractional_part.insert(fractional_part.begin(), bit);
    }
}

bitstring::bitstring(const std::vector<bool>& i, const std::vector<bool>& f) :
    integral_part(i), fractional_part(f) {}

//------------------------------------------------
// specific methods:

bitstring bitstring::negation(unsigned char index) const
{
    if (index >= this->get_size()); //error
    
    std::vector<bool> intg(integral_part), frac(fractional_part);

    if (index >= integral_part.size())
        frac[index] = !frac[index];
    else
        intg[index] = !intg[index];

    return { intg, frac };
}

double bitstring::convert() const
{
    long long integral = 0;
    long long power = 1;

    for (unsigned char index_bit = integral_part.size() - 1;; index_bit--)
    {
        integral += integral_part.at(index_bit) * power;
        power *= 2;
        if (0 == index_bit)
            break;
    }

    double fraction = 1.0;
    for (unsigned char index_bit = 0;;);

    return fraction + integral;
}

//------------------------------------------------
// constant methods:

const unsigned char& bitstring::get_size() const
{
    return integral_part.size() + fractional_part.size();
}

const std::vector<bool>& bitstring::get_bits() const
{
    std::vector<bool> ret(integral_part.size() + fractional_part.size());
    for (bool bit : integral_part)
        ret.emplace_back(bit);
    for (bool bit : fractional_part)
        ret.emplace_back(bit);
    
    return ret;
}

const std::vector<bool>& bitstring::get_integral() const
{
    return this->integral_part;
}

const std::vector<bool>& bitstring::get_fractional() const
{
    return this->fractional_part;
}

std::ostream& operator << (std::ostream& out, const bitstring& str)
{
    for (const bool& bit : str.get_integral())
        out << bit;
    out << '.';
    for (const bool& bit : str.get_fractional())
        out << bit;
    return out;

}

#endif
