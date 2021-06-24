#pragma once

#include <cstdint>
#include <iostream>

class number_t {
private:
    long long _n1{0};
public:
    //Ко{}нструкторы (пустой, копирования, от числа)
    number_t(const number_t&);// copy constr
    number_t(long long _n1 = 0);// creat number_t
    //template<typename T> number_t(T _n1);
    //Оператор присвоения
    number_t& operator=(const number_t&);
    //number_t& operator=(const int64_t &);
    //Каст (`bool`, числу, `std::string`)
    explicit operator bool() const;
    explicit operator int64_t() const;
    explicit operator std::string() const;

    //Бинарные арифметические операторы
    friend number_t operator+(number_t , const number_t& right);
    friend number_t operator-(number_t, const number_t& right);
    friend number_t operator*(number_t, const number_t& right);
    friend number_t operator/(number_t, const number_t& right);
    friend number_t operator %(number_t, const number_t& right);

    number_t& operator+=(const number_t& right);
    number_t& operator-=(const number_t& right);
    number_t& operator*=(const number_t& right);
    number_t& operator/=(const number_t& right);
    number_t& operator%=(const number_t& right);


    //битовые операторы
    friend number_t operator^(number_t , const number_t& right);
    friend number_t operator&(number_t , const number_t& right);
    friend number_t operator|(number_t , const number_t& right);
    friend number_t operator>>(number_t , const number_t& right);
    friend number_t operator << (number_t , const number_t& );


    number_t& operator^=(const number_t& right);
    number_t& operator&=(const number_t& right);
    number_t& operator|=(const number_t& right);
    number_t& operator<<=(const number_t& right);
    number_t& operator>>=(const number_t& right);



    //Операторы вывода в поток и ввода из потока
    friend std::ostream& operator<< (std::ostream&, const number_t&);
    friend std::istream& operator>> (std::istream&, number_t&);

    //Унарные операторы
    number_t operator-() const;
    number_t operator+() const;
    number_t operator!() const;
    number_t operator~() const;

    //Операторы инкремента и декремента
    number_t operator++(int);
    number_t operator--(int);
    number_t& operator++();
    number_t& operator--();

    //Операторы сравнения
    friend bool operator > (const number_t &, const number_t &);
    friend bool operator <= (const number_t &, const number_t &);

    friend bool operator < (const number_t &, const number_t &);
    friend bool operator >= (const number_t &, const number_t &);

    friend bool  operator == (const number_t&,const number_t&);
    friend bool  operator != (const number_t &,const number_t &);

};
