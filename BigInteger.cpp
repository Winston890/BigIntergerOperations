//-----------------------------------------------------------------------------
// BigInteger.cpp
// Implementation file for BigInteger ADT
// Winston Yi
// wyi10
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdlib.h>
#include<cmath>
#include"BigInteger.h"
#include"List.h"

#define MAX_LEN 1000000000

// Class Constructors & Destructors -------------------------------------------

// Creates a new BigInteger in the empty state.
BigInteger::BigInteger(){
    signum = 0;
}

// Copy Constructor.
BigInteger::BigInteger(const BigInteger& N){
    this->signum = N.signum;
    this->digits = N.digits;
}

BigInteger::BigInteger(std::string s) {
    if (s[0] == '-') {
        signum = -1;
    } else {
        signum = 1;
    }
    if (s[0] == '-' or s[0] == '+') {
        s.erase(0, 1);
    }
    if (s.length() == 0) {
        throw std::invalid_argument("Need an argument BOZO");
    }
    if (!(s.find_first_not_of("0123456789") == std::string::npos)) {
        throw std::invalid_argument("Bro only digits");
    }
    long digit = 0;
    while (s[0] == '0' and s.length() > 1) {
        s.erase(0, 1);
    }
    while (s.length() > 9) {
        std::string k = s.substr(s.length() - 9, 9);
        s.erase(s.length() - 9, 9);
        digit = stol(k);
        digits.insertBefore(digit);
    }
    digit = stol(s);
    digits.insertBefore(digit);
}

// Destructor

// Access functions -----------------------------------------------------------

int BigInteger::sign() const {
    return signum;
}

int BigInteger::compare(const BigInteger& N) const {
    if (this->signum > N.signum) {
        return 1;
    } else if (this->signum < N.signum) {
        return -1;
    } else {
        List C = digits;
        List C4 = N.digits;    
        if (C.length() > C4.length()) {
            return 1;
        } else if (C4.length() > C.length()) {
            return -1;
        } else {
            C.moveBack();
            C4.moveBack();
            long thisDigit = C.back();
            long NDigit = C4.back();
            for (int i = 0; i < C.length(); i++) {
                if (thisDigit == NDigit) {
                    thisDigit = C.movePrev();
                    NDigit = C4.movePrev();
                } else {
                    if (thisDigit > NDigit) {
                        return 1;
                    } else {
                        return -1;
                    }
                }
            }
            return 0;
        }
   }
}


// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero() {
    signum = 0;
    digits.List::clear();
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate() {
    if (sign() == -1) {
        signum = 1;
    } else if (sign() == 1) {
        signum = -1;
    }
}
 
// Other Functions ---------------------------------------------------------

// BigInteger Arithmetic operations ----------------------------------------

static void negateList(List& L) {
    L.moveFront();
    for (int i = 0; i < L.length(); i++) {
        long val = L.peekNext();
        L.setAfter(-1*val);
        L.moveNext();
    }
}

static int normalizeList(List& L) { 
    L.moveFront();
    long digit = 0, carry = 0;
    for (int i = 0; i < L.length(); i++) {
        digit = L.peekNext() + carry;
        carry = 0;
        if (abs(digit) > MAX_LEN) {
            carry = digit / MAX_LEN;
        }
        L.setAfter(digit % MAX_LEN);
        L.moveNext();
    }
    if (carry > 0) {
        L.insertAfter(carry);
    }
    if (digit > 0) {
        return 1;
    } else if (digit < 0){
        return -1;
    } else {
        return 0;
    }
}

static int abs_compare(List digits, List N) {
    List C = digits;
    List C4 = N;    
    if (C.length() > C4.length()) {
        return 1;
    } else if (C4.length() > C.length()) {
        return -1;
    } else {
        C.moveBack();
        C4.moveBack();
        long thisDigit = abs(C.back());
        long NDigit = abs(C4.back());
        for (int i = 0; i < C.length(); i++) {
            if (thisDigit == NDigit) {
                thisDigit = abs(C.movePrev());
                NDigit = abs(C4.movePrev());
            } else {
                if (thisDigit > NDigit) {
                    return 1;
                } else {
                    return -1;
                }
            }
        }
    }
    return 0;
}

static void sumList(List& S, List A, List B, int sgn) {
    A.moveFront();
    B.moveFront();
    long digit = 0, carry = 0;
    if (S.length() != 0) {
        S.clear();
    }
    int min_len = (A.length() > B.length()) ? B.length() : A.length();
    for (int i = 0; i < min_len; i++) {
        digit = A.peekNext() + carry + B.peekNext();
        if (digit < -MAX_LEN) {
            digit += MAX_LEN;
            carry = 1;
        } else if (digit > MAX_LEN) {
            digit -= MAX_LEN;
            carry = 1;
        } else {
            carry = 0;
        }
        S.insertBefore(digit);
        A.moveNext();
        B.moveNext();
    }

    int diff = A.length() - S.length();
    int diff1 = B.length() - S.length();
    if (A.length() > B.length()) {
        for (int i = 0; i < diff; i++) {
            S.insertBefore(carry + A.peekNext());
            carry = 0;
            A.moveNext(); 
        }
    } else {
        for (int i = 0; i < diff1; i++) {
            S.insertBefore(carry + B.peekNext());
            carry = 0;
            B.moveNext();
        }
    }
    if (carry != 0) {
        S.insertBefore(1);
    }
}

static void equateSumList(List& S, List A) {
    if (S.length() > 0) {
        S.moveFront();
    }
    A.moveFront();
    long digit = 0, carry = 0;
    int min_len = (A.length() > S.length()) ? S.length() : A.length();
    for (int i = 0; i < min_len; i++) {
        digit = A.peekNext() + carry + S.peekNext();
        if (digit > MAX_LEN) {
            digit -= MAX_LEN;
            carry = 1;
        } else {
            carry = 0;
        }
        S.setAfter(digit);
        A.moveNext();
        S.moveNext();
    }

    int diff = A.length() - S.length();
    for (int i = 0; i < diff; i++) {
        S.insertBefore(carry + A.peekNext());
        carry = 0;
        A.moveNext();
    }
}


static int addList(List& S, List A, List B, int sgn, int sgnA) {
    A.moveFront();
    B.moveFront();
    long digit = 0, carry = 0;
    if (S.length() != 0) {
        S.clear();
    }
    int min_len = (A.length() > B.length()) ? B.length() : A.length();
    for (int i = 0; i < min_len; i++) {
        digit = sgnA*A.peekNext() + sgn*B.peekNext() + carry;
        carry = 0;
        if ((digit < 0) != (sgnA < 0) and (digit != 0)) {
            if (digit < 0) {
                digit += MAX_LEN;
            } else if (digit > 0) {
                digit -= MAX_LEN;
            }
            carry = -1*sgnA;
        }
        S.insertBefore(digit);
        A.moveNext();
        B.moveNext();
    }
    int diff = A.length() - S.length();
    for (int i = 0; i < diff; i++) {
        digit = sgnA*A.peekNext() + carry;
        carry = 0;
        if ((digit < 0) != (sgnA < 0)) {
            if (digit < 0) {
                digit += MAX_LEN;
            } else if (digit > 0) {
                digit -= MAX_LEN;
            }
            carry = -1*sgnA;
        }
        S.insertBefore(digit);
        A.moveNext(); 
    }
    return sgnA;
}

static void setPos(List& S) {
    if (S.length() == 0) {
        return;
    } else {
        S.moveFront();
        for (int i = 0; i < S.length(); i++) {
            if (S.peekNext() < 0) {
                S.setAfter(-S.peekNext());
            }
            S.moveNext();
        }
    }
}

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const {
    BigInteger B;
    List C = this->digits;
    if (this->signum*N.sign() == 1) {
        sumList(B.digits, C, N.digits, N.sign());
        B.signum = N.sign();
    } else {
        if (abs_compare(C, N.digits) > 0) {
            B.signum = addList(B.digits, C, N.digits, N.sign(), this->signum);
            if (B.sign() == -1) {
                negateList(B.digits);
            }
        } else if (abs_compare(C, N.digits) < 0) {
            B.signum = addList(B.digits, N.digits, C, this->signum, N.sign());
            setPos(B.digits);
        } else {
            B.digits.insertBefore(0);
            B.signum = 0;
        }

    }
    return B;
}

BigInteger BigInteger::sub(const BigInteger& N) const {
    BigInteger B;
    List C = this->digits;
    if (this->signum != N.sign()) {
        sumList(B.digits, C, N.digits, -1*N.sign());
        B.signum = this->signum;
    } else {
        BigInteger A = *this;
        BigInteger Z = N;
        A.signum = -A.sign();
        B = A.add(Z);
        if (abs_compare(A.digits, Z.digits) < 0) {
            B.signum = A.sign();
        } else if (abs_compare(A.digits, Z.digits) > 0) {
            B.signum = Z.sign();
        } else {
            B.signum = 0;
        }
    }
    return B;
}

static void shiftList(List& L, int p) {
    int numZero = p / 9;
    L.moveFront();
    for (int i = 0; i < numZero; i++) {
        L.insertBefore(0);
    }
    p %= 9;
    if (p > 0) { //Useless, but to fulfill functionality of shiftList in case p is not a mult of 9
        for (int i = L.position(); i < L.length(); i++) {
            printf("SHOULD NOT ENTER");
            L.setAfter(L.peekNext()*pow(10, p));
            L.moveNext();
        }
    }
}

    
static void scalarMultList(List& L, ListElement m) {
    L.moveFront();
    long digit = 0;
    for (int i = 0; i < L.length(); i++) {
        digit = L.peekNext() * m;
        L.setAfter(digit);
        L.moveNext();
    }
}
        
    
BigInteger BigInteger::mult(const BigInteger& N) const {
    BigInteger B;
    List C = this->digits;
    List D = N.digits;
    D.moveFront();
	List total;
    List temp;
    for (int i = 0; i < D.length(); i++) {
		temp = C;
        scalarMultList(temp, D.moveNext());
        normalizeList(temp);
        shiftList(temp, i*9);
        equateSumList(total, temp);
    }
    B.digits = total;
    B.signum = this->signum*N.sign();
    return B;
}
    
    

// to_string()
std::string BigInteger::to_string() {
    std::string s = "";
    if (sign() == 0) {
        s += "0";
        return s;
    } else if (sign() == -1) {
        s += "-";
    }
    s += digits.List::to_string();
    return s;
}
    
std::ostream& operator<<( std::ostream& stream, BigInteger N ) {
    return stream << N.BigInteger::to_string();
}

bool operator==( const BigInteger& A, const BigInteger& B ) {
    if (A.digits == B.digits and A.sign() == B.sign()) {
        return true;
    } else {
        return false;
    }
}

bool operator<( const BigInteger& A, const BigInteger& B ) {
    if (B.compare(A) == 1) {
        return true;
    } else {
        return false;
    }
}

bool operator<=( const BigInteger& A, const BigInteger& B ) {
    if (B.compare(A) == 1 or B.compare(A) == 0) {
        return true;
    } else {
        return false;
    }
}
    
bool operator>( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) == 1) {
        return true;
    } else {
        return false;
    }
}

bool operator>=( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) == 1 or A.compare(B) == 0) {
        return true;
    } else {
        return false;
    }
}

BigInteger operator+( const BigInteger& A, const BigInteger& B ) {
    BigInteger N = A.add(B);
    return N;
}

BigInteger operator+=( BigInteger& A, const BigInteger& B ) {
    BigInteger C = B;
    A = A.add(C);
    return A;
}

BigInteger operator-( const BigInteger& A, const BigInteger& B ) {
    BigInteger C = A;
    BigInteger D = B; 
    BigInteger N = A.sub(B);
    return N;
}

BigInteger operator-=( BigInteger& A, const BigInteger& B ) {
    BigInteger C = B;
    A = A.sub(C);
    return A;
}

BigInteger operator*( const BigInteger& A, const BigInteger& B ) {
    BigInteger C = A;
    BigInteger D = B;
    BigInteger N = A.mult(B);
    return N;
}

BigInteger operator*=( BigInteger& A, const BigInteger& B ) {
    BigInteger C = B;
    A = A.mult(C);
    return A;
}
