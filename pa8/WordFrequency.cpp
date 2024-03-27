
/****************************************************************************************
Ann Sasi
pa8
CruzID asasi
WordFrequency.cpp

*****************************************************************************************/
#include<iostream>
#include<string>
#include<fstream>
#include<stdexcept>
#include <algorithm>
#include"Dictionary.h"
using namespace std;

int main(int argc, char * argv[]) {
    ifstream in;
    ofstream out;
    string line;
    string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";
    Dictionary D;

    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return EXIT_FAILURE;
    }

    in.open(argv[1]);
    if (!in.is_open()) {
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return EXIT_FAILURE;
    }
    out.open(argv[2]);
    if (!out.is_open()) {
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return EXIT_FAILURE;
    }

    while (getline(in, line)) {
        size_t length = line.length();
        size_t firstNonDelim = min(line.find_first_not_of(delim, 0), length);
        size_t keyEnd;
        string firstKey;

        while (firstNonDelim != string::npos) {
            keyEnd = min(line.find_first_of(delim, firstNonDelim), length);
            firstKey = line.substr(firstNonDelim, keyEnd - firstNonDelim);

            transform(firstKey.begin(), firstKey.end(), firstKey.begin(), ::tolower);

            if (!firstKey.empty()) {
                if (D.contains(firstKey)) {
                    D.getValue(firstKey)++;
                } else {
                    D.setValue(firstKey, 1);
                }
            }

            // Move to next word
            firstNonDelim = line.find_first_not_of(delim, keyEnd);
        }
    }

    out << D << endl;
    in.close();
    out.close();
    return 0;
}
