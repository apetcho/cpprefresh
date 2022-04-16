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
// ----- BST<T>::inorder(*node)                                     -----
// ----------------------------------------------------------------------
template<typename T>
void BST<T>::inorder(BSTNode<T> *node){
    if(node != nullptr){
        inorder(node->left);
        visit(node);
        inorder(node->right);
    }
}

// ----------------------------------------------------------------------
// ----- BST<T>::preorder(*node)                                    -----
// ----------------------------------------------------------------------
template<typename T>
void BST<T>::preorder(BSTNode<T> *node){
    if(node != nullptr){
        visit(node);
        preorder(node->left);
        preorder(node->right);
    }
}

// ----------------------------------------------------------------------
// ----- BST<T>::postorder(*node)                                   -----
// ----------------------------------------------------------------------
template<typename T>
void BST<T>::postorder(BSTNode<T> *node){
    if(node != nullptr){
        postorder(node->left);
        postorder(node->right);
        visit(node);
    }
}

// ----------------------------------------------------------------------
// ----- BST<T>::delete_by_copying(item)                            -----
// ----------------------------------------------------------------------
template<typename T>
void BST<T>::delete_by_copying(BSTNode<T>*& node){
    BSTNode<T> *prev;
    BSTNode<T> *tmp = node;
    if(node->right == nullptr){         // node right child
        node = node->left;
    }else if(node->left == nullptr){    // node left child
        node = node->right;
    }else{                              // has both children
        tmp = node->left;
        prev = node;
        while(tmp->right != nullptr){
            prev = tmp;
            tmp = tmp->right;
        }
        node->item = tmp->item;
        if(prev == node){
            prev->left = tmp->left;
        }else{ prev->right = tmp->left; }
    }

    delete tmp;
}

// ----------------------------------------------------------------------
// ----- BST<T>::find_and_delete_by_copying(item)                   -----
// ----------------------------------------------------------------------
template<typename T>
void BST<T>::find_and_delete_copying(const T& element){
    BSTNode<T> *node = root;
    BSTNode<T> *prev = nullptr;

    while(node != nullptr && !(node->item == element)){
        prev = node;
        if(element < node->item){
            node = node->left;
        }else{
            node = node->right;
        }
    }
    if(node != nullptr && node->item == element){
        if(node == root){
            delete_by_copying(root);
        }else if(prev->left == node){
            delete_by_copying(prev->left);
        }else{
            delete_by_copying(prev->right);
        }
    }else if( root != nullptr){
        std::cout << "Element " << element << " not in the tree" << std::endl;
    }else{
        std::cout << "The tree is empty" << std::endl;
    }
}

// ----------------------------------------------------------------------
// ----- BST<T>::delete_by_merging(*node)                           -----
// ----------------------------------------------------------------------
template<typename T>
void BST<T>::delete_by_merging(BSTNode<T> *&node){
    BSTNode<T> *tmp = node;
    if(node != nullptr){
        if(!node->right){ node = node->left;}
        else if(!node->left){node = node->right; }
        else{
            tmp = node->left;
            while(tmp->right != nullptr){ tmp = tmp->right; }
            tmp->right = node->right;
            tmp = node;
            node = node->left;
        }

        delete tmp;
    }
}

// ----------------------------------------------------------------------
// ----- BST<T>::find_and_delete_by_merging(*node)                  -----
// ----------------------------------------------------------------------
template<typename T>
void BST<T>::find_and_delete_by_merging(const T& element){
    BSTNode<T> *node = root;
    BSTNode<T> *prev = nullptr;
    while(node != nullptr){
        if(node->item == element){break;}
        prev = node;
        if(element < node->item){ node = node->left; }
        else{ node = node->right; }
    }
    if(node != nullptr && node->item == element){
        if(node == root){ delete_by_merging(root); }
        else if(prev->left == node){ delete_by_merging(prev->left); }
        else{ delete_by_merging(prev->right); }
    }else if(root != nullptr){
        std::cout << "Element " << element << " is not in the tree"
            << std::endl;
    }else{
        std::cout << "The tree is empty" << std::endl;
    }
}

// ----------------------------------------------------------------------
// ----- BST<T>::iterative_preorder()                               -----
// ----------------------------------------------------------------------
template<typename T>
void BST<T>::iterative_preorder(){
    Stack<BSTNode<T>*> travStack;
    BSTNode<T> *node = root;
    if(node != nullptr){
        travStack.push(node);
        while(!travStack.empty()){
            node = travStack.pop();
            visit(node);
            if(node->right != nullptr){ travStack.push(node->right); }
            if(node->left != nullptr){ travStack.push(node->left); }
        }
    }
}

// ----------------------------------------------------------------------
// ----- BST<T>::iterative_inorder()                                -----
// ----------------------------------------------------------------------
template<typename T>
void BST<T>::iterative_inorder(){
    Stack<BSTNode<T>*> travStack;
    BSTNode<T> *node = root;

    while(node != nullptr){
        while(node != nullptr){
            if(node->right){ travStack.push(node->right); }
            travStack.push(node);
            node = node->left;
        }
        node = travStack.pop();
        while(!travStack.empty() && node->right ==nullptr){
            visit(node);
            node = travStack.pop();
        }
        visit(node);
        if(!travStack.empty()){ node = travStack.pop(); }
        else{ node = nullptr; }
    }
}

// ----------------------------------------------------------------------
// ----- BST<T>::iterative_postorder()                              -----
// ----------------------------------------------------------------------
template<typename T>
void BST<T>::iterative_postorder(){
    Stack<BSTNode<T>*> travStack;
    BSTNode<T> *node = root;
    BSTNode<T> *q = root;

    while(node != nullptr){
        for(; node->left != nullptr; node = node->left){
            travStack.push(node);
        }
        while(node->right == nullptr || node->right == q){
            visit(node);
            q = node;
            if(travStack.empty()){ return; }
            node = travStack.pop();
        }
        travStack.push(node);
        node = node->right;
    }
}

// ----------------------------------------------------------------------
// ----- BST<T>::breadth_first()                                    -----
// ----------------------------------------------------------------------
template<typename T>
void BST<T>::breadth_first(){
    Queue<BSTNode<T>*> myqueue;
    BSTNode<T> *node = root;
    if(node != nullptr){
        myqueue.enqueue(node);
        while(!myqueue.empty()){
            node = myqueue.dequeue();
            visit(node);
            if(node->left != nullptr){ myqueue.enqueue(node->left); }
            if(node->right != nullptr){ myqueue.enqueue(node->right); }
        }
    }
}

// ----------------------------------------------------------------------
// ----- BST<T>::morris_inorder()                                   -----
// ----------------------------------------------------------------------
template<typename T>
void BST<T>::morris_inorder(){
    BSTNode<T> *node = root;
    BSTNode<T> *tmp;

    while(node != nullptr){
        if(node->left == nullptr){
            visit(node);
            node = node->right;
        }else{
            tmp = node->left;
            while(tmp->right != nullptr && tmp->right != node){
                tmp = tmp->right;
            }
            if(tmp->right == nullptr){
                tmp->right = node;
                node = node->left;
            }else{
                visit(node);
                tmp->right = nullptr;
                node = node->right;
            }
        }
    }
}
