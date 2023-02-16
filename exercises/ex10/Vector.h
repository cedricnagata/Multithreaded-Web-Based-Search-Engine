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

            /****Vector assignment****/
            Vector &operator=(const Vector &other); //equals
            Vector &operator+=(const Vector &other); // plus-equals
            Vector &operator-=(const Vector &other); // minus-equals

            /****Operations****/
            Vector operator+(const Vector &other); // addition
            Vector operator-(const Vector &other); // subtraction
            double operator*(const Vector &other); // dot product
            Vector operator*(const double k); // multiplication

            /****Output stream****/
            friend std::ostream & operator<<(std::ostream &output, const Vector &v);

        private:
            // vector representation
            double *magnitudes = new double[3];
    };
}

#endif