/****************************************************************************************
Ann Sasi
pa7
CruzID asasi
Dictionary.cpp

*****************************************************************************************/
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"
using namespace std;

// Helper Functions (Optional) ---------------------------------------------
Dictionary::Node::Node(keyType K, valType V){
    key = K;
    val = V;
    parent= nullptr;
    left = nullptr;
    right = nullptr;
}
Dictionary::Dictionary(){
    nil = new Node("", 0);
    nil -> left = nil;
    nil -> right = nil;
    nil -> parent = nil;
    root = nil;
    current = nil;
    num_pairs = 0;
}
Dictionary::Dictionary(const Dictionary& D){
    nil = new Node("", 0);
    nil -> parent = nil;
    root = nil;
    current = nil;
    num_pairs = 0;
    preOrderCopy(D.root,nil);
}
Dictionary::~Dictionary(){
    postOrderDelete(root);
    delete nil;
   }
   // inOrderString()
   // Appends a string representation of the tree rooted at R to string s. The
   // string appended consists of: "key : value \n" for each key-value pair in
   // tree R, arranged in order by keys.
    void Dictionary::inOrderString(std::string& s, Node* R) const{
        if (R->key != "" && R->val != 0){
            inOrderString(s, R-> left);
            s+= R->key + " : " + std::to_string(R->val) + "\n";
            inOrderString(s, R->right);
        }
   }

   // preOrderString()
   // Appends a string representation of the tree rooted at R to s. The appended
   // string consists of keys only, separated by "\n", with the order determined
   // by a pre-order tree walk.
    void Dictionary::preOrderString(std::string& s, Node* R) const{
        if (R->key != "" && R->val != 0){
            s+= R->key + "\n";
            preOrderString(s, R-> left);
            preOrderString(s, R->right);
        } 
   }

   // preOrderCopy()
   // Recursively inserts a deep copy of the subtree rooted at R into this 
   // Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N) {
    if (R->key != "" && R->val != 0){
        //std::cout << "Before SetValue\n";
        //std::cout << R->key << " " << R->val << "\n";
        setValue(R->key,R->val);
        //std::cout << "After SetValue\n";
        preOrderCopy(R->left,N);
        preOrderCopy(R->right,N);
    }
}


   // postOrderDelete()
   // Deletes all Nodes in the subtree rooted at R.
   void Dictionary::postOrderDelete(Node* R){
    if (R->key == "" && R->val == 0){
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
    if ((R->key == "" && R->val == 0) || k == R ->key){
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
    Dictionary::Node* Dictionary::findMin(Node* R) {
    if (R->key != "" && R->val != 0) {
        while (R->left->key != "" && R->left->val != 0) {
            R = R->left;
        }
        return R;
    }
    return nil;
}

   // findMax()
   // If the subtree rooted at R is not empty, returns a pointer to the 
   // rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R) {
    if (R->key != "" && R->val != 0) {
        while (R->right->key != "" && R->right->val != 0) {
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
        if(N->right->key != "" && N->right->val != 0){
            return findMin(N->right);
        }
        Node* y = N->parent;
        while (y->key != "" && y->val != 0 && N == y->right){
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
        if(N->left->key != "" && N->left->val != 0){
            return findMax(N->left);
        }
        Node* y = N->parent;
        while (y->key != "" && y->val != 0 && N == y->left){
            N = y;
            y = y->parent;
        }
        return y;
   }

   // Destructor



   // Access functions --------------------------------------------------------

   // size()
   // Returns the size of this Dictionary.
   int  Dictionary::size() const{
    return num_pairs;
   }

   // contains()
   // Returns true if there exists a pair such that key==k, and returns false
   // otherwise.
   bool  Dictionary::contains(keyType k) const{
    if (search(root, k) == nil){
        return false;
    }
    return true;
   }

   // getValue()
   // Returns a reference to the value corresponding to key k.
   // Pre: contains(k)
   valType&  Dictionary::getValue(keyType k) const{
    Node * X = search(root, k);
    if (X == nil) {
        throw std::logic_error("Dictionary: getValue(): key \"" + k + "\" does not exist");
    }
    return X ->val;
   }
   // hasCurrent()
   // Returns true if the current iterator is defined, and returns false 
   // otherwise.
   bool  Dictionary::hasCurrent() const{
    return (current->key != "");
   }

   // currentKey()
   // Returns the current key.
   // Pre: hasCurrent() 
   keyType  Dictionary::currentKey() const{
    if (current == nil){
        throw logic_error("currentKey() pre-condition: contains(k)");
    }
     return current->key;

   }

   // currentVal()
   // Returns a reference to the current value.
   // Pre: hasCurrent()
   valType&  Dictionary::currentVal() const{
     if (current == nil){
        throw logic_error("getValue() pre-condition: contains(k)");
    }
     return current->val;
   }


   // Manipulation procedures -------------------------------------------------

   // clear()
   // Resets this Dictionary to the empty state, containing no pairs.
   void  Dictionary::clear(){
    postOrderDelete(root);
    root = nil;
    current = nil;
    num_pairs = 0;
   }

   // setValue()
   // If a pair with key==k exists, overwrites the corresponding value with v, 
   // otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v) {
    //std::cout << "Before Search\n";
    Node *N = search(root, k);
    //std::cout << "After Search\n";
    if (N != nil) {
        N->val = v;
    }
    else {
        Node* y = new Node(k, v);
        y->left = y->right = nil; 
        Node* search = root;
        Node* parent = nil;

        while (search != nil) {
            parent = search;
            if (y->key < search->key) {
                search = search->left;
            }
            else {
                search = search->right;
            }
        }

        y->parent = parent;

        if (parent == nil) {
            root = y;
        }
        else if (y->key < parent->key) {
            parent->left = y;
        }
        else {
            parent->right = y;
        }

        num_pairs++;
    }
}


   // remove()
   // Deletes the pair for which key==k. If that pair is current, then current
   // becomes undefined.
   // Pre: contains(k).
   void  Dictionary::transplant(Dictionary* D, Dictionary::Node* U, Dictionary::Node* V){
    if (U->parent->key == "" && U->parent->val == 0){
        D->root = V;
    }
    else if (U == U->parent->left){
        U->parent->left = V;
    }
    else{
        U->parent->right = V;
    }
    if (V->key != "" && V->val != 0){
        V->parent = U->parent;
    }
   }
   
   void Dictionary::remove(keyType k) {
    Node *N = search(root, k);
    if (N == nil) {
        throw std::invalid_argument("Dictionary: remove(): key \"" + k + "\" does not exist");
        return;
    }

    if (N->left == nil) {
        transplant(this, N, N->right);
    } else if (N->right == nil) {
        transplant(this, N, N->left);
    } else {
        Node* Y = findMin(N->right);
        if (Y->parent != N) {
            transplant(this, Y, Y->right);
            Y->right = N->right;
            Y->right->parent = Y;
        }
        transplant(this, N, Y);
        Y->left = N->left;
        Y->left->parent = Y;
    }

    if (N == current) {
        current = nil;
    }
    delete N;
    num_pairs--;
}

   // begin()
   // If non-empty, places current iterator at the first (key, value) pair
   // (as defined by the order operator < on keys), otherwise does nothing. 
   void  Dictionary::begin(){
    current = findMin(root);
   }

   // end()
   // If non-empty, places current iterator at the last (key, value) pair
   // (as defined by the order operator < on keys), otherwise does nothing. 
   void  Dictionary::end(){
    current = findMax(root);
   }

   // next()
   // If the current iterator is not at the last pair, advances current 
   // to the next pair (as defined by the order operator < on keys). If 
   // the current iterator is at the last pair, makes current undefined.
   // Pre: hasCurrent()
   void  Dictionary::next(){
    if (current == nil) {
        throw std::invalid_argument("Dictionary does not exist");
        return;
    }
    current = findNext(current);
   }

   // prev()
   // If the current iterator is not at the first pair, moves current to  
   // the previous pair (as defined by the order operator < on keys). If 
   // the current iterator is at the first pair, makes current undefined.
   // Pre: hasCurrent()
   void  Dictionary::prev(){
        if (current == nil) {
            throw std::invalid_argument("Dictionary does not exist");
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
   // Returns a string consisting of all keys in this Dictionary. Consecutive
   // keys are separated by newline "\n" characters. The key order is given
   // by a pre-order tree walk.
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
   std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
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
Dictionary& Dictionary::operator=(const Dictionary& D) {
    if (this != &D) {
        // Create a temporary copy of the other dictionary
        Dictionary temp = D;

        swap(nil, temp.nil);
        swap(root, temp.root);
        swap(current, temp.current);
        swap(num_pairs, temp.num_pairs);
    }
    return *this;
}

