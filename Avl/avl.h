#ifndef AVL_H
#define AVL_H
#include<iostream>
#include<exception>
#include<queue>

struct node
{
    int data{};
    int heigh{};
    node* left{};
    node* right{};
    node(const int& data_ , const int& heigh_ = 0 , node* left_ =nullptr , node* right_=nullptr):data(data_) , heigh(heigh_) , left(left_) , right(right_){}
};

class Avl
{
    public:

    Avl() = default;

    Avl(const int& );

    Avl(const Avl&);
    
    Avl& operator=(const Avl&);

    ~Avl();

    void insert(const int&);

    void remove(const int&);

    void inorder();

    void levelOrder();

    private:

    void inorderRecursive(node*&);

    node* minElem(node*&);

    node* removeRecursive(node*& , const int&);

    node* insertRecursive(node*& , const int&);

    int heigh(node*&);

    int balance_factor(node*&);

    node* rightRotation(node*&);

    node* leftRotation(node*&);

    node* copy(node*& , node*&);

    void destroy(node*&);

    node* root{};
};


#endif