// complex.hpp

#pragma once

#include <iostream>

class Complex {
private:
    double real;
    double imag;

public:
    // Constructor
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    // Getter methods
    double getReal() const { return real; }
    double getImag() const { return imag; }

    // Addition
    Complex operator+(const Complex &other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    // Subtraction
    Complex operator-(const Complex &other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    // Multiplication
    Complex operator*(const Complex &other) const {
        return Complex(real * other.real - imag * other.imag,
                       real * other.imag + imag * other.real);
    }

    // Division
    Complex operator/(const Complex &other) const {
        double denominator = other.real * other.real + other.imag * other.imag;
        return Complex((real * other.real + imag * other.imag) / denominator,
                       (imag * other.real - real * other.imag) / denominator);
    }

    bool operator==(const Complex &other) const {
        return (real == other.real && imag == other.imag);
    }

    // Output stream operator
    friend std::ostream& operator<<(std::ostream &out, const Complex &c) {
        out << c.real;
        if (c.imag >= 0) out << '+';
        out << c.imag << 'i';
        return out;
    }
};
