#include <iostream>
#include <algorithm> 
#include "Fraction.h"

Fraction::Fraction(int counter, int denominator) {
    this->counter = counter;
    this->denominator = denominator;
    reduce();
}

Fraction::Fraction(double value, int maxdenom) {
    this->counter = (int) (value * maxdenom);
    this->denominator = maxdenom;
}

Fraction Fraction::operator+(Fraction other) {
    return Fraction(counter * other.denominator + other.counter * denominator,
            denominator * other.denominator);
}

Fraction Fraction::operator+=(Fraction other) {
    counter = counter * other.denominator + other.counter * denominator;
    denominator = denominator * other.denominator;
    return *this;
}

Fraction Fraction::operator-(Fraction other) {
    return Fraction(counter * other.denominator - other.counter * denominator,
            denominator * other.denominator);
}

Fraction Fraction::operator-=(Fraction other) {
    counter = counter * other.denominator - other.counter * denominator;
    denominator = denominator * other.denominator;
    return *this;
}

Fraction Fraction::operator*(Fraction other) {
    return Fraction(counter * other.counter, denominator * other.denominator);
}

Fraction Fraction::operator*=(Fraction other) {
    counter = counter * other.counter;
    denominator = denominator * other.denominator;
    return *this;
}

Fraction Fraction::operator/(Fraction other) {
    return Fraction(counter * other.denominator, denominator * other.counter);
}

Fraction Fraction::operator/=(Fraction other) {
    counter = counter * other.denominator;
    denominator = denominator * other.counter;
    return *this;
}

bool Fraction::operator==(Fraction other) {
    if (counter == other.counter && denominator == other.denominator) {
        return true;
    }
    return false;
}

Fraction::operator double() const {
    return 1.0 * counter / denominator;
}

void Fraction::reduce() {
    int gcdv = gcd(counter, denominator);
    if (gcd != 0) {
        counter /= gcdv;
        denominator /= gcdv;
    }
    if (denominator < 0) {
        counter *= -1;
        denominator *= -1;
    }
}

int Fraction::gcd(int a, int b) {
    while (b != 0) {
        int rest = a % b;
        a = b;
        b = rest;
    }
    return a;
}

void operator<<(std::ostream &stream, Fraction fract) {

    stream << "(" << fract.GetCounter() << "," << fract.GetDenominator() << ")";


}

//void operator >>(istream &stream, Fraction fract) {
//    stream >> fract.GetCounter() >> fract.GetDenominator();
//}
