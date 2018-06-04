#include <cmath>
#include<iostream>
#include "Fraction.h"

// gibt den genaueren Wert, 311/99, zurück
//Fraction Fraction::sternBrocot(double number, int maxdenom) { // bekommt zahl, sucht Fraction im sternbrocot die der am nächsten ist
//    Fraction leftFraction = (int) number; // bei pi dann 3
//    Fraction rightFraction = ((int) number) + 1; // bei pi dann 4
//    Fraction middleFraction = Fraction(leftFraction.counter + rightFraction.counter,
//            leftFraction.denominator + rightFraction.denominator); //neuer, mittlerer bruch
//    Fraction resultFraction = middleFraction;
//    while (middleFraction.denominator < maxdenom) { // gewählte grenze
//        if ((double) middleFraction > number) { // falls Ziel links von middle ist
//            rightFraction = middleFraction; // neuer rechter bruch ist die alte mitte
//        } else { // andersherum
//            leftFraction = middleFraction;
//        }
//        middleFraction.SetCounter(leftFraction.counter + rightFraction.counter); // neue mitte
//        middleFraction.SetDenominator(leftFraction.denominator + rightFraction.denominator);
//        if (fabs((double) middleFraction - number) < fabs((double) resultFraction - number)) { 
//            resultFraction = middleFraction;// wenn neue mitte näher an ziel ist als letzes erg
//        }
//    }
//    return resultFraction;
//}

Fraction::Fraction(int counter, int denominator) {
    this->counter = counter;
    this->denominator = denominator;
    reduce();
}

Fraction::Fraction(double value, int maxdenom) {
    Fraction temp = sternBrocot(value, maxdenom);
    this->counter =  temp.counter;
    this->denominator = temp.denominator;
}

Fraction Fraction::operator+(const Fraction other) const {
    return Fraction(counter * other.denominator + other.counter * denominator,
            denominator * other.denominator);
}

Fraction Fraction::operator+=(const Fraction other) {
    counter = counter * other.denominator + other.counter * denominator;
    denominator = denominator * other.denominator;
    return *this;
}

Fraction Fraction::operator-(const Fraction other) const {
    return Fraction(counter * other.denominator - other.counter * denominator,
            denominator * other.denominator);
}

Fraction Fraction::operator-=(const Fraction other) {
    counter = counter * other.denominator - other.counter * denominator;
    denominator = denominator * other.denominator;
    return *this;
}

Fraction Fraction::operator*(const Fraction other) const {
    return Fraction(counter * other.counter, denominator * other.denominator);
}

Fraction Fraction::operator*=(const Fraction other) {
    counter = counter * other.counter;
    denominator = denominator * other.denominator;
    return *this;
}

Fraction Fraction::operator/(const Fraction other) const {
    return Fraction(counter * other.denominator, denominator * other.counter);
}

Fraction Fraction::operator/=(const Fraction other) {
    counter = counter * other.denominator;
    denominator = denominator * other.counter;
    return *this;
}

bool Fraction::operator==(const Fraction other) const {

    if (counter == other.counter && denominator == other.denominator) { //wenn brüche == sind direkt true
        return true;
    }
    return false;
}

Fraction::operator double() const {
    return 1.0 * counter / denominator;
}

Fraction Fraction::sternBrocot(double number, int maxdenom)
{ // bekommt zahl, sucht Fraction im sternbrocot die der am nächsten ist
    Fraction lowerLimit = (int) number; // bei pi dann 3
    Fraction upperLimit = ((int) number) + 1; // bei pi dann 4
    Fraction middleFraction = Fraction(lowerLimit.counter + upperLimit.counter,
            lowerLimit.denominator + upperLimit.denominator); //neuer, mittlerer bruch
    while (middleFraction.denominator < maxdenom) { // gewählte grenze
        if ((double) middleFraction > number) { // falls Ziel links von middle ist
            upperLimit = middleFraction; // neuer rechter bruch ist die alte mitte
        } else { // andersherum
            lowerLimit = middleFraction;
        }
        middleFraction.counter = lowerLimit.counter + upperLimit.counter; // neue mitte
        middleFraction.denominator = lowerLimit.denominator + upperLimit.denominator;
    }
    return upperLimit;
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

std::ostream& operator<<(std::ostream &stream, const Fraction &fract) {
    stream << "(" << fract.counter << ", " << fract.denominator << ")";
    return stream;
}

std::istream& operator >>(std::istream &stream, Fraction &fract){
    stream >> fract.counter >> fract.denominator;
    return stream;
}