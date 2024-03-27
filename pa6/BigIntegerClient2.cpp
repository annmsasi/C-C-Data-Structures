
#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"
int power2 = 9;
int base2 = 1000;
using namespace std;
List negateList2(List X){
    if(X.length() == 0){
    return X;
   } 
   X.moveFront();
   while(X.position() < X.length()){
    X.setAfter(-X.peekNext());
    X.moveNext();
   }
   return X;
 }
int normalize2(List& N){
   int sig = 1;
   ListElement el = 0;
   ListElement carryon = 0;
   N.moveBack();
   if (N.front() < 0 ){
        negateList2(N);
        sig = -1;
   }
   while(N.position() > 0){
    el = N.peekPrev();
    if(el <0){
        el += base2 +carryon;
        N.setBefore(el);
        carryon = -1;
        }
    else{
        el += carryon;
        carryon = 0;
        if (el >= base2){
            carryon = el/base2;
            el %= base2;
        }
        N.setBefore(el);
    }
    N.movePrev();
   }
   while(carryon > base2){
    el = carryon%base2;
    N.insertAfter(el);
    carryon/=base2;
   }
   if (carryon != 0){
    N.moveFront();
    N.insertAfter(carryon);
   }
   if(N.front() < 0){
        N.setAfter((N.peekNext()*-1)-1);
        N.moveNext();
        while(N.position() < N.length()){
            N.setAfter(base2 - N.peekNext());
            N.moveNext();
            
        }
        cout<<N<<endl;
        normalize2(N);
        sig = -1;
   }
   N.moveFront();
   while(N.peekNext() == 0 && N.length() > 0){
        N.eraseAfter();
   }
   if (N.length() == 0){
    return 0;
   }
   return sig;
}

int main(){
    List L;
    L.insertAfter(-19787865433897165);
    cout<<normalize2(L)<<endl;
    cout<<L<<endl;
    
}