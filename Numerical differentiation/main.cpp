#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include "Differentiation.h"
using namespace std;


// ======================================================
// Main
// ======================================================

int main()
{
    // Evaluation point
    double x = 1.0;

    // h values: 10^-1 to 10^-6
    vector<double> hValues =
    {
        1e-1,
        1e-2,
        1e-3,
        1e-4,
        1e-5,
        1e-6
    };


    // Create test functions
    Exponential exponential;
    Sine sine;
    Polynomial polynomial;


    // Open result.csv
    ofstream file("result.csv");

    if (!file.is_open())
    {
        cout << "Error opening result.csv" << endl;
        return 1;
    }


    // CSV header
    file << "Function,Method,h,Approximate,Exact,Absolute Error\n";


    // Array of functions
    TestFunction* functions[] =
    {
        &exponential,
        &sine,
        &polynomial
    };


    // ==================================================
    // Test all three functions
    // ==================================================

    for (TestFunction* function : functions)
    {
        cout << "\n\n============================================\n";
        cout << "Function: " << function->name() << endl;
        cout << "x = " << x << endl;
        cout << "============================================\n";


        // ==================================================
        // Forward Difference
        // ==================================================

        cout << "\nForward Difference\n";

        cout << left
             << setw(15) << "h"
             << setw(20) << "Approximate"
             << setw(20) << "Exact"
             << setw(20) << "Absolute Error"
             << endl;

        cout << string(75, '-') << endl;

        for (double h : hValues)
        {
            ForwardDifference method(x, h);

            double approximate = method.calculate(*function);
            double exact = function->exactDerivative(x);
            double error = fabs(exact - approximate);

            cout << fixed << setprecision(10);

            cout << setw(15) << h
                 << setw(20) << approximate
                 << setw(20) << exact
                 << setw(20) << error
                 << endl;

            file << function->name() << ","
                 << "Forward,"
                 << h << ","
                 << approximate << ","
                 << exact << ","
                 << error << "\n";
        }


        // ==================================================
        // Backward Difference
        // ==================================================

        cout << "\nBackward Difference\n";

        cout << left
             << setw(15) << "h"
             << setw(20) << "Approximate"
             << setw(20) << "Exact"
             << setw(20) << "Absolute Error"
             << endl;

        cout << string(75, '-') << endl;

        for (double h : hValues)
        {
            BackwardDifference method(x, h);

            double approximate = method.calculate(*function);
            double exact = function->exactDerivative(x);
            double error = fabs(exact - approximate);

            cout << setw(15) << h
                 << setw(20) << approximate
                 << setw(20) << exact
                 << setw(20) << error
                 << endl;

            file << function->name() << ","
                 << "Backward,"
                 << h << ","
                 << approximate << ","
                 << exact << ","
                 << error << "\n";
        }


        // ==================================================
        // Central Difference
        // ==================================================

        cout << "\nCentral Difference\n";

        cout << left
             << setw(15) << "h"
             << setw(20) << "Approximate"
             << setw(20) << "Exact"
             << setw(20) << "Absolute Error"
             << endl;

        cout << string(75, '-') << endl;

        for (double h : hValues)
        {
            CentralDifference method(x, h);

            double approximate = method.calculate(*function);
            double exact = function->exactDerivative(x);
            double error = fabs(exact - approximate);

            cout << setw(15) << h
                 << setw(20) << approximate
                 << setw(20) << exact
                 << setw(20) << error
                 << endl;

            file << function->name() << ","
                 << "Central,"
                 << h << ","
                 << approximate << ","
                 << exact << ","
                 << error << "\n";
        }
    }


    // Close CSV file
    file.close();

    cout << "\n\nResults saved in result.csv" << endl;

    return 0;
}