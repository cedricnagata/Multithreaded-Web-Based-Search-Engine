// Cedric Nagata
// nagatac@uw.edu

#include <string>
#include <math.h>
#include "Polar.h"

using namespace std;

// constructor
Polar::Polar(double r, double a) : r(r), a(a) {}

// ToString
string Polar::ToString() const {
    return "Polar Point: (" + to_string(r) + ", " + to_string(a) + ")";
}

// Distance method
double Polar::Distance(const Polar &point) const {
    return sqrt(pow(r, 2.0) + pow(point.r, 2.0) - (2 * r * point.r) * cos((a - point.a) * (3.1415 / 180)));
}