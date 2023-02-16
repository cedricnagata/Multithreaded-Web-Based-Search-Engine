// Cedric Nagata
// nagatac@uw.edu

#ifndef _POLAR_H_
#define _POLAR_H_

#include <string>
#include "Coordinate.h"

using namespace std;

class Polar: public Coordinate {
public:
    // constructor
    Polar(double, double);

    // virtual method
    virtual string ToString() const;

    // distance method
    double Distance(const Polar&) const;
    
private:
    double r; // radius
    double a; // angle (degrees)
};

#endif