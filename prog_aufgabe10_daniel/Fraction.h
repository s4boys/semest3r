 
#ifndef FRACTION_H
#define FRACTION_H

class ostream;
class istream;

class Fraction {
public:
    Fraction(int counter=0, int denominator=1);
    Fraction(double value, int maxdenom=100);
    Fraction operator+(Fraction other);
    Fraction operator+=(Fraction other);
    Fraction operator-(Fraction other);
    Fraction operator-=(Fraction other);
    Fraction operator*(Fraction other);
    Fraction operator*=(Fraction other);
    Fraction operator/(Fraction other);
    Fraction operator/=(Fraction other);
    bool operator==(Fraction other);
    operator double() const;
    friend void operator <<(ostream &stream, Fraction fract);
//    friend void operator >>(istream &stream, Fraction fract);
    int GetCounter() const { return counter; }
    int GetDenominator() const { return denominator; }
private:
    void reduce();
    static int gcd(int a, int b);
    int counter;
    int denominator;
};

#endif /* FRACTION_H */

