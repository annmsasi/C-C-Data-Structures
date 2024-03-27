/****************************************************************************************
Ann Sasi
pa6
CruzID asasi
Arithmetic.cpp

*****************************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include "BigInteger.h" // Assuming this contains the definition of BigInteger class

using namespace std;

int main(int argc, char* argv[]) {
    // Check command line for correct number of arguments
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return 1;
    }

    // Open input file
    ifstream in(argv[1]);
    if (!in.is_open()) {
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return 1;
    }

    // Open output file
    ofstream out(argv[2]);
    if (!out.is_open()) {
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return 1;
    }

    string A_str, B_str;
    if (!(in >> A_str >> B_str)) {
        cerr << "Failed to read input from file" << endl;
        return 1;
    }

    BigInteger A(A_str), B(B_str);

    const BigInteger s3("3"), s2("2"), s9("9"), s16("16");

    out << A << endl << endl;
    out << B << endl << endl;
    out << A + B << endl << endl;
    out << A - B << endl << endl;
    out << A - A << endl << endl;
    out << (s3 * A) - (s2 * B) << endl << endl;
    out << A * B << endl << endl;
    out << A * A << endl << endl;
    out << B * B << endl << endl;
    out << (s9 * (A * A * A * A)) + (s16 * (B * B * B * B * B)) << endl << endl;
    in.close();
    out.close();
        
    return 0;
}
