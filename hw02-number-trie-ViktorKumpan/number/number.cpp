#include "number.h"
#include <iostream>
#include <limits>
#include <stdexcept>
#include <typeinfo>
#include <string>
#include <sstream>


number_t::number_t(const number_t &num)
        :_n1{num._n1}
{
}

number_t::number_t(long long n1)
        : _n1{static_cast<long long>(n1)}
{
}


number_t& number_t::operator = (const number_t & num) {
    if (this == &num)
        return *this;
    _n1 = num._n1;
    return  *this;
}

number_t::operator bool() const { return _n1;}

number_t::operator int64_t() const { return _n1; }

number_t::operator std::string() const {return std::to_string(_n1); }


number_t operator+(number_t right, const number_t &left) {
    return right._n1+=left._n1;
}


number_t operator-(number_t right, const number_t &left) {
    return right._n1-left._n1;
}

number_t operator*(number_t right, const number_t &left) {
    return right._n1*left._n1;
}

number_t operator/(number_t right,const number_t &left) {
    if (left._n1 == 0){
        throw std::domain_error{"you can't divide by zero"};
    }
    return right._n1/=left._n1;
}

number_t operator%(number_t right, const number_t &left) {
    return right._n1%=left._n1;
}

number_t& number_t::operator += (const number_t &right) {
    _n1 += right._n1;
    return *this;
}


number_t& number_t::operator-=(const number_t &right) {
    _n1 -= right._n1;
    return *this;
}

number_t& number_t::operator*=(const number_t &right) {
    _n1 *= right._n1;
    return *this;
}

number_t& number_t::operator/=(const number_t &right) {
    if (right._n1 == 0){
        throw std::domain_error{"you can't divide by zero"};
    }
    _n1 /= right._n1;
    return *this;
}

number_t& number_t::operator%=(const number_t &right) {
    _n1 %= right._n1;
    return *this;
}

std::ostream &operator<<(std::ostream & os, const number_t & num) {
    os << num._n1;
    return os;
}

std::istream &operator>>(std::istream & is, number_t & num) {
    is >> num._n1;
    return is;
}

number_t number_t::operator-() const{
    return (-_n1);
}

number_t number_t::operator+() const {
    return number_t(*this);
}

number_t number_t::operator!() const {
    return (_n1 == 0);
}

number_t number_t::operator~() const {
    return ~_n1;
}

number_t &number_t::operator++() {
    _n1++;
    return *this;
}

number_t number_t::operator++(int) {
    number_t temp = *this;
    ++*this;
    return temp;
}

number_t number_t::operator--(int) {
    number_t temp = *this;
    --(*this);
    return temp;
}

number_t &number_t::operator--() {
    _n1--;
    return *this;
}

bool operator>(const number_t &num1,const number_t & num2)  {
    return (num1._n1 > num2._n1);
}

bool operator<=(const number_t &num1,const number_t &num2)  {
    return (num1._n1 <= num2._n1);
}

bool operator<(const number_t &num1, const number_t &num2)  {
    return (num1._n1 < num2._n1);
}

bool operator>=(const number_t &num1, const number_t & num2)  {
    return (num1._n1 >= num2._n1);
}

bool  operator==(const number_t &num1,const number_t &num2)  {
    return (num1._n1 == num2._n1);
}

bool operator!=(const number_t &num1 ,const number_t &num2)  {
    return !(num1._n1 == num2._n1);
}




number_t operator^(number_t right,const number_t &left) {
    return right._n1^=left._n1;
}

number_t operator&(number_t right,const number_t &left) {
    return right._n1&=left._n1;
}

number_t operator|(number_t right,const number_t &left) {
    return right._n1|=left._n1;
}

number_t operator<<(number_t left, const number_t &right) {
    return left._n1<<=right._n1;
}

number_t operator>>(number_t left, const number_t &right) {
    return left._n1>>=right._n1;
}


number_t& number_t::operator<<=(const number_t &right) {
    _n1 <<= right._n1;
    return *this;
}

number_t& number_t::operator>>=(const number_t &right) {
    _n1 >>= right._n1;
    return *this;
}

number_t& number_t::operator^=(const number_t &right) {
    _n1 ^= right._n1;
    return *this;
}

number_t& number_t::operator&=(const number_t &right) {
    _n1 &= right._n1;
    return *this;
}

number_t& number_t::operator|=(const number_t &right) {
    _n1 |= right._n1;
    return *this;
}

