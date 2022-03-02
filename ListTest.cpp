// Winston Yi
// wyi10
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

int main(){
   List A, B, S;

   cout << endl;
   A.insertBefore(1);
   A.insertAfter(2);
   A.moveNext();
   A.insertBefore(3);
   A.insertAfter(5);
   A.insertAfter(4);
   A.movePrev();
   for (int i = 5; i > 0; i--) {
    B.insertAfter(i);
   }
   cout << "A find next is " << A.findNext(5) << endl;
   cout << "A find prev is " << A.findPrev(1) << endl;
   cout << "A.front() = " << A.front() << endl;
   cout << "A.back() = " << A.back() << endl;
   cout << "A = " << A << endl;
   cout << "B = " << B << endl;
   cout << "B==A is " << (B==A?"true":"false") << endl;
   List K = A.concat(B);
   cout << "K = " << K << endl;
   A.moveNext();
   cout << "A.position() = " << A.position() << endl;
   A.movePrev();
   A.cleanup();
   cout << "A = " << A << endl;
   A.clear();
   cout << "A = " << A << endl;
   cout << endl;
   return 0;
}
