#include "NumberWithUnits.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <iostream>
using namespace std;

namespace ariel
{
    map<string, map<string, double>> NumberWithUnits::myUnits;
    void NumberWithUnits::read_units(ifstream &file)
    {
        if (file)
        {
            string u;
            while (getline(file, u))
            {
                string parent = " ";
                string operatorE = " ";
                string child = " ";
                double one = 1;
                double number = 1;
                istringstream(u) >> skipws >> one >> parent >> operatorE >> number >> child;
                if (myUnits.count(parent) == 0)
                {
                    myUnits.insert({parent, map<string, double>{}});
                }
                if (myUnits.count(child) == 0)
                {
                    myUnits.insert({child, map<string, double>{}});
                }

                for (auto const &elem : myUnits.at(parent))
                {
                    myUnits.at(child).insert({elem.first, elem.second / number});
                    myUnits.at(elem.first).insert({child, number / elem.second});
                }

                for (auto const &elem : myUnits.at(child))
                {
                    myUnits.at(parent).insert({elem.first, elem.second * number});
                    myUnits.at(elem.first).insert({parent, 1 / (number * elem.second)});
                }

                myUnits.at(parent).insert({child, number});
                myUnits.at(child).insert({parent, 1 / number});
            }
        }
        else
        {
            throw string("no such file");
        }
    }

    NumberWithUnits::NumberWithUnits(double a, const string &n) : amount(a), name(n)
    {
        if (myUnits.count(n) == 0)
        {
            throw invalid_argument("illigal type");
        }
    }

    bool sameType(const string &a, const string &b)
    {
        return (NumberWithUnits::myUnits.at(a).count(b) != 0) && (NumberWithUnits::myUnits.at(b).count(a) != 0);
    }

    //Compare operation
    bool NumberWithUnits::operator==(const NumberWithUnits &u) const
    {
        const float EPS =0.0001;
        
        if (name == u.name)
        {
            return abs(amount - u.amount) <= EPS;
        }
        if (!sameType(name, u.name))
        {
            throw invalid_argument("Not Same Type");
        }

        return abs((myUnits.at(name).at(u.name) * amount) - u.amount) <= EPS;
    }

    bool NumberWithUnits::operator!=(const NumberWithUnits &u) const
    {
        return !this->operator==(u);
    }

    bool NumberWithUnits::operator>(const NumberWithUnits &u) const
    {
        if (name == u.name)
        {
            return amount > u.amount;
        }
        if (!sameType(name, u.name))
        {
            throw invalid_argument("Not Same Type");
        }

        return myUnits.at(name).at(u.name) * amount > u.amount;
    }

    bool NumberWithUnits::operator<(const NumberWithUnits &u) const
    {
        if (name == u.name)
        {
            return amount < u.amount;
        }
        if (!sameType(name, u.name))
        {
            throw invalid_argument("Not Same Type");
        }

        return myUnits.at(name).at(u.name) * amount < u.amount;
    }

    bool NumberWithUnits::operator>=(const NumberWithUnits &u) const
    {
        return !this->operator<(u);
    }

    bool NumberWithUnits::operator<=(const NumberWithUnits &u) const
    {
        return !this->operator>(u);
    }

    // += / -= operation
    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &u)
    {
        if (name == u.name)
        {
            amount += u.amount;
            return *this;
        }
        if (!sameType(name, u.name))
        {
            throw invalid_argument("Not Same Type");
        }

        amount += myUnits.at(u.name).at(name) * u.amount;
        return *this;
    }

    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &u)
    {
        if (name == u.name)
        {
            amount -= u.amount;
            return *this;
        }
        if (!sameType(name, u.name))
        {
            throw invalid_argument("Not Same Type");
        }

        amount -= myUnits.at(u.name).at(name) * u.amount;
        return *this;
    }

    // prefix  ++a
    NumberWithUnits &NumberWithUnits::operator++()
    {
        amount++;
        return *this;
    }

    // postfix a++
    NumberWithUnits NumberWithUnits::operator++(int)
    {
        NumberWithUnits before(amount, name);
        amount++;
        return before;
    }

    // prefix  --a
    NumberWithUnits &NumberWithUnits::operator--()
    {
        amount--;
        return *this;
    }

    // postfix a--
    NumberWithUnits NumberWithUnits::operator--(int)
    {
        NumberWithUnits before(amount, name);
        amount--;
        return before;
    }

    //Plus/Minus operation
    NumberWithUnits operator+(const NumberWithUnits &u1, const NumberWithUnits &u2)
    {
        if (u1.name == u2.name)
        {
            double tempAmount = u1.amount + u2.amount;
            return NumberWithUnits{tempAmount, u1.name};
        }
        if (!sameType(u1.name, u2.name))
        {
            throw invalid_argument("Not Same Type");
        }

        double tempAmount = u1.amount + NumberWithUnits::myUnits.at(u2.name).at(u1.name) * u2.amount;
        return NumberWithUnits{tempAmount, u1.name};
    }

    NumberWithUnits operator-(const NumberWithUnits &u1, const NumberWithUnits &u2)
    {
        if (u1.name == u2.name)
        {
            double tempAmount = u1.amount - u2.amount;
            return NumberWithUnits{tempAmount, u1.name};
        }
        if (!sameType(u1.name, u2.name))
        {
            throw invalid_argument("Not Same Type");
        }

        double tempAmount = u1.amount - NumberWithUnits::myUnits.at(u2.name).at(u1.name) * u2.amount;
        return NumberWithUnits{tempAmount, u1.name};
    }

    //Mul operation
    NumberWithUnits operator*(const double d, const NumberWithUnits &u1)
    {
        return NumberWithUnits(d * u1.amount, u1.name);
    }
    NumberWithUnits operator*(const NumberWithUnits &u1, const double d)
    {
        return NumberWithUnits(d * u1.amount, u1.name);
    }

    //Unary operation
    NumberWithUnits operator+(const NumberWithUnits &u1)
    {
        return NumberWithUnits(u1.amount, u1.name);
    }
    NumberWithUnits operator-(const NumberWithUnits &u1)
    {
        return NumberWithUnits(-u1.amount, u1.name);
    }

    //Input/Output operation
    std::ostream &operator<<(std::ostream &os, const NumberWithUnits &u)
    {
        return os << (u.amount) << "[" << u.name << "]";
    }
    std::istream &operator>>(std::istream &is, NumberWithUnits &u)
    {
        char sign1 = ' ';
        char sign2 = ' ';
        string tempName = " ";
        double tempAmount = 0;
        is >> skipws >> tempAmount >> sign1 >> tempName;
        if (tempName.at(tempName.length() - 1) != ']')
        {
            is >> sign2;
        }
        else
        {
            tempName = tempName.substr(0, tempName.length() - 1);
        }
        if (NumberWithUnits::myUnits.count(tempName) == 0)
        {
            throw invalid_argument("illigal type");
        }
        u.amount = tempAmount;
        u.name = tempName;
        return is;
    }
};
