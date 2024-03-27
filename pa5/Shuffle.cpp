/****************************************************************************************
Ann Sasi
pa5
CruzID asasi
Shuffle.cpp

*****************************************************************************************/
#include<iostream>
#include<string>
#include<stdexcept>
#include <iomanip>
#include"List.h"
using namespace std;

void shuffle(List& D);

int main(int argc, char *argv[]) {
    // Check command line for correct number of arguments
    if (argc != 2){
        cerr << "incorrect deck size" << endl;
        return 1;
    }
    
    int deckSize = atoi(argv[1]);

    cout << "deck size shuffle count" << endl;
    cout << "------------------------------" << endl;
    List D;
    for (int deck = 1; deck <= deckSize; deck++){
        // for (int i = 0; i < deck; ++i) {
        //     D.insertBefore(i);
        // }
        D.moveBack();
        D.insertBefore(deck-1);

        int shuffle_count = 1;
        List original_deck = D;
        shuffle(D);
        while (!(D == original_deck)){
            shuffle(D);
            shuffle_count++;
        }
        cout << setw(8) << left << deck << setw(12) << right << shuffle_count << endl;
    }     

    return 0;  
}

void shuffle(List& D){
    List A,B;
    int len = D.length();
    D.moveFront();
    for(int i = 0; i <(len/2);i++){
        A.insertBefore(D.peekNext());
        D.moveNext();
    }
    //cout<<A<<endl;

    for(int i = (len/2); i <(len);i++){
        B.insertBefore(D.peekNext());
        D.moveNext();
    }
    D.clear();
    A.moveFront();
    B.moveFront();
    // cout<<"A"<<A<<endl;
    // cout<<"B"<<B<<endl;

    while (B.position() < B.length()) {
            int x = B.moveNext();
            D.insertBefore(x);
            if (A.position() < A.length()) {
                int y = A.moveNext();
                D.insertBefore(y);
            }
    }
}
