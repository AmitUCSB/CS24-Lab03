// intbst.cpp
// Implements class IntBST
// Amit Karthikeyan, 04/23/25

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() { 
    root = nullptr;
}

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    if(n) {
        clear(n->left);
        clear(n->right);
        delete n;
    }
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    if (!root) {
        root = new Node(value);
        root->parent = nullptr;
        return true;
    }
    return insert(value, root);
}

bool IntBST::insert(int value, Node *n) {
    if (value > n->info) {
        if (!n->right) {
            n->right = new Node(value);
            n->right->parent = n; 
            return true;
        } else {
            return insert(value, n->right);  
        }
    } else if (value < n->info) {
        if (!n->left) {
            n->left = new Node(value);
            n->left->parent = n;   
            return true;
        } else {
            return insert(value, n->left); 
        }
    } else {
        return false;  
    }
}


// print tree data pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if (n) {
        cout << n->info << " ";
        printPreOrder(n->left);
        printPreOrder(n->right);
    }
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    if(root) {
        printInOrder(root);
    }
}
void IntBST::printInOrder(Node *n) const {
    if (n) {
        printInOrder(n->left);
        cout << n->info << " ";
        printInOrder(n->right);
    }
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
}

void IntBST::printPostOrder(Node *n) const {
    if (n) {
        printPostOrder(n->left);
        printPostOrder(n->right);
        cout << n->info << " ";
    }
}

// return sum of values in tree
int IntBST::sum() const {
    return sum(root); 
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    if (n) {
        return n->info + sum(n->left) + sum(n->right);
    } else {
        return 0;
    }
}

// return count of values
int IntBST::count() const {
    return count(root);
}

// recursive helper for count
int IntBST::count(Node *n) const {
    if (n) {
        return 1 + count(n->left) + count(n->right);
    } else {
        return 0;
    }
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
    while(n) {
        if (value == n->info) {
            return n;
        }
        if (value > n->info) {
            n = n->right;
        } else {
            n = n->left;
        }
    }
    return nullptr; 
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
    Node* p = root;
    while(p) {
        if (value == p->info) {
            return true;
        }
        if (value > p->info) {
            p = p->right;
        } else {
            p = p->left;
        }
    }
    return false; 
}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
    Node* p = getNodeFor(value, root);
    if(p->left) {
        p = p->left;
        while(p->right) {
            p = p->right;
        }
        return p;
    } else {
        while (p->parent && p == p->parent->left) {
            p = p->parent;
        }
        if (p->parent) {
            return p->parent;
        } else {
            return nullptr;
        }
    }
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
    Node* p = getNodeFor(value, root);
    if(p->left) {
        p = p->left;
        while(p->right) {
            p = p->right;
        }
        return p->info;
    } else {
        while (p->parent && p == p->parent->left) {
            p = p->parent;
        }
        if (p->parent) {
            return p->parent->info;
        } else {
            return 0;
        }
    }
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
    Node* p = getNodeFor(value, root);
    if(!p) return nullptr;
    if(p->right) {
        p = p->right;
        while(p->left) {
            p = p->left;
        }
        return p;
    } else {
        while (p->parent && p == p->parent->right) {
            p = p->parent;
        }
        if (p->parent) {
            return p->parent;
        } else {
            return nullptr;
        }
    }
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
    Node* p = getNodeFor(value, root);
    if(p->right) {
        p = p->right;
        while(p->left) {
            p = p->left;
        }
        return p->info;
    } else {
        while (p->parent && p == p->parent->right) {
            p = p->parent;
        }
        if (p->parent) {
            return p->parent->info;
        } else {
            return 0;
        }
    }
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value){
    Node* p = getNodeFor(value, root);
    if (!p) {
        return false;
    }
    if (!p->left && !p->right) {
        if (!p->parent) {
            root = nullptr;
        } else {
            if (p == p->parent->left)
                p->parent->left = nullptr;
            else
                p->parent->right = nullptr;
        }
        delete p;
        return true;
    }
    if (!p->left || !p->right) {
        Node* q = (p->left) ? p->left : p->right;
        if (!p->parent) {
            root = q;
        } else {
            if (p == p->parent->left)
                p->parent->left = q;
            else
                p->parent->right = q;
        }
        q->parent = p->parent;
        delete p;
        return true;
    }
    Node* r = p->right;
    while (r->left) {
        r = r->left;
    }
    p->info = r->info;
    if (r->parent->left == r)
        r->parent->left = r->right;
    else
        r->parent->right = r->right;

    if (r->right)
        r->right->parent = r->parent;

    delete r;
    return true;
}
