#include <iostream>

/*
 * Mike Silvasy
 * 1/30/20
 * MWF 1:25-2:15
 * Project 1
 *
 * Programming Language:  C++
 */

using namespace std;

int u1 = 1, v1 = 0, u2 = 0, v2 = 1, u3 = 28056, v3 = 3032, q = 0, a, b;
void setUp();
void calculateGCD();

/*
 * Runs the program.
 */
int main()
{
    setUp();
    calculateGCD();

    cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" <<
        "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;

    u3 = 48432;
    v3 = 47376;
    u1 = 1, v1 = 0, u2 = 0, v2 = 1, q = 0;
    setUp();
    calculateGCD();

    return 0;
}

/*
 * Displays the a and b values, and creates the first two rows of the table (labels and initial values).
 */
void setUp() {
    a = u3;
    b = v3;
    cout << "Initial Values:  a = " << a << ", b = " << b << "\n" << endl;
    cout << "\tu1\t|\tv1\t|\tu2\t|\tv2\t|\tu3\t|\tv3\t|\tq\t\n";
    cout <<"------------------------------------------------------------------------------------------" <<
        "-----------------------\n";
    cout <<  u1 << "\t\t|" << v1 << "\t\t|" << u2 << "\t\t|" << v2 << "\t\t|" << u3 << "\t\t|" << v3 << "\t\t|" << q << endl;
}

/*
 * Finds the greatest common denominator (GCD), the values for x and y such that ax + by = gcd(a, b),
 * and adds values to the table after each calculation.
 */
void calculateGCD() {
    while (v3 != 0) {
        cout <<"-----------------------------------------------------------------------------------" <<
            "------------------------------\n";
        // Computes q value
        q = u3/v3;

        // Computes u values and stores the old values for future use
        int oldu1 = u1;
        int oldu2 = u2;
        int oldu3 = u3;
        u1 = v1;
        u2 = v2;
        u3 = v3;

        // Computes the v values
        v1 = oldu1 - (q * v1);
        v2 = oldu2 - (q * v2);
        v3 = oldu3 - (q * v3);

        cout <<  u1 << "\t\t|" << v1 << "\t\t|" << u2 << "\t\t|" << v2 <<
            "\t\t|" << u3 << "\t\t|" << v3 << "\t\t|" << q << endl;
    }
    cout << "\n===> The greatest common denominator (GCD) is " << u3 << endl;

    cout << "\n===> Therefore, we know the following function " << a << "x + " << b << "y = " << u3
        << " is true for x = " << u1 << " and y = " << u2 << endl;
}
