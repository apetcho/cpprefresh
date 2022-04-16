#ifndef __MY_GENERIC_BST_H_
#define __MY_GENERIC_BST_H_

#include<queue>
#include<stack>
#include<iostream>

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
// ----- CUSTOM GENERIC BSTNOde                                     -----
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

// ----------------------------------------------------------------------
// ----- CUSTOM GENERIC BST                                         -----
// ----------------------------------------------------------------------
template<typename T>
class BST{
public:
    // ---- default ctor
    BST(){ root = nullptr; }
    // ---- dtor
    ~BST(){
        clear();
    }
    // ----- clear()
    void clear(){
        clear(root);
        root = nullptr;
    }
    // ----- is_empty()
    bool is_empty() const {
        return root == nullptr;
    }
    // ----- preorder()
    void preorder(){ preorder(root); }
    // ----- inorder()
    void inorder(){ inorder(root); }
    // ----- postorder()
    void postorder(){ postorder(root); }
    // ----- insert()
    void insert(const T&);
    // ----- recursive_insert()
    void recrusive_insert(const T& element){
        recursive_insert(root, element);
    }
    // ----- search()
    T* search(const T& element){ return search(root, element); }
    // ----- recursive_search()
    T* recursive_search(const T& element){
        return recursive_search(root, element);
    }
    // ----- other methods ------
    void delete_by_copying(BSTNode<T>*&);
    void find_and_delete_copying(const T&);
    void delete_by_merging(BSTNode<T>*&);
    void find_and_delete_by_merging(const T&);
    void iterative_preorder();
    void iterative_inorder();
    void iterative_postorder();
    void breadth_first();
    void morris_preorder();
    void morris_inorder();
    void morris_postorder();
    void balance(T*, int, int);

protected:
    BSTNode<T> *root;
    void clear(BSTNode<T>*);
    void recursive_insert(BSTNode<T>*&, const T&);
    T* search(BSTNode<T>*, const T&) const;
    T* recursive_search(BSTNode<T>*, const T&) const;
    void preorder(BSTNode<T>*);
    void inorder(BSTNode<T>*);
    void postorder(BSTNode<T>*);
    virtual void visit(BSTNode<T>* node){
        std::cout << node->item << " ";
    }
};

// ----------------------------------------------------------------------
// ----- BST<T>::clear()                                            -----
// ----------------------------------------------------------------------
template<typename T>
void BST<T>::clear(BSTNode<T> *node){
    if(node != nullptr){
        clear(node->left);
        clear(node->right);
        delete node;
    }
}
