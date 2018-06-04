 
#ifndef FRACTION_H
#define FRACTION_H


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
    Fraction sternBrocot(double value, int maxdenom);
    operator double() const;
    friend std::ostream& operator <<(std::ostream &stream, const Fraction &fract);
    friend std::istream& operator >>(std::istream &stream, Fraction &fract);
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
