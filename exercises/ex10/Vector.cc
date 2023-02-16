// Cedric Nagata
// nagatac@uw.edu

#include <iostream>
#include "Vector.h"

namespace vector333
{
    /****Constructor implementation****/
    // Default
    Vector::Vector()
    {
        std::cout << "Vector()";
        std::cout << ", the constructed Vector is at " << this << std::endl;

        this->magnitudes[0] = 0.0;
        this->magnitudes[1] = 0.0;
        this->magnitudes[2] = 0.0;
    }
    // 3-argument
    Vector::Vector(const double x, const double y, const double z)
    {
        std::cout << "Vector(" << x << "," << y << "," << z << ")";
        std::cout << ", the constructed Vector is at " << this << std::endl;

        this->magnitudes[0] = x;
        this->magnitudes[1] = y;
        this->magnitudes[2] = z;
    }
    // Copy
    Vector::Vector(const Vector &copy)
    {
        std::cout << "Vector(copy " << &copy << ")";
        std::cout << ", the constructed Vector is at " << this << std::endl;

        this->magnitudes[0] = copy.magnitudes[0];
        this->magnitudes[1] = copy.magnitudes[1];
        this->magnitudes[2] = copy.magnitudes[2];
    }
    // Destructor
    Vector::~Vector()
    {
        delete[] magnitudes;
        std::cout << "Destructor of Vector at " << this << std::endl;
    }

    /****Operation function implementations****/
    // Addition
    Vector Vector::operator+(const Vector &other)
    {
        return Vector(magnitudes[0] + other.magnitudes[0], magnitudes[1] + other.magnitudes[1], magnitudes[2] + other.magnitudes[2]);
    }
    // Subtraction
    Vector Vector::operator-(const Vector &other)
    {
        return Vector(magnitudes[0] - other.magnitudes[0], magnitudes[1] - other.magnitudes[1], magnitudes[2] - other.magnitudes[2]);
    }
    // Dot Product
    double Vector::operator*(const Vector &other)
    {
        return magnitudes[0] * other.magnitudes[0] + magnitudes[1] * other.magnitudes[1] + magnitudes[2] * other.magnitudes[2];
    }
    // Multiplication
    Vector Vector::operator*(const double k)
    {
        return Vector(magnitudes[0] * k, magnitudes[1] * k, magnitudes[2] * k);
    }

    /****Vector assignment****/
    // Equals assignment
    Vector &Vector::operator=(const Vector &other)
    {
        magnitudes[0] = other.magnitudes[0];
        magnitudes[1] = other.magnitudes[1];
        magnitudes[2] = other.magnitudes[2];

        return *this;
    }
    // Plus-Equals assignment
    Vector &Vector::operator+=(const Vector &other)
    {
        magnitudes[0] += other.magnitudes[0];
        magnitudes[1] += other.magnitudes[1];
        magnitudes[2] += other.magnitudes[2];

        return *this;
    }
    // Minus-Eqauls assignment
    Vector &Vector::operator-=(const Vector &other)
    {
        magnitudes[0] -= other.magnitudes[0];
        magnitudes[1] -= other.magnitudes[1];
        magnitudes[2] -= other.magnitudes[2];

        return *this;
    }

    /****Output stream****/
    std::ostream &operator<<(std::ostream &out, const Vector &v)
    {
        out << "(" << v.magnitudes[0] << "," << v.magnitudes[1] << "," << v.magnitudes[2] << ")";
        return out;
    }

} // namespace