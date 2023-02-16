// Cedric Nagata
// nagatac@uw.edu

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

namespace vector333 {
    class Vector {
        public:
            /****Constructors****/
            // 0-argument constructor
            Vector();
            // 3-argument constructor
            Vector(const double x, const double y, const double z);
            // copy constructor
            Vector(const Vector &v);
            // destructor
            ~Vector();

            /****Accessor functions****/
            double get_x() const { return x_; }
            double get_y() const { return y_; }
            double get_z() const { return z_; }

            /****Vector assignment****/
            Vector &operator=(const Vector &other); //equals
            Vector &operator+=(const Vector &other); // plus-equals
            Vector &operator-=(const Vector &other); // minus-equals

            /****Operations****/
            Vector operator+(const Vector &other); // addition
            Vector operator-(const Vector &other); // subtraction
            double operator*(const Vector &other); // dot product
            Vector operator*(const double k); // multiplication

        private:
            // vector representation
            double x_, y_, z_;
    };

/****Output stream****/
std::ostream & operator<<(std::ostream &output, const Vector &v);
}

#endif