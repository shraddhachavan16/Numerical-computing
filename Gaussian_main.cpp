
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Include/Gaussian.h"
using namespace std;

void printAndSave(const string& title,Gaussian& solver,ofstream& fout)
{
    cout << "\n" << title << "\n";
    fout << "\n" << title << "\n";

    if (!solver.solve())
    {
        cout << "Method Failed\n";
        fout << "Method Failed\n";
        return;
    }

    const vector<double>& sol = solver.getSolution();

    cout << fixed << setprecision(6);
    fout << fixed << setprecision(6);

    for (size_t i = 0; i < sol.size(); i++)
    {
        cout << "x" << i + 1 << " = " << sol[i] << endl;
        fout << "x" << i + 1 << " = " << sol[i] << endl;
    }

   
    ofstream data("solution.dat");
    for (size_t i = 0; i < sol.size(); i++)
        data << i + 1 << " " << sol[i] << endl;
    data.close();
}

int main()
{
    int size;
    string filename;

    cout << "Enter matrix size: ";
    cin >> size;

    cout << "Enter input filename: ";
    cin >> filename;

    NoPivot noPivot(size);
    WithPivot withPivot(size);

    if (!noPivot.readFile(filename) ||
        !withPivot.readFile(filename))
    {
        cout << "File reading error\n";
        return 1;
    }

    ofstream fout("output.txt");
    printAndSave("===== WITHOUT PIVOT =====",noPivot,fout);
    printAndSave("===== WITH PARTIAL PIVOT =====",withPivot,fout);

    fout.close();

    cout << "\nResults saved in output.txt\n";
    cout << "Data saved in solution.dat for GNUplot\n";

    return 0;
}