#ifndef TWO_THREE_TREE_H
#define TWO_THREE_TREE_H
#include <iostream>
using namespace std;

template <class Key, class Val>
struct Node
{
    Key *lkey;    // left key
    Val *lval;    // left val
    Key *rkey;    // right key
    Val *rval;    // right val
    Node *left;   // left child
    Node *center; // center child
    Node *right;  // right child
};

template <class Key, class Val>
class Tree
{
    Node<Key, Val> *root; // The root of the 2-3 tree

public:
    Node<Key, Val> *Root() const { return root; }

    bool isEmpty() const { return !root; }
    // EFFECTS: return true if and only if the 2-3 tree is empty.

    Val *search(Key key) const;
    // EFFECTS: search a record with key as "key" in the 2-3
    // tree. If such a record exists, return the Val*
    // part of the record. Otherwise, return NULL.

    bool insert(Key *key, Val *val);
    // MODIFIES: this tree
    // EFFECTS: insert (key, val) pair into the 2-3 tree.
    // Return true if insertion succeeds (i.e., no duplicated
    // key exists in the tree). Otherwise, return false.

    Val *remove(Key key);
    // MODIFIES: this tree
    // EFFECTS: remove a record with key as "key" from the
    // 2-3 tree. If such a record exists, return the Val* part
    // of that record. Otherwise, return NULL.

    void inOrderPrint(ostream &os) const;
    // MODIFIES: os
    // EFFECTS: in-order traverse the 2-3 tree and print to the
    // output stream os the Val part of each record visited with
    // one record per line. To print a record stored in a node
    // at level k, you should first print 4*k spaces and then the
    // Val part of the record. Assume that the root is at level 0.

    Tree();                              // default constructor
    Tree(const Tree &t);                 // copy constructor
    Tree &operator=(const Tree &t);      // assignment operator
    ~Tree();                             // destructor
};

#endif /* TWO_THREE_TREE_H */
