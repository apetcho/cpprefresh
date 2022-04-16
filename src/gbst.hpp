#ifndef __MY_GENERIC_BST_H_
#define __MY_GENERIC_BST_H_

#include<queue>
#include<stack>

template<typename T>
class Stack : std::stack<T>{
public:
    T pop(){
        T = tmp = top();
        std::stack<T>::pop();
        return tmp;
    }
};

#endif
