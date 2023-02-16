// Cedric Nagata
// nagatac@uw.edu

#include <string>
#include <math.h>
#include "Cartesian.h"

using namespace std;

// constructor
Cartesian::Cartesian(double x, double y) : x(x), y(y) {}

// ToString
string Cartesian::ToString() const {
    return "Cartesian Point: (" + to_string(x) + ", " + to_string(y) + ")";
}

// Distance Method
double Cartesian::Distance(const Cartesian &point) const {
    return sqrt(pow((x - point.x), 2.0) + pow((y - point.y), 2.0));
}