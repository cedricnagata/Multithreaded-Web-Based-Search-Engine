// Cedric Nagata
// nagatac@uw.edu

#include <iostream>
#include "Vector.h"

namespace vector333 {
    /****Constructor implementation****/
    // Default
    Vector::Vector() {
        std::cout << "Vector()";
        std::cout << ", the constructed Vector is at " << this << std::endl;

        this->x_ = 0.0;
        this->y_ = 0.0;
        this->z_ = 0.0;
    }
    // 3-argument
    Vector::Vector(const double x, const double y, const double z) {
        std::cout << "Vector(" << x << "," << y << "," << z << ")";
        std::cout << ", the constructed Vector is at " << this << std::endl;

        this->x_ = x;
        this->y_ = y;
        this->z_ = z;
    }
    // Copy
    Vector::Vector(const Vector &copy) {
        std::cout << "Vector(copy " << &copy << ")";
        std::cout << ", the constructed Vector is at " << this << std::endl;

        this->x_ = copy.x_;
        this->y_ = copy.y_;
        this->z_ = copy.z_;
    }
    // Destructor
    Vector::~Vector() {
        std::cout << "Destructor of Vector at " << this << std::endl;
    }

    /****Operation function implementations****/
    // Addition
    Vector Vector::operator+(const Vector &other) {
        return Vector(x_ + other.x_, y_ + other.y_, z_ + other.z_);
    }
    // Subtraction
    Vector Vector::operator-(const Vector &other) {
        return Vector(x_ - other.x_, y_ - other.y_, z_ - other.z_);
    }
    // Dot Product
    double Vector::operator*(const Vector &other) {
        return x_ * other.x_ + y_ * other.y_ + z_ * other.z_;
    }
    // Multiplication
    Vector Vector::operator*(const double k) {
        return Vector(x_ * k, y_ * k, z_ * k);
    }

    /****Vector assignment****/
    // Equals assignment
    Vector &Vector::operator=(const Vector &other) {
        x_ = other.x_;
        y_ = other.y_;
        z_ = other.z_;

        return *this;
    }
    // Plus-Equals assignment
    Vector &Vector::operator+=(const Vector &other) {
        x_ += other.x_;
        y_ += other.y_;
        z_ += other.z_;

        return *this;
    }
    // Minus-Eqauls assignment
    Vector &Vector::operator-=(const Vector &other) {
        x_ -= other.x_;
        y_ -= other.y_;
        z_ -= other.z_;

        return *this;
    }

    /****Output stream****/
    std::ostream & operator<<(std::ostream &out, const Vector &v) {
      out << "(" << v.get_x() << "," << v.get_y() << "," << v.get_z() << ")";
      return out;
    }
    
} // namespace