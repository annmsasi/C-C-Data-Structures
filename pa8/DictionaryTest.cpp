//-----------------------------------------------------------------------------
// A test client for the Dictionary ADT
// Ann Sasi
// pa8
// CruzID asasi
// DictionaryTest.cpp
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main(){
   Dictionary A;
   A.setValue("d", 1);
   A.setValue("b", 5);
   A.setValue("c", 16);
   A.setValue("f", 176);
   A.setValue("e", 3214);

   A.begin();
   cout<<A.currentVal()<<endl;
   A.remove("b");
   A.begin();
   A.clear();
   A.begin();
   A.currentVal();
   A.setValue("a", 1);
   A.setValue("b", 5);
   A.setValue("c", 16);
   A.setValue("d", 176);
   A.setValue("e", 3214);
   A.begin();
   A.next();
   A.next();
   A.setValue("a", 1);
   A.setValue("b", 5);
   A.setValue("e", 3214);
   A.end();
   A.prev();
   Dictionary B;
   B = A;
   B.setValue("justify", 100);
   B.setValue("leaflet", 20);
   B.setValue("godsend", 15);
   B.setValue("quizzical", 10);
   B.setValue("solemnly", 5);
   B.setValue("abbreviation", 1);

   cout << "A.size() = " << A.size() << endl  << A << endl;
   cout << "B.size() = " << B.size() << endl  << B << endl;
   cout << "A pre-order: " << endl << A.pre_string() << endl;

    return 0;

   return( EXIT_SUCCESS );
}