#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"
#include"BigInteger.h"
#include <valarray>
using namespace std;
int power = 9;
int base = 1000000000;
List negateList(List X){
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

int normalize(List& N){
    N.moveBack();
    long carry = 0;
    long num = 0;
    int sig;
    while(N.position() > 0){
        num = N.peekPrev() + carry;
        carry = num/base;
        if(num <0){
            carry--;
            N.setBefore((num%base)+base);
        }
        else{
            N.setBefore(num%base);
        }
        N.movePrev();
        

    }
    N.insertBefore(carry);
    N.moveFront();
    if (N.peekNext() < 0){
        sig = -1;
    }
    else if(N.peekNext() > 0){
        sig = 1;
    }
    else if (N.peekNext() == 0){
        sig = 0;
    }
    return sig;

//     if (N.front() == 0 && N.length() == 1){
//         return 0;
//     }
//     int sig = 1;
//    ListElement el = 0;
//    ListElement carryon = 0;
//    N.moveBack();
//    if (N.front() < 0 ){
//         negateList(N);
//         sig = -1;
//    }
//    while(N.position() > 0){
//     el = N.peekPrev();
//     if(el <0){
//         el += base +carryon;
//         N.setBefore(el);
//         carryon = -1;
//         }
//     else{
//         el += carryon;
//         carryon = 0;
//         if (el >= base){
//             carryon = el/base;
//             el %= base;
//         }
//         N.setBefore(el);
//     }
//     N.movePrev();
//    }
//    while(carryon > base){
//     el = carryon%base;
//     N.insertAfter(el);
//     carryon/=base;
//    }
//    if (carryon != 0){
//     N.moveFront();
//     N.insertAfter(carryon);
//    }
//    if(N.front() < 0){
//         N.setAfter((N.peekNext()*-1)-1);
//         N.moveNext();
//         while(N.position() < N.length()- 1){
//             N.setAfter(base - N.peekNext()-1);
//             N.moveNext();
//         }
//         el = base - N.peekNext();
//         N.setAfter(el);
//         if( el >=base){
//             normalize(N);
//         }
//         sig = -1;
//    }
//    N.moveFront();
//    while(N.length() > 0 && N.peekNext() == 0  ){
//         N.eraseAfter();
//    }
//    if (N.length() == 0){
//     N.insertAfter(0);
//     return 0;
//    }
//    return sig;
}
//    while (digs.peekNext() ==0){
//     digs.eraseAfter();
//    }
//    if ( digs.length() == 0){
//     return 0;
//    }
//    if (digs.front() > 0){
//     sig = 1;
//    }
//    if (digs.front() < 0){
//     negateList(digs);
//     sig = -1;
//    }
//    ListElement carry = 0;
//    digs.moveBack();
//    for (int x = 0; x<digs.length();x++ ){
//         ListElement val = digs.movePrev() + carry;
//         cout<<val<<endl;
//         carry = val/base;
//         val = val%base;
//         if (x == (digs.length()-1)){
//             digs.setAfter(val);\
//             break;
//         }
//         digs.setAfter(val);
//     }
//     digs.moveFront();
//     while (digs.peekNext() ==0){
//         digs.eraseAfter();
//     }
//    N = digs;
//    return sig;

BigInteger::BigInteger(){
    signum = 0;
    digits = List();
}

// BigInteger()
// Constructor that creates a new BigInteger from the long value x.
BigInteger::BigInteger(long x){
    if(x == 0){
        signum = 0;
        digits = List();
        return;
    }
    if (x < 0){
        signum = -1;
    }
    else{
        signum = 1;
    }
    while (x > 0){
        digits.insertAfter(x % base);
        x = x / base;
    }
}
    

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s) {
    if (s.length() == 0) {
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }
    // Check if the string is non-numeric
    if (s[0] == '-') {
        signum = -1;
    } else {
        signum = 1;
    }

    // Remove sign prefix
    if (s[0] == '-' || s[0] == '+') {
        s = s.substr(1);
    }
    for (int i = 0; i < s.length(); i++) {
        if (!isdigit(s[i])) {
            throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        }
    }

    // Determine the sign of the BigInteger


    // Insert the numbers into the digits list
    size_t max = 0;
    size_t digs = s.length();
    if (s.length() % power != 0) {
        std::string remainder = s.substr(0, s.length() % power);
        long numbers = std::stol(remainder);
        digits.insertAfter(numbers);
        s.erase(0, s.length() % power);
        digits.moveNext();
    }
    digs = s.length();

    while (max < (s.length() / power)) {
        std::string num = s.substr(digs - power, power);
        digits.insertAfter(std::stol(num));
        digs = digs - power;
        max++;
    }

    // each element in the list has leading zeros
    digits.moveFront();
    while (digits.position() < digits.length()) {
        long num = digits.moveNext();
        std::string s = std::to_string(num);
        while (s.length() < power) {
            s = "0" + s;
        }
        digits.eraseBefore();
        digits.insertBefore(std::stol(s));
    }
}



// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N){
    this -> signum = N.signum;
    this -> digits = N.digits;
}
// Optional Destuctor
// ~BigInteger()
// ~BigInteger();


// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const{
    return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const{

    if ((this->sign() == 0) && (N.sign() == 0)){
        return 0;
    }
    else if (this->signum > N.signum){
        return 1;
    }
    else if ((this->signum < N.signum)){
        return -1;
    }
    if (this->digits.length() < N.digits.length()){
        return -1;
    }
    else if (this->digits.length() > N.digits.length()){
        return 1;
    }
    List A = this ->digits;
    List B = N.digits;
    A.moveFront();
    B.moveFront();
    if (this->signum == 1) {
        for (A.moveFront(),B.moveFront(); A.position() <A.length(), B.position() < B.length(); A.moveNext(), B.moveNext()){
            if(A.peekNext() > B.peekNext()){
                return 1;
            }
            else if (A.peekNext() < B.peekNext()){
                return -1;
            }
        }
        return 0;
    }
    else if (this->signum ==  -1) {
        for (A.moveFront(),B.moveFront(); A.position() <A.length(), B.position() < B.length(); A.moveNext(), B.moveNext()){
            if(A.peekNext() < B.peekNext()){
                return 1;
            }
            else if (A.peekNext() > B.peekNext()){
                return -1;
            }
        }
    }
    return 0;

}


// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero(){
    digits.clear();
    signum = 0;
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate(){
    if (signum == -1){
        signum = 1;
    }
    else if (signum == 1){
        signum = -1;
    }
}


// BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.

List sumList(List A, List B) {
    List num;
    A.moveBack();
    B.moveBack(); 
    long carry = 0;
    if(A.length() == 0){
        return B;
    }
    else if(B.length() == 0){
        return A;
    }
    while (A.position() > 0 || B.position() > 0 || carry != 0) {
        long a = (A.position() > 0) ? A.peekPrev() : 0;
        long b = (B.position() > 0) ? B.peekPrev() : 0;
        long sum = a + b + carry;
        carry = sum / base; 
        sum %= base; 

        num.moveFront();
        num.insertBefore(sum);

        if (A.position() > 0) A.movePrev();
        if (B.position() > 0) B.movePrev();
    }
    normalize(num);
    return num;
}
List scalarMult(List N, ListElement x){
    List C = N;
    C.moveFront();
    while(C.position()<C.length()){
        C.setAfter(C.peekNext()*x);
        C.moveNext();
    }
    return C;
}


BigInteger BigInteger::add(const BigInteger& N) const{
    BigInteger Sum;
    List numN = N.digits;
    List numX = digits;
    List add;
    List smaller;
    List greater;
    int diff_size;
    if (this->signum < 0){
        numX = negateList(numX);
    } 
    if (N.signum < 0){
        numN = negateList(numN);
    }
    add = sumList(numX,numN);
    Sum.signum = normalize(add);
    Sum.digits = add;
    return Sum;
    // if (numX.length() < numN.length()){
    //     diff_size = numN.length() - numX.length();
    //     for (int x = 0; x< diff_size; x++){
    //         numX.insertAfter(0);
    //     }
    // }
    // else if (numX.length() > numN.length()){
    //     diff_size = numX.length() - numN.length();
    //     for (int x = 0; x< diff_size; x++){
    //         numN.insertAfter(0);
    //     }
    // }
    // if (numN == numX && N.signum != signum){
    //     Sum.signum = 0;
    //     return Sum;
    // }

    // int len = numX.length();
    // long s;

    // for (int i = 0; i < len; i++){
    //     s = numX.peekPrev() * signum;
    //     s+=numN.peekPrev() * N.signum;
    //     add.insertAfter(s);
    //     numN.movePrev();
    //     numX.movePrev();
    // }

    // Sum.digits = add;

}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const{
    BigInteger Diff;
    BigInteger X = N;
    // X.digits = negateList(N.digits); // Make a copy of N to perform negation
    // Negate the second number
    // negateList(X.digits);
    X.negate();
    // Call the add function (adjusted to properly call member function)
    Diff = this->add(X);

    return Diff;
    // BigInteger Diff;
    // BigInteger X;
    // List numN = N.digits;
    // List numX = this-> digits;
    // List difference;
    // numX.moveBack();
    // numN.moveBack();
    // if (this < N){
    //     Diff.signum = -1;

    // }
    // else if(this == N){
    //     Diff = BigInteger(0);
    //     return;
    // }
    // else{
    //     Diff.signum = 1;
    // }
    // if (N.sign() == -1){
    //     X.signum = 1;
    //     X.digits = numN;
    // }
    // else{
    //     X.signum = -1;
    //     X.digits = numN;
    // }
    // this.add(X);
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const {
    BigInteger Product;
    int Xsig = this->signum;
    int Nsig = N.signum;
    if (Xsig == 0 || Nsig == 0){
        return Product;}
    List copy = digits;
    List Nval = N.digits;
    List val;
    List sum;
    int shift = 0;
    long mult;
    copy.moveBack();
    while (copy.position() > 0) {
        mult = copy.peekPrev();
        val = scalarMult(N.digits, mult);
        val.moveBack();
        for (int i = 0; i < shift; i++) {
            val.insertBefore(0);
        }

        shift++;
        sum = sumList(sum,val);
        copy.movePrev();
    }
    Product.digits = sum;

    if (Xsig != Nsig){
        Product.signum = -1;
    }
    else {
        Product.signum = 1;
    }
    normalize(Product.digits);
    return Product;
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string(){
    string num;
    if (this->signum == -1){
        num+= '-';
    }
    else if (this -> signum == 0){
        num+= '0';
        return num;
    }
    digits.moveFront();
    num += std::to_string(digits.moveNext());
    
    while(digits.position()<digits.length()){
        string s =std::to_string(digits.moveNext());
        while(s.length()< power){
            s = "0"+s;
        }
        num+=s;
    }
    return num;
}



// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
    return stream<<N.BigInteger::to_string();
}
// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ){
    return A.compare(B) == 0;
}
// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ){
    int i = A.compare(B);
    return (i<0);
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){
    int i = A.compare(B);
    return (i<=0);
}
// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){
    int i = A.compare(B);
    return (i>0);
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){
    int i = A.compare(B);
    return (i>=0);
}
// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
    return (A.add(B));
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
    BigInteger X = A.add(B);
    A.signum = X.signum;
    A.digits = X.digits;
    return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
    return (A.sub(B));
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
    BigInteger X = A.sub(B);
    A.signum = X.signum;
    A.digits = X.digits;
    return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
    return(A.mult(B));
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
    BigInteger X = A.mult(B);
    A.signum = X.signum;
    A.digits = X.digits;
    return A;
}
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"
#include"BigInteger.h"
#include <valarray>
using namespace std;

int power = 9;
int base = 1000000000;
List negateList(List X){
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

int normalize(List& L){
    if (L.front() == 0) {
        return 0;
    }

    int sign = 1;
    if (L.front() < 0) {
        negateList(L);
        sign = -1;
    }

    L.moveBack();
    ListElement E = 0;
    int carry = 0;
    while (L.position() > 0) {
        E = L.peekPrev();
        if (E < 0) {
            E += base + carry;
            L.setBefore(E);
            carry = -1;
        }
        else {
            E += carry;
            carry = 0;
            if (E >= base) {
                carry = E / base;
                E = E % base;
            }
            L.setBefore(E);
        }
        L.movePrev();
    }
    if (carry != 0) {
        L.moveFront();
        L.insertAfter(carry);
    }
    return sign;
}

BigInteger::BigInteger(){
    signum = 0;
    digits = List();
}


BigInteger::BigInteger(long x){
    if(x == 0){
        signum = 0;
        digits = List();
        return;
    }
    if (x < 0){
        signum = -1;
    }
    else{
        signum = 1;
    }
    while (x > 0){
        digits.insertAfter(x % base);
        x = x / base;
    }
}
    

BigInteger::BigInteger(std::string s) {
    if (s.length() == 0) {
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }
    // Check if the string is non-numeric
    if (s[0] == '-') {
        signum = -1;
    } else {
        signum = 1;
    }

    // Remove sign prefix
    if (s[0] == '-' || s[0] == '+') {
        s = s.substr(1);
    }
    for (int i = 0; i < s.length(); i++) {
        if (!isdigit(s[i])) {
            throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        }
    }

    size_t max = 0;
    size_t digs = s.length();
    if (s.length() % power != 0) {
        std::string remainder = s.substr(0, s.length() % power);
        long numbers = std::stol(remainder);
        digits.insertAfter(numbers);
        s.erase(0, s.length() % power);
        digits.moveNext();
    }
    digs = s.length();

    while (max < (s.length() / power)) {
        std::string num = s.substr(digs - power, power);
        digits.insertAfter(std::stol(num));
        digs = digs - power;
        max++;
    }

    digits.moveFront();
    while (digits.position() < digits.length()) {
        long num = digits.moveNext();
        std::string s = std::to_string(num);
        while (s.length() < power) {
            s = "0" + s;
        }
        digits.eraseBefore();
        digits.insertBefore(std::stol(s));
    }
}


BigInteger::BigInteger(const BigInteger& N){
    this -> signum = N.signum;
    this -> digits = N.digits;
}

int BigInteger::sign() const{
    return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const{

    if ((this->sign() == 0) && (N.sign() == 0)){
        return 0;
    }
    else if (this->signum > N.signum){
        return 1;
    }
    else if ((this->signum < N.signum)){
        return -1;
    }
    if (this->digits.length() < N.digits.length()){
        return -1;
    }
    else if (this->digits.length() > N.digits.length()){
        return 1;
    }
    List A = this ->digits;
    List B = N.digits;
    A.moveFront();
    B.moveFront();
    if (this->signum == 1) {
        for (A.moveFront(),B.moveFront(); A.position() <A.length(), B.position() < B.length(); A.moveNext(), B.moveNext()){
            if(A.peekNext() > B.peekNext()){
                return 1;
            }
            else if (A.peekNext() < B.peekNext()){
                return -1;
            }
        }
        return 0;
    }
    else if (this->signum ==  -1) {
        for (A.moveFront(),B.moveFront(); A.position() <A.length(), B.position() < B.length(); A.moveNext(), B.moveNext()){
            if(A.peekNext() < B.peekNext()){
                return 1;
            }
            else if (A.peekNext() > B.peekNext()){
                return -1;
            }
        }
    }
    return 0;

}


void BigInteger::makeZero(){
    digits.clear();
    signum = 0;
}

void BigInteger::negate(){
    if (signum == -1){
        signum = 1;
    }
    else if (signum == 1){
        signum = -1;
    }
}

void sumList(List& S, List A, List B, int sign) {
    S.clear();
    B.moveFront();
    while (B.position() < B.length()) {
        B.setAfter(sign * B.peekNext());
        B.moveNext();
    }
    A.moveBack();
    B.moveBack();
    while (A.position() > 0 && B.position() > 0) {
        S.insertAfter(A.peekPrev() + B.peekPrev());
        A.movePrev();
        B.movePrev();
    }
    while (A.position() > 0) {
        S.insertAfter(A.peekPrev());
        A.movePrev();
    }
    while(B.position() > 0) {
        S.insertAfter(B.peekPrev());
        B.movePrev();
    }

    S.moveFront();
    while (S.front() == 0 && S.length() > 1) {
        S.eraseAfter();
    }
}
List scalarMult(List N, ListElement x){
    List C = N;
    C.moveFront();
    while(C.position()<C.length()){
        C.setAfter(C.peekNext()*x);
        C.moveNext();
    }
    return C;
}


BigInteger BigInteger::add(const BigInteger& N) const{
    BigInteger Sum;
    BigInteger copy = *this;
    List numN = N.digits;
    List numX = digits;
    List add;
    List smaller;
    List greater;
    int diff_size;
    if (this->signum < 0){
        numX = negateList(numX);
    } 
    if (N.signum < 0){
        numN = negateList(numN);
    }
    sumList(add,numX,numN,1);
    Sum.digits = add;
    Sum.signum = normalize(add);
    cout<<Sum.signum<<"hi"<<endl;
    cout<<Sum.digits<<endl;
    return Sum;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const{
    BigInteger Diff;
    BigInteger X = N;

    X.negate();
    Diff = this->add(X);

    return Diff;
    
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const {
    BigInteger Product;
    int Xsig = this->signum;
    int Nsig = N.signum;
    if (Xsig == 0 || Nsig == 0){
        return Product;}
    List ProdList;
    List Ntemp = N.digits;
    Ntemp.moveBack();
    int shift = 0;
    while (0< Ntemp.position()){
        List A = digits;
        long scale = Ntemp.peekPrev();
        scalarMult(A,scale);
        A.moveBack();
        for (int i = 0; i < shift; i++) {
            A.insertBefore(0);
        }
        List newProd = ProdList;
        sumList(ProdList,newProd,A,1);
        normalize(ProdList);
        Ntemp.movePrev();
        shift++;
    }
    Product.digits = ProdList;
    Product.signum = N.signum*signum;
    return Product;
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string(){
    string num;
    if (this->signum == -1){
        num+= "-";
    }
    if (this -> signum == 0){
        num+= '0';
        return num;
    }
    digits.moveFront();
    num += std::to_string(digits.moveNext());
    while(digits.position()<digits.length()){
        string s =std::to_string(digits.moveNext());
        while(s.length()< power){
            s = "0"+s;
        }
        num+=s;
    }
    return num;
}



// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
    return stream<<N.BigInteger::to_string();
}
// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ){
    return A.compare(B) == 0;
}
// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ){
    int i = A.compare(B);
    return (i<0);
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){
    int i = A.compare(B);
    return (i<=0);
}
// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){
    int i = A.compare(B);
    return (i>0);
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){
    int i = A.compare(B);
    return (i>=0);
}
// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
    return (A.add(B));
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
    BigInteger X = A.add(B);
    A.signum = X.signum;
    A.digits = X.digits;
    return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
    return (A.sub(B));
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
    BigInteger X = A.sub(B);
    A.signum = X.signum;
    A.digits = X.digits;
    return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
    return(A.mult(B));
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
    BigInteger X = A.mult(B);
    A.signum = X.signum;
    A.digits = X.digits;
    return A;
}
