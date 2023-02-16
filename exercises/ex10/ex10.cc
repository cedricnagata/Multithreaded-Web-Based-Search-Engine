// Cedric Nagata
// nagatac@uw.edu

#include "Vector.h"
#include <iostream>

using namespace std;
using namespace vector333;

int main() {
    /****Constructor Tests****/
    Vector constr1;
    cout << "Default Constructor - Expected Vector: (0,0,0), Actual: " << constr1 << endl;

    Vector constr2(1.0, 2.0, 3.0);
    cout << "3-Argument Constructor - Expected Vector: (1,2,3), Actual: " << constr2 << endl;

    Vector constr3(1.0, 5.0, 10.0);
    Vector constr4(constr3);
    cout << "Copy Constructor - Copied Vector: (1,5,10), Actual: " << constr4 << endl;
    
    /****Vector assignment****/
    Vector assn1(0.0, 0.0, 0.0);
    Vector assn2(10.0, 10.0, 10.0);
    Vector assn3(1.0, 2.0, 3.0);
    assn1 = assn2;
    cout << "Assignment(=) - Assigned Vector: (10,10,10), Actual Vector: " << assn1 << endl;
    assn1 += assn3;
    cout << "Assignment(+=) - Assigned Vector: (11,12,13), Actual Vector: " << assn1 << endl;
    assn1 -= assn3;
    cout << "Assignment(-=) - Assigned Vector: (10,10,10), Actual Vector: " << assn1 << endl;

    /****Operations****/
    Vector oper1(2.0,2.0,2.0);
    Vector oper2(1.0,1.0,1.0);
    Vector oper3 = oper1 + oper2;
    Vector oper4 = oper1 - oper2;
    double oper5 = oper1 * oper2;   
    Vector oper6 = oper2 * 2.0;

    cout << "Addition - Expected: (3,3,3), Actual: " << oper1 + oper2 << endl;
    cout << "Subtraction - Expected: (1,1,1), Actual: " << oper1 - oper2 << endl;
    cout << "Dot Product - Expected: 6, Actual: " << oper5 << endl;
    cout << "Multiplication - Expected: (2,2,2), Actual: " << oper2 * 2.0 << endl;

    return 0;
}