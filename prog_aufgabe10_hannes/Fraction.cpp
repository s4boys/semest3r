#include <iostream>
#include <algorithm> 
#include "Fraction.h"
#define MAX_DEN 100

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

Fraction sternBrocot(double number) { // bekommt zahl, sucht Fraction im sternbrocot die der am nächsten ist
    Fraction leftFraction = (int) number; // bei pi dann 3
    Fraction rightFraction = ((int) number) + 1; // bei pi dann 4
    Fraction middleFraction = Fraction(leftFraction.GetCounter() + rightFraction.GetCounter(),
            leftFraction.GetDenominator() + rightFraction.GetDenominator()); //neuer, mittlerer bruch
    Fraction resultFraction = middleFraction;
    while (middleFraction.GetDenominator() < MAX_DEN) { // gewählte grenze
        if ((double) middleFraction > number) { // falls Ziel links von middle ist
            rightFraction = middleFraction; // neuer rechter bruch ist die alte mitte
        } else { // andersherum
            leftFraction = middleFraction;
        }
        middleFraction.SetCounter(leftFraction.GetCounter() + rightFraction.GetCounter()); // neue mitte
        middleFraction.SetDenominator(leftFraction.GetDenominator() + rightFraction.GetDenominator());
        if (fabs((double) middleFraction - number) < fabs((double) resultFraction - number)) { 
            resultFraction = middleFraction;// wenn neue mitte näher an ziel ist als letzes erg
        }
    }
    return resultFraction;
}

bool Fraction::operator==(Fraction other) {

    if (counter == other.counter && denominator == other.denominator) { //wenn brüche == sind direkt true
        return true;
    }
    double a = (double) Fraction(counter, denominator);
    double b = (double) Fraction(other.counter, other.denominator);
    return sternBrocot(a) == sternBrocot(b);
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