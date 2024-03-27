/****************************************************************************************
Ann Sasi
pa6
CruzID asasi
List.cpp

*****************************************************************************************/
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"
#include <valarray>
using namespace std;

List::Node::Node(ListElement x){
    data = x;
    next = nullptr;
    prev = nullptr;
}

List::List(){
    frontDummy =  new Node(0);
    backDummy =  new Node(0);
    frontDummy -> next = backDummy;
    backDummy -> prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

   // Copy constructor.
   List::List(const List& L){
    frontDummy =  new Node(0);
    backDummy =  new Node(0);
    frontDummy -> next = backDummy;
    backDummy -> prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
    Node* N = L.frontDummy -> next;
    while(N != L.backDummy){
        int data = N -> data;
        this -> insertBefore(data);
        N = N -> next;
    }
    this -> moveFront();
   }

   // Destructor
   List::~List(){
    this -> clear();
    delete this -> frontDummy;
    delete this -> backDummy;
    }

   // Access functions --------------------------------------------------------

   // length()
   // Returns the length of this List.
   int List::length() const{
    return (this -> num_elements);
   }

   // front()
   // Returns the front element in this List.
   // pre: length()>0
   ListElement List::front() const{
    if (this -> num_elements == 0){
        throw std::length_error("List: Front(): empty List");
    }
    return(frontDummy -> next -> data);
   }

   // back()
   // Returns the back element in this List.
   // pre: length()>0
   ListElement List::back() const{
        if (this -> num_elements == 0){
        throw std::length_error("List: back(): empty List");
    }
    return(backDummy -> prev -> data);
   }
   

   // position()
   // Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const {
    if (pos_cursor < 0 || pos_cursor > num_elements) {
        throw std::range_error("List: position(): invalid cursor position");
    }
    return pos_cursor;
}

   // peekNext()
   // Returns the eleanment after the cursor.
   // pre: position()<length()
   ListElement List::peekNext() const{
    if (this -> num_elements == 0){
        throw std::range_error("List: peekNext(): empty List");
    }
    else if(pos_cursor >= num_elements){
        throw std::range_error("List: peekNext(): cursor >list");
    }
    
    return (afterCursor -> data);
   }

   // peekPrev()
   // Returns the element before the cursor.
   // pre: position()>0
   ListElement List::peekPrev() const{
    if (this -> num_elements == 0 ||pos_cursor <= 0){
        throw std::range_error("List: peekPrev(): empty List");
    }
    if (this -> pos_cursor == 0){
        throw std::range_error("peekPrev(): cursor at front");
    }
    return (beforeCursor -> data);
   }

   // Manipulation procedures -------------------------------------------------

   // clear()
   // Deletes all elements in this List, setting it to the empty state.
   void List::clear(){
    moveFront();
    while(num_elements >0){
        eraseAfter();
    }
   }

   // moveFront()
   // Moves cursor to position 0 in this List.
   void List::moveFront(){

    beforeCursor = frontDummy;
    afterCursor = frontDummy -> next;
    pos_cursor = 0;
   }

   // moveBack()
   // Moves cursor to position length() in this List.
   void List::moveBack(){
    beforeCursor = backDummy -> prev;
    afterCursor = backDummy;
    pos_cursor = num_elements;
   }


   // moveNext()
   // Advances cursor to next higher position. Returns the List element that
   // was passed over. 
   // pre: position()<length() 
   ListElement List::moveNext(){
    if (position()> length()){
        throw std::range_error("List: moveNext(): position > List");
    }
    beforeCursor = beforeCursor -> next;
    afterCursor = afterCursor -> next;
    pos_cursor ++;
    return beforeCursor ->data;
   }

   // movePrev()
   // Advances cursor to next lower position. Returns the List element that
   // was passed over. 
   // pre: position()>0
   ListElement List::movePrev(){
    if (position()<= 0){
        throw std::range_error("List: moveprev(): position > List");
    }
    afterCursor = afterCursor -> prev;
    beforeCursor = beforeCursor -> prev;
    pos_cursor --;
    return afterCursor ->data;
   }
   // insertAfter()
   // Inserts x after cursor.
void List::insertAfter(ListElement x) {
    if (this ->num_elements < 0 || this -> pos_cursor > num_elements) {
        throw std::range_error("List: insertAfter(): invalid cursor position");
    }
    Node *temp = new Node(x);
    temp->prev = beforeCursor;
    temp->next = afterCursor;
    beforeCursor->next = temp;
    afterCursor->prev = temp;
    afterCursor = temp;
    num_elements++;
}

   // insertBefore()
   // Inserts x before cursor.
void List::insertBefore(ListElement x) {
    if (this->pos_cursor < 0 || this->pos_cursor > num_elements) {
        throw std::range_error("List: insertBefore(): invalid cursor position");
    }
    Node *temp = new Node(x);
    temp->next = afterCursor;
    temp->prev = beforeCursor;
    afterCursor->prev = temp;
    beforeCursor->next = temp;
    beforeCursor = temp;
    pos_cursor++;
    num_elements++;
}


   // setAfter()
   // Overwrites the List element after the cursor with x.
   // pre: position()<length()
   void List::setAfter(ListElement x){
    if (position() >= length()){
        throw std::range_error("List: setAfter(): position > List");
    }
    afterCursor -> data = x;
   }

   // setBefore()
   // Overwrites the List element before the cursor with x.
   // pre: position()>0
   void List::setBefore(ListElement x){
    if (position() <= 0){
        throw std::range_error("List: setBefore(): position > List");
    }
    beforeCursor -> data = x;
   }
   // eraseAfter()
   // Deletes element after cursor.
   // pre: position()<length()
void List::eraseAfter() {
    if (pos_cursor >= num_elements) {
        throw std::range_error("List: eraseAfter(): invalid cursor position");
    }
    Node *temp = afterCursor;
    temp->next->prev = beforeCursor;
    beforeCursor->next = temp->next;
    afterCursor = temp -> next;
    delete temp;
    num_elements--;
}

void List::eraseBefore() {
    if (pos_cursor <= 0) {
        throw std::range_error("List: eraseBefore(): invalid cursor position");
    }
    Node *temp = beforeCursor;
    temp->prev->next = afterCursor;
    afterCursor->prev = temp->prev;
    beforeCursor = temp -> prev;
    delete temp;
    num_elements--;
    pos_cursor--;
}


   // Other Functions ---------------------------------------------------------

   // findNext()
   // Starting from the current cursor position, performs a linear search (in 
   // the direction front-to-back) for the first occurrence of element x. If x
   // is found, places the cursor immediately after the found element, then 
   // returns the final cursor position. If x is not found, places the cursor 
   // at position length(), and returns -1. 
int List::findNext(ListElement x) {
    while(position() < length()){
        if (moveNext()== x){
            return position();
        }
    }
    moveBack();
    return -1;
}



   // findPrev()
   // Starting from the current cursor position, performs a linear search (in 
   // the direction back-to-front) for the first occurrence of element x. If x
   // is found, places the cursor immediately before the found element, then
   // returns the final cursor position. If x is not found, places the cursor 
   // at position 0, and returns -1. 
   int List::findPrev(ListElement x){
    while(position() > 0){
        if (movePrev()== x){
            return pos_cursor;
        }
    }
    moveFront();
    return -1;
}

   // cleanup()
   // Removes any repeated elements in this List, leaving only unique elements.
   // The order of the remaining elements is obtained by retaining the frontmost 
   // occurrance of each element, and removing all other occurances. The cursor 
   // is not moved with respect to the retained elements, i.e. it lies between 
   // the same two retained elements that it did before cleanup() was called.
void List::cleanup() {
    if (frontDummy == nullptr || backDummy == nullptr) return;
    Node *cur = frontDummy->next;
    int pos = 0;
    while (cur != backDummy) {
        Node *comp = cur->next;
        pos = 0;
        while (comp != backDummy) {
            pos++;
            if (comp->data == cur->data) {
                if (comp == beforeCursor) {
                    eraseBefore();
                    comp = cur->next;
                    continue;
                }
                else if (comp == afterCursor) {
                    eraseAfter();
                    comp = cur->next;
                    continue;
                }
                else {
                    comp->prev->next = comp->next;
                    comp->next->prev = comp->prev;
                    Node *temp = comp->next;
                    delete comp;
                    comp = temp;
                    num_elements--;
                    if (pos <= pos_cursor){
                        pos_cursor--;
                    }
                    // If the last element is removed, update backDummy->prev
                    if (temp == backDummy) {
                        backDummy->prev = temp->prev;
                    }
                    continue;
                }
            }
            comp = comp->next;
        }
        cur = cur->next;
    }
}



    // while (cur != backDummy)
    // {
    //     Node *comp = cur -> next;
    //     while(comp != backDummy){
    //         Node* nextComp = comp->next;
    //         if (comp -> data == cur -> data){
    //             if (comp == beforeCursor){
    //                 eraseBefore();
    //             }
    //             else if (comp == afterCursor){
    //                 eraseAfter();
    //         }else{
    //             comp->prev->next = comp->next;
    //             comp->next->prev = comp->prev;
    //             delete(comp);
    //             num_elements--;}
    //     }
    //     comp = nextComp;
    // }
    

 
   // concat()
   // Returns a new List consisting of the elements of this List, followed by
   // the elements of L. The cursor in the returned List will be at postion 0.
   List List::concat(const List& L) const{
        List cat;
        Node *A = this -> frontDummy -> next;
        Node *B = L.frontDummy -> next;
        while (A != this -> backDummy){
            cat.insertBefore(A -> data);
            A = A -> next;
        }
        while (B != L.backDummy){
            cat.insertBefore(B -> data);
            B = B -> next;
        }
        cat.pos_cursor = 0;
        cat.beforeCursor = cat.frontDummy;
        cat.afterCursor = cat.frontDummy -> next;
        return cat;

   }

   // to_string()
   // Returns a string representation of this List consisting of a comma 
   // separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const {
    if(length() == 0) return "()";
    std::string conct = "(";
    Node *A = this ->frontDummy->next; 
    while (A->next != this-> backDummy){
        conct += std::to_string(A->data) + ", ";
        A = A->next;
    };
    conct += std::to_string(A->data);
    // for (A; A != this -> backDummy; A = A->next) {
    //     cout << "Current node data: " << A->data << endl; // Debug print statement
    //     conct += std::to_string(A->data) + " ";
    // }
    conct += ")";
    return conct;
}



    // equals()
    // Returns true if and only if this List is the same integer sequence as R.
    // The cursors in this List and in R are unchanged.
    bool List::equals(const List& R) const{
        if (this -> num_elements != R.num_elements){
            return false;
        }
        Node *A = this -> frontDummy -> next;
        Node *B = R.frontDummy -> next;
        while(A != backDummy){
            if ((A -> data) != (B -> data)){
                return false;
            }
            A = A -> next;
            B = B -> next;
        }
        return true;
    }


    // Overriden Operators -----------------------------------------------------

    // operator<<()
    // Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ){
        stream << L.to_string();
        return stream;

    }

    // operator==()
    // Returns true if and only if A is the same integer sequence as B. The 
    // cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ){
        return A.equals(B);
    }

    // operator=()
    // Overwrites the state of this List with state of L.
    List& List::operator=( const List& L ){
            if (this != &L) {
      List temp = L;
      std::swap(frontDummy, temp.frontDummy);
      std::swap(backDummy, temp.backDummy);
      std::swap(num_elements, temp.num_elements);
      std::swap(beforeCursor, temp.beforeCursor);
      std::swap(afterCursor, temp.afterCursor);
      std::swap(pos_cursor, temp.pos_cursor);
    }
    return *this;
    }
