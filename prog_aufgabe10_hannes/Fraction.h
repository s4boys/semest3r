 
#ifndef FRACTION_H
#define FRACTION_H

class ostream;
class istream;

class Fraction {
public:
    Fraction(int counter=0, int denominator=1);
    Fraction(double value, int maxdenom=100);
    Fraction operator+(const Fraction other) const;
    Fraction operator+=(const Fraction other);
    Fraction operator-(const Fraction other) const;
    Fraction operator-=(const Fraction other);
    Fraction operator*(const Fraction other) const;
    Fraction operator*=(const Fraction other);
    Fraction operator/(const Fraction other) const;
    Fraction operator/=(const Fraction other);
    bool operator==(const Fraction other) const;
    operator double() const;
    friend ostream& operator <<(ostream &stream, const Fraction &fract);
//    friend istream& operator >>(istream &stream, Fraction &fract);
    Fraction sternBrocot(double number, int maxdenom) {}
    int GetCounter() const { return counter; }
    int GetDenominator() const { return denominator; }
    int SetCounter(int ctr) { counter= ctr; }
    int SetDenominator(int den) { denominator = den; }
private:
    void reduce();
    static int gcd(int a, int b);
    int counter;
    int denominator;
};

#endif /* FRACTION_H */
