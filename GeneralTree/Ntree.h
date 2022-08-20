#ifndef NTREE_H
#define NTREE_H
#include<vector>
#include<queue>
#include<stack>
#include<list>
#include<unordered_map>
#include<iostream>
#include<exception>
struct node
{
    int data{};
    std::vector<node*> children;

    node(const int& data_):data(data_){}
};

class Ntree
{
    public: 

    Ntree() = delete;

    Ntree(const int&);

    Ntree(const Ntree&);

    Ntree& operator=(const Ntree&);

    ~Ntree();

    void insert(const int& , const int&);

    void levelOrder();

    void reverseLevelOrder();

    void elemsOnKthLevel(const int&);

    void pathFromLeavesToRoot();

    bool containsSubtree(const Ntree&);



    private:

    node* find(std::vector<node*>& children , const int& data);

    bool contains(node*& , node*&);

    void printPathToRoot(node* , std::unordered_map<node* , node*>&);

    void elemsOnKthLevelRecursive(std::vector<int>& , node*& , const int&);

    bool exists(node*& , const int&);

    node* copy(node*& , node*&);

    void destroy(node*&);

    node* root{};
};

#endif