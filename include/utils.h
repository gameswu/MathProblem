#pragma once

#include <numeric>

// 分数结构体
template <typename T>
struct Fraction
{
    T numerator;
    T denominator;

    void simplify()
    {
        T gcd = std::gcd(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;
    }
};

template <typename T>
Fraction<T> operator+(const Fraction<T> &lhs, const Fraction<T> &rhs)
{
    Fraction<T> res;
    res.numerator = lhs.numerator * rhs.denominator + rhs.numerator * lhs.denominator;
    res.denominator = lhs.denominator * rhs.denominator;
    res.simplify();
    return res;
}

template <typename T>
Fraction<T> operator-(const Fraction<T> &lhs, const Fraction<T> &rhs)
{
    Fraction<T> res;
    res.numerator = lhs.numerator * rhs.denominator - rhs.numerator * lhs.denominator;
    res.denominator = lhs.denominator * rhs.denominator;
    res.simplify();
    return res;
}

template <typename T>
Fraction<T> operator*(const Fraction<T> &lhs, const Fraction<T> &rhs)
{
    Fraction<T> res;
    res.numerator = lhs.numerator * rhs.numerator;
    res.denominator = lhs.denominator * rhs.denominator;
    res.simplify();
    return res;
}

template <typename T>
Fraction<T> operator/(const Fraction<T> &lhs, const Fraction<T> &rhs)
{
    Fraction<T> res;
    res.numerator = lhs.numerator * rhs.denominator;
    res.denominator = lhs.denominator * rhs.numerator;
    res.simplify();
    return res;
}