#ifndef __MY_GENERIC_BST_H_
#define __MY_GENERIC_BST_H_

#include<queue>
#include<stack>

// ----------------------------------------------------------------------
// ----- CUSTOM GENERIC STACK                                       -----
// ----------------------------------------------------------------------
template<typename T>
class Stack : std::stack<T>{
public:
    T pop(){
        T = tmp = top();
        std::stack<T>::pop();
        return tmp;
    }
};

// ----------------------------------------------------------------------
// ----- CUSTOM GENERIC QUEUE                                       -----
// ----------------------------------------------------------------------
template<typename T>
class Queue : public std::queue<T> {
public:
    T dequeue(){
        T tmp = front();
        std::queue<T>::pop();
        return tmp;
    }

    void enqueue(const T& element){
        push(element);
    }
};

// ---- forward declaration
template<typename T> class BST;

// ----------------------------------------------------------------------
// ----- CUSTOM GENERIC BST                                         -----
// ----------------------------------------------------------------------
template<typename T>
class BSTNode {
public:
    BSTNode(){}

    BSTNode(const T& elt, BSTNode<T> *lhs=nullptr, BSTNode<T> *rhs=nullptr)
    : item(elt), left(lhs), right(rhs){}

    T item;
    BSTNode<T> *left;
    BSTNode<T> *right;
};

#endif
