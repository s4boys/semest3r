#include <iostream>
#include "Fraction.h"
#define MAX_DEN 100

Fraction::Fraction(int counter, int denominator) {
    this->counter = counter;
    this->denominator = denominator;
    reduce();
}

Fraction::Fraction(double value, int maxdenom) {
    Fraction sB = sternBrocot(value, maxdenom);
    this->counter =  sB.counter;
    this->denominator = sB.denominator;
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

/* Finde Zahl die am Nächsten zu Fließkommazahl ist*/
Fraction Fraction::sternBrocot(double number, int maxdenom){ 
    Fraction lowerLimit = (int) number; 
    Fraction upperLimit = ((int) number) + 1; 
    Fraction middleFraction = Fraction(lowerLimit.counter + upperLimit.counter,
            lowerLimit.denominator + upperLimit.denominator); //neuer, mittlerer bruch
    while (middleFraction.denominator < maxdenom) { // Grenze, hier = 100
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

bool Fraction::operator==(const Fraction other) const {
    if (counter == other.counter && denominator == other.denominator) { 
        return true;
    }
    return false;
}

Fraction::operator double() const {
    return 1.0 * counter / denominator;
}

//reduziere Nenner um ggT
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

//finde größten gemeinsamen Teiler
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

std::istream& operator>>(std::istream &stream, Fraction &fract){
    stream >> fract.counter >> fract.denominator;
//    fract.reduce();  ->wenn Input direkt gekürzt sein soll
    return stream;
}