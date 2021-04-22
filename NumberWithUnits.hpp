#pragma once

#include <fstream>
#include <string>
#include <map>

namespace ariel
{
    class NumberWithUnits
    {
        double amount;
        std::string name;

    public:
        static std::map<std::string, std::map<std::string, double>> myUnits;
        NumberWithUnits(double, const std::string&);
        static void read_units(std::ifstream &);

        //Compare operation
        bool operator==(const NumberWithUnits &u) const;
        bool operator!=(const NumberWithUnits &u) const;
        bool operator>(const NumberWithUnits &u) const;
        bool operator>=(const NumberWithUnits &u) const;
        bool operator<(const NumberWithUnits &u) const;
        bool operator<=(const NumberWithUnits &u) const;

        NumberWithUnits &operator+=(const NumberWithUnits &u);
        NumberWithUnits &operator-=(const NumberWithUnits &u);

        NumberWithUnits &operator++();         // prefix  ++a
        NumberWithUnits operator++(int); // postfix a++
        NumberWithUnits &operator--();         // prefix  --a
        NumberWithUnits operator--(int); // postfix a--

        //Plus/Minus operation
        friend NumberWithUnits operator+(const NumberWithUnits &u1, const NumberWithUnits &u2);
        friend NumberWithUnits operator-(const NumberWithUnits &u1, const NumberWithUnits &u2);

        //Mul operation
        friend NumberWithUnits operator*(const double d, const NumberWithUnits &u1);
        friend NumberWithUnits operator*(const NumberWithUnits &u1, const double d);

        //Unary operation
        friend NumberWithUnits operator+(const NumberWithUnits &u1);
        friend NumberWithUnits operator-(const NumberWithUnits &u1);

        //Input/Output operation
        friend std::ostream &operator<<(std::ostream &os, const NumberWithUnits &u);
        friend std::istream &operator>>(std::istream &is, NumberWithUnits &u);
    };
}