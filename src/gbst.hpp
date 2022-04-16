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
    void recursive_insert(const T& element){
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

// ----------------------------------------------------------------------
// ----- BST<T>::insert(item)                                       -----
// ----------------------------------------------------------------------
template<typename T>
void BST<T>::insert(const T& element){
    if(root == nullptr){
        root = new BSTNode<T>(element);
        return;
    }

    BSTNode<T> *node = root;
    BSTNode<T> *prev = nullptr;
    /* find appropiate place and insert a new node holding element */
    while(node != nullptr){
        prev = node;
        if(element < node->item){ node = node->left; }
        else{ node = node->right; }
    }
    if( element < prev->item){
        prev->left = new BSTNode<T>(element);
    }else{
        prev->right = new BSTNode<T>(element);
    }
}

// ----------------------------------------------------------------------
// ----- BST<T>::insert(item)                                       -----
// ----------------------------------------------------------------------
template<typename T>
void BST<T>::recursive_insert(BSTNode<T>*& node, const T& element){
    if(node == nullptr){
        node = new BSTNode<T>(element);
    }else if(element < node->item){
        recursive_insert(node->left, element);
    }else{ recursive_insert(node->right, element);}
}

// ----------------------------------------------------------------------
// ----- BST<T>::search(node, item)                                 -----
// ----------------------------------------------------------------------
template<typename T>
T* BST<T>::search(BSTNode<T> *node, const T& element) const {
    while(node != nullptr){
        if(element == node->item){ return &node->item; }
        else if(element < node->item){ node = node->left; }
        else { node = node->right; }
    }

    return nullptr;
}

// ----------------------------------------------------------------------
// ----- BST<T>::recursive_search(item)                             -----
// ----------------------------------------------------------------------
template<typename T>
T* BST<T>::recursive_search(BSTNode<T> *node, const T& element) const{
    if(node != nullptr){
        if(element == node->item){return &node->item;}
        else if(element < node->item){
            return recursive_search(node->left, element);
        }else{
            return recursive_search(node->right, element);
        }
    }else{
        return nullptr;
    }
}

// ----------------------------------------------------------------------
// ----- BST<T>::inorder(item)                                      -----
// ----------------------------------------------------------------------
template<typename T>
void BST<T>::inorder(BSTNode<T> *node){
    if(node != nullptr){
        inorder(node->left);
        visit(node);
        inorder(node->right);
    }
}
