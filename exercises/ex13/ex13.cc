// Cedric Nagata
// nagatac@uw.edu

#include <iostream>

#include "Cartesian.h"
#include "Polar.h"

using namespace std;

int main(int argc, char **argv) {
    // Construct cartesian points
    Cartesian cart1(1.0, 2.0);
    Cartesian cart2(5.0, 10.0);

    // Test ToString and Distance
    cout << "Cartesian Point 1: " << cart1.ToString() << endl;
    cout << "Cartesian Point 1: : " << cart2.ToString() << endl;
    cout << "Expected Distance: 8.944, Actual Distance: " << cart1.Distance(cart2) << endl;

    // Construct polar points
    Polar p1(1.0, 90.0);
    Polar p2(5.0, 180.0);

    // Test ToString and Distance
    cout << "Polar Point 1: " << p1.ToString() << endl;
    cout << "Polar Point 2: " << p2.ToString() << endl;
    cout << "Expected Distance: 5.099, Actual Distance: " << p1.Distance(p2) << endl;

    return EXIT_SUCCESS;
}