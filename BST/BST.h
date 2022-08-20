#ifndef BST_H
#define BST_H
#include<exception>
#include<iostream>
#include<string>
#include<fstream>
#include<queue>

template<typename T>
struct node
{
    T data;
    node* left{};
    node* right{};

    node(const T& data_ , node* left_ , node* right_):data(data_) , left(left_) , right(right_){}
};

template<typename T>
class BST
{
    public:

    BST();

    BST(const BST<T>&);

    BST<T>& operator=(const BST<T>&);

    ~BST();

    void add(const T&); // no dublicates

    void remove(const T&);

    void inorder();

    void preorder();

    void postorder();

    int heigh();

    void loadFromFile(const std::string&);

    void writeInFile(const std::string&);

    private:

    node<T>* root{};

    node<T>* copy(node<T>*& , node<T>*&);

    void destroy(node<T>*&);

    node<T>* minNode(node<T>*&);

    node<T>* insertRecursive(node<T>*& , const T&);

    node<T>* removeRecursive(node<T>*& , const T&);

    void inorderRecursive(node<T>*);

    void preorderRecursive(node<T>*);

    void postorderRecursive(node<T>*);

    int heighRecursive(node<T>*);


};

#include"BST.cpp"
#endif
