//-----------------------------------------------------------------------------
// List.cpp
// Implementation file for List ADT
// Winston Yi
// wyi10
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"


// Private Constructor --------------------------------------------------------

// Node constructor
List::Node::Node(ListElement x){
   data = x;
   next = nullptr;
   prev = nullptr;
}


// Class Constructors & Destructors -------------------------------------------

// Creates a new List in the empty state.
List::List(){
   frontDummy = new Node(-1);
   backDummy = new Node(-1);
   frontDummy->next = backDummy;
   backDummy->prev = frontDummy;
   beforeCursor = frontDummy;
   afterCursor = backDummy;
   pos_cursor = 0;
   num_elements = 0;
}

// Copy Constructor.
List::List(const List& L){
   // make this an empty List
   frontDummy = new Node(-1);
   backDummy = new Node(-1);
   frontDummy->next = backDummy;
   backDummy->prev = frontDummy;
   beforeCursor = frontDummy;
   afterCursor = backDummy;
   num_elements = 0;

   // load elements of L into this List
   Node* N = L.frontDummy->next;
   while( (N->next)!=nullptr ){
      this->insertBefore(N->data);
      N = N->next;
   }
   pos_cursor = 0;
}

// Destructor
List::~List(){
    pos_cursor = 0;
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    while (length() > 0) {
        eraseAfter();
    }
    delete frontDummy;
    delete backDummy;
}


// Access functions -----------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const {
    return num_elements;
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const {
    if (length() == 0) {
        throw std::length_error("List: empty called front()");
    }
    return ((frontDummy->next)->data);
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const {
    if (length() == 0) {
        throw std::length_error("List: empty called back()");
    }
    return ((backDummy->prev)->data);
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const {
    return pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const {
    if (position() < length()) {
    	return afterCursor->data;
    } else {
        throw std::range_error("peekNext dummy Node()");
	}
}
        

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const {
    if (pos_cursor <= 0) {
        throw std::range_error("List: peekPrev dummy Node()");
    }
    return beforeCursor->data;
}

// Manipulation procedures -------------------------------------------------

void List::clear() {
    moveFront();
    int len = length();
    for (int i = 0; i < len; i++) {
        eraseAfter();
    }
    pos_cursor = 0;
}
        

void List::moveFront() {
    if (length() == 0) {
        printf("Nothing to move front on");
    }
    pos_cursor = 0;
    afterCursor = frontDummy->next;
    beforeCursor = frontDummy;
}

void List::moveBack() {
    if (length() == 0) {
        printf("Nothing to move backt on");
    }
    afterCursor = backDummy;
    beforeCursor = backDummy->prev;
    pos_cursor = length();
}

ListElement List::moveNext() {
    if (position() >= length()) {
        throw std::range_error("List: moveNext range error");
    }
    ListElement x = peekNext();
    if (position() < length()) {
        pos_cursor += 1;
    } else {
        printf("Out of bounds (lower or upper)");
    }
    afterCursor = afterCursor->next;
    beforeCursor = beforeCursor->next;
    return x;
}
    
ListElement List::movePrev() {
    if (pos_cursor <= 0) {
        throw std::range_error("List: movePrev error");
    }
    ListElement x = peekPrev();
    if (pos_cursor <= 0) {
        throw std::range_error("List: movePrev dummy Node()");
    }
    pos_cursor -= 1;
    afterCursor = afterCursor->prev;
    beforeCursor = beforeCursor->prev;
    return x;
}

void List::insertAfter(ListElement x) {
    Node* insert = new Node(x);
    if (length() == 0) {
        pos_cursor = 0;
    } 
    insert->prev = beforeCursor;
    beforeCursor->next = insert;
    insert->next = afterCursor;
    afterCursor->prev = insert;
    afterCursor = insert;

    num_elements += 1;
}
        
void List::insertBefore(ListElement x) {
    Node* insert = new Node(x);
    if (length() == 0) {
        pos_cursor = 0;
    } 
    insert->prev = beforeCursor;
    beforeCursor->next = insert;
    insert->next = afterCursor;
    afterCursor->prev = insert;
    beforeCursor = insert;

    pos_cursor += 1;
    num_elements += 1;
}
        
void List::setAfter(ListElement x) {
    if (position() == length()) {
        throw std::range_error("List: setAfter range error");
    }
    afterCursor->data = x;
}

void List::setBefore(ListElement x) {
    if (pos_cursor <= 0) {
        throw std::range_error("List: setBefore dummy Node()");
    }
    beforeCursor->data = x;
}


void List::eraseAfter() {
    if (pos_cursor >= length()) {
        throw std::range_error("List: eraseAfter pos wrong)");
    }
    if (length() == 0) {
        throw std::range_error("List: eraseAfter Empty List");
    }
    Node *N = afterCursor;
    beforeCursor->next = afterCursor->next;
    afterCursor->next->prev = beforeCursor;
    afterCursor = afterCursor->next;
    delete N;
    num_elements -= 1;
}

void List::eraseBefore() {
    if (pos_cursor <= 0) {
        throw std::range_error("List: eraseBefore pos wrong");
    }
    Node *N = beforeCursor;
    beforeCursor->prev->next = afterCursor;
    afterCursor->prev = beforeCursor->prev;
    beforeCursor = beforeCursor->prev;
    delete N;
    pos_cursor -= 1;
    num_elements -= 1;
}

int List::findNext(ListElement x) {
    if (length() == 0) {
        throw std::range_error("List: FindNext on empty list()");
    }
    Node* N = afterCursor;
    for (; (N->next)!=nullptr; N=N->next) {
        beforeCursor = beforeCursor->next;
        afterCursor = afterCursor->next;
        pos_cursor += 1;
        if (N->data == x) {
            return position();
        }
    }
    return -1;
}

int List::findPrev(ListElement x) {
    if (length() == 0) {
        throw std::range_error("List: Findprev on empty list()");
    }
    Node* N = beforeCursor;
    for (; (N->prev)!=nullptr; N=N->prev) {
        beforeCursor = beforeCursor->prev;
        afterCursor = afterCursor->prev;
        pos_cursor -= 1;
        if (N->data == x) {
            return position();
        }
    }
    return -1;
}

List List::concat(const List& L) const {
    List A;
    Node* N = frontDummy->next;
    if (length() > 0) {
        for (; (N->next) != nullptr; N=N->next) {
            A.insertBefore(N->data);
        }
    }
    if (L.length() > 0) {
        Node* N = L.frontDummy->next;
        for (; (N->next) != nullptr; N=N->next) {
            A.insertBefore(N->data);
        }
    }
    A.pos_cursor = 0;
    A.afterCursor = A.frontDummy->next;
    A.beforeCursor = A.frontDummy;
    return A;
}

void List::cleanup() {
    if (length() == 0) {
        std::cout << "bruh empty ecleanup" << std::endl;
        return;
    }
    int pos = position();
    moveFront();
	Node* N = frontDummy->next;
	Node* data = frontDummy->next;
	for (int i = 0; i < length(); i++) {
		moveFront();
		moveNext();
		for (int j = 0; j < i; j++) {
			moveNext();
		}
		while (findNext(data->data) != -1) {
            if (position() <= pos) {
                pos -= 1;
            }
			eraseBefore();
		}
		data = data->next;
		N = N->next;
	}
    moveFront();
    for (int i = 0; i < pos; i++) {
        moveNext();
    }
}


bool List::equals(const List& R) const {
	if (*this == R) {
		return true;
	} else {
		return false;
	}
}

std::ostream& operator<<( std::ostream& stream, const List& L ) {
    return stream << L.List::to_string();
}

bool operator==( const List& A, const List& B ) {
    std::string s = A.List::to_string();
    std::string k = B.List::to_string();
    if (s == k) {
        return true;
    } else{
       return false;
    }
} 

List& List::operator=( const List& L ) {
   if( this != &L ){ // not self assignment
      // make a copy of L
      List temp = L;

      // then swap the copy's fields with fields of this
      std::swap(frontDummy, temp.frontDummy);
      std::swap(backDummy, temp.backDummy);
      std::swap(num_elements, temp.num_elements);
      std::swap(pos_cursor, temp.pos_cursor);
   }
	return *this;
}
	
// to_string()
// Returns a string representation of List consisting of a space separated 
// list of data values.
std::string List::to_string() const{
    Node* N = nullptr;
    std::string s = "";
    if (List::length() == 0) {
        return s;
    }
    bool startInt = false;
    for(N=backDummy->prev; (N->prev)!=nullptr; N=N->prev){
        std::string c = std::to_string(N->data);
        if (N->data != 0) {
            startInt = true;
        }
        if (startInt == false) {
            continue;
        }
        if (N->next != backDummy and startInt) {
            for (int i = 9-c.length(); i > 0; i--) {
                s += "0";
            }
        }
        s += c;
    }
    if (s == "") {
        s = "0";
    }
    while (s[0] == '0') {
        s.erase(0, 1);
    }
    return s;
}

