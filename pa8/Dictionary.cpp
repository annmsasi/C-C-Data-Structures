
/****************************************************************************************
Ann Sasi
pa8
CruzID asasi
Dictionary.cpp

*****************************************************************************************/
#include<iostream>
#include<string>
#include "Dictionary.h"
using namespace std;

#define RED -1
#define BLACK 1

Dictionary::Node::Node(keyType K, valType V){
    key = K;
    val = V;
    parent= nullptr;
    left = nullptr;
    right = nullptr;
    color = RED;
}
Dictionary::Dictionary(){
    nil = new Node("nil", -1);
    nil->color = BLACK;
    root = nil;
    current = nil;
    num_pairs = 0;
}

   // Copy constructor.
Dictionary::Dictionary(const Dictionary& D){
    nil = new Node("nil", -1);
    nil->color = BLACK;
    root = nil;
    current = nil;
    num_pairs = 0;
    preOrderCopy(D.root, D.nil);
   }

Dictionary::~Dictionary(){
    postOrderDelete(root);
    delete nil;
   }

   // inOrderString()
   // Appends a string representation of the tree rooted at R to string s. The
   // string appended consists of: "key : value \n" for each key-value pair in
   // tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        inOrderString(s, R->left);
        s.append(R->key);
        s.append(" : ");
        s.append(std::to_string(R->val));
        s.append("\n");
        inOrderString(s, R->right);
    }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string will consist of keys only, with the order determined by a pre-order
// tree walk. The keys stored in black Nodes will be appended as "key\n", and
// the keys stored in red Nodes will be appended as "key (RED)\n". The output 
// of this function is demonstrated in /Examples/pa8/DictionaryClient-out.  
void Dictionary::preOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        s.append(R->key);
        s.append(R->color == RED ? " (RED)" : "");
        s.append("\n");
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}


// BST_insert()
// Inserts a copy of the Node *M into this Dictionary. Used by preOrderCopy().
void Dictionary::BST_insert(Node* M){

}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N){
    if (R == N) {
        return;
    }
    setValue(R->key, R->val);
    preOrderCopy(R->left, N);
    preOrderCopy(R->right, N);
}
// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R.
void Dictionary::postOrderDelete(Node* R){
    if (R == nil){
        return;
    }
    postOrderDelete(R->left);
    postOrderDelete(R->right);
    delete(R);
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
    if(R == nil){
        return nil;
    }
    if (k == R -> key){
        return R;
    }
    else if (k<R->key){
        return search(R->left,k);
    }
    else{
        return search(R->right,k);
    }
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R){
    if (R != nil ) {
        while (R->left != nil) {
            R = R->left;
        }
        return R;
    }
    return nil;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R){
    if (R != nil ) {
        while (R->right != nil) {
            R = R->right;
        }
        return R;
    }
    return nil;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N){
    if(N->right!= nil){
        return findMin(N->right);
    }
    Node* y = N->parent;
    while (y != nil && N == y->right){
        N = y;
        y = y->parent;
    }
    return y;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N){
    if(N->left != nil){
        return findMax(N->left);
    }
    Node* y = N->parent;
    while (y != nil && N == y->left){
        N = y;
        y = y->parent;
    }
    return y;
}

// RBT Helper Functions (Optional) -----------------------------------------

// LeftRotate()
void Dictionary::LeftRotate(Node* N){
    Node* temp = N->right;
    N->right = temp->left;
    if (temp->left != nil){
        temp->left->parent = N;
    }
    temp->parent = N->parent;
    if (N->parent == nil){
        root = temp;
    }
    else if(N->parent->left == N){
        N->parent->left = temp;
    }
    else{
        N->parent->right = temp;
    }
    temp->left = N;
    N->parent = temp;
}

// RightRotate()
void Dictionary::RightRotate(Node* N){
    Node* temp = N->left;
    N->left = temp->right;
    if (temp->right != nil){
        temp->right->parent = N;
    }
    temp->parent = N->parent;
    if (N->parent == nil){
        root = temp;
    }
    else if(N->parent->right == N){
        N->parent->right = temp;
    }
    else{
        N->parent->left = temp;
    }
    temp->right = N;
    N->parent = temp;
}

// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node* N){
    while(N != root && N->parent->color == RED){
        if(N->parent == N->parent->parent->left){
            Node* y = N->parent->parent->right;
            if(y->color == RED){
                N->parent->color = BLACK;
                y->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            }
            else{
                if (N == N->parent->right){
                    N = N->parent;
                    LeftRotate(N);
                }
                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                RightRotate(N->parent->parent);
            }
        }
        else{
            Node* y = N->parent->parent->left;
            if (y->color == RED){
                N->parent->color = BLACK;
                y->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            }
            else{
                if (N == N->parent->left){
                    N = N->parent;
                    RightRotate(N);
                }
                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                LeftRotate(N->parent->parent);
            }
        }
    }
    root->color = BLACK;
}


// RB_Transplant()
void Dictionary::RB_Transplant(Node* u, Node* v){
    if(u->parent == nil){
        root = v;
    }
    else if (u == u ->parent->left){
        u->parent->left = v;
    }
    else{
        u->parent->right = v;
    }
    v->parent = u->parent;
}

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node* N){
    while(N != root && N->color == BLACK){
        if(N ==N->parent->left){
            Node* W = N->parent->right;
            if(W->color == RED){
                W->color = BLACK;
                N->parent->color = RED;
                LeftRotate(N->parent);
                W = N->parent->right;
            }
            if(W->left->color == BLACK && W->right->color== BLACK){
                W->color = RED;
                N = N->parent;
            }
            else{
                if(W->right->color == BLACK){
                    W->left->color = BLACK;
                    W->color = RED;
                    RightRotate(W);
                    W = N->parent->right;
                }
                W->color = N->parent->color;
                N->parent->color = BLACK;                 // case 4
                W->right->color = BLACK;                  // case 4
                LeftRotate(N->parent);                // case 4
                N = root;                  
            }
        }
        else{
            Node* W = N->parent->left;
            if (W->color == RED){        
                W->color = BLACK;                        // case 5
                N->parent->color = RED;                   // case 5
                RightRotate(N->parent);               // case 5
                W = N->parent->left;
            }
            if (W->right->color == BLACK && W->left->color == BLACK){
                W->color = RED;                   // case 6
                N = N->parent;  
            }
            else {
                if (W->left->color == BLACK){
                    W->right->color = BLACK;               // case 7
                    W->color = RED;                     // case 7
                    LeftRotate(W);                    // case 7
                    W = N->parent->left; 
                }
                  // case 7
                W->color =N->parent->color;               // case 8
                N->parent->color = BLACK;                 // case 8
                W->left->color = BLACK;                   // case 8
                RightRotate(N->parent);               // case 8
                N = root;  
            }       
        }
    }
    N->color= BLACK;
}

// RB_Delete()
void Dictionary::RB_Delete(Node* N){
    Node* y = N;
    int y_original_color = y->color;
    Node* x = nil;
    if (N->left == nil){
        x = N->right;
        RB_Transplant(N, N->right);
    }
    else if (N->right == nil){
        x = N->left;
        RB_Transplant(N, N->left);
    }
    else{ 
        y = findMin(N->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == N){
            x->parent = y;
        }
        else {
            RB_Transplant(y, y->right);
            y->right = N->right;
            y->right->parent = y;
        }
        RB_Transplant(N, y);
        y->left = N->left;
        y->left->parent = y;
        y->color = N->color;
        }
        if (y_original_color == BLACK){
            RB_DeleteFixUp(x);
    }
}


// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const{
    return this->num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const{
    if (search(root, k) == nil){
        return false;
    }
    return true;
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const{
    Node * X = search(root, k);
    if (X == nil) {
        throw std::logic_error("Dictionary: getValue(): key \"" + k + "\" does not exist");
    }
    return X ->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const{
    return (current != nil);
}
// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const{
    if (!hasCurrent()) {
        throw logic_error("Dictionary: currentKey(): current undefined");
    }
    return current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const{
    if (hasCurrent() == false) {
        throw logic_error("Dictionary: currentVal(): current undefined");
    }
    return current->val;
}


// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear(){
    postOrderDelete(root);
    root = nil;
    current = nil;
    num_pairs = 0;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v){
    Node* y = nil;
    Node* x = root;
    Node* z = search(root, k);
    if (z != nil){
        z->val = v;
        return;
    }
    z = new Node(k, v);
    num_pairs++;
    while (x != nil){
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == nil)
        root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;

    z->left = nil;
    z->right = nil;
    z->color = RED;
    RB_InsertFixUp(z);
}



// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k){
    if (contains(k) == false) {
        throw logic_error("Dictionary: remove(): key \"" + k + "\" does not exist");
    }
    Node* N = search(root, k);
    if (N == current) {
        current = nil;
    }
    RB_Delete(N);
    num_pairs--;
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin(){
    current = findMin(root);
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end(){
    current = findMax(root);
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next(){
    if (current == nil) {
        throw invalid_argument("Dictionary does not exist");
        return;
        }
    current = findNext(current);
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev(){
    if (current == nil) {
        throw invalid_argument("Dictionary does not exist");
        return;
    }
    current = findPrev(current);
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const{
    string s;
    inOrderString(s,root);
    return s;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. The key order is 
// given by a pre-order tree walk. The keys stored in black Nodes will appear in
// the returned string as "key\n", and the keys stored in red Nodes will appear 
// as "key (RED)\n".  The output of this function is demonstrated in 
// /Examples/pa8/DictionaryClient-out.
std::string Dictionary::pre_string() const{
    string s;
    preOrderString(s,root);
    return s;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const{
    return (to_string() == D.to_string());
}


// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
ostream& operator<<( std::ostream& stream, Dictionary& D ){
    return stream << D.to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ){
    return (A.equals(B));
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ){
    Dictionary temp = D;
    cout<<"here"<<endl;
    if(this != &D){    
        clear();
        preOrderCopy(D.root, nil);
        cout<<"hee"<<endl;
    }
    return *this;
}
