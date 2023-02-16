// Cedric Nagata
// nagatac@uw.edu

#ifndef _CARTESIAN_H_
#define _CARTESIAN_H_

#include <string>
#include "Coordinate.h"

using namespace std;

class Cartesian: public Coordinate {
public:
    // constructor
    Cartesian(double, double);

    // virtual method
    virtual string ToString() const;

    // distance method
    double Distance(const Cartesian&) const;
    
private:
    double x; // x coordinate
    double y; // y coordinate
};

#endif