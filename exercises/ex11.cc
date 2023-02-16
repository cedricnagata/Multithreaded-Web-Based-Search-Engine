// Cedric Nagata
// nagatac@uw.edu

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// template function declaration
template <class T> T ReadValue(istream& in);

int main(int argc, char **argv) {
    vector<double> inputs;

    cout << "Input 6 doubles:" << endl;

    // get doubles
    for (int i = 0; i < 6; i++) {
        // use template function to read input
        double curr = ReadValue<double>(cin);
        inputs.push_back(curr);
    }

    // sort vector using iterators
    sort(inputs.begin(), inputs.end());

    // print sorted doubles
    cout << "Your sorted doubles are:" << endl;
    for (int i = 0; i < 6; i++) {
        cout << inputs[i] << endl;
    }

    return EXIT_SUCCESS;
}

template <class T> T ReadValue(istream& in) {
    T next;
    in >> next;

    // check inputs
    if (!cin.good()) {
      cerr << "Error reading input" << endl;
      exit(EXIT_FAILURE);
    }

    return next;   
}

