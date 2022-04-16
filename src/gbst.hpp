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

#endif
