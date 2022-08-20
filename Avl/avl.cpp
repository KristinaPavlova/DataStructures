#ifndef AVL_CPP
#define AVL_CPP
#include"avl.h"

Avl::Avl(const int& data )
{
    try
    {
        this->root = new node(data);
    }
    catch(const std::exception& e)
    {
        this->root = nullptr;
        throw std::bad_alloc();
    }
    
}

Avl::Avl(const Avl& other )
{
    node* otherRoot = const_cast<node*>(other.root);
    this->root = this->copy(this->root , otherRoot);
}

Avl& Avl::operator=(const Avl& other )
{
    if(this != &other)
    {
        Avl cpy(other);
        std::swap(this->root , cpy.root);
    }
}

Avl::~Avl()
{
    this->destroy(this->root);
}

void Avl::insert(const int& value)
{
    this->root = insertRecursive(this->root , value);
}

void Avl::remove(const int& value)
{
    this->root = this->removeRecursive(this->root , value);
}

node* Avl::removeRecursive(node*& curr, const int& value)
{
    if(curr == nullptr)
    {
        throw std::invalid_argument("no such value");
    }
    else if(curr->data > value)
    {
        curr->left = this->removeRecursive(curr->left , value);
    }
    else if(curr->data < value)
    {
        curr->right = this->removeRecursive(curr->right , value);
    }
    else
    {
        //no children
        if(curr->left == nullptr && curr->right == nullptr)
        {
            delete curr;
            return nullptr;
        }
        //only right child
        else if(curr->left == nullptr)
        {
            std::swap(curr->data , curr->right->data);
            delete curr->right;
            curr->right == nullptr;
            return curr;
        }
        //only left child
        else if(curr->right == nullptr)
        {
            std::swap(curr->data , curr->left->data);
            delete curr->left;
            curr->left == nullptr;
            return curr;
        }
        //2 children
        else
        {
            node* minElem = this->minElem(curr->right);
            std::swap(curr->data ,minElem->data);
            curr->right = this->removeRecursive(curr->right , minElem->data);
        }
    }

    curr->heigh = 1 + std::max(this->heigh(curr->left) , this->heigh(curr->right));

    int balance = this->balance_factor(curr);

    if(balance < -1 && this->balance_factor(curr->right) < 1)
    {
        curr = this->leftRotation(curr);
    }
    else if(balance < -1 && this->balance_factor(curr->right) >= 1)
    {
        curr->right = this->rightRotation(curr->right);
        curr = this->leftRotation(curr);
    }
    else if(balance > 1 && this->balance_factor(curr->left) >= 1)
    {
        curr = this->rightRotation(curr);
    }
    else if(balance > 1 && this->balance_factor(curr->left) < 1)
    {
        curr->left = this->leftRotation(curr->left);
        curr = this->rightRotation(curr);
    }
    return curr;

}

node* Avl::minElem(node*& curr)
{
    if(curr == nullptr)
    {
        throw std::invalid_argument("nullptr");
    }
    node* minEl = this->root;

    while(minEl->left != nullptr)
    {
        minEl = minEl->left;
    }
    return minEl;
}

node* Avl::insertRecursive(node*& curr, const int& value)
{
    if(curr == nullptr)
    {
        return new node(value , 0);
    }
    else if(curr->data > value)
    {
        curr->left = this->insertRecursive(curr->left , value);
    }
    else if(curr->data < value)
    {
        curr->right = this->insertRecursive(curr->right , value);
    }
    else
    {
        return curr;
    }

    curr->heigh = 1 + std::max(this->heigh(curr->left) , this->heigh(curr->right));

    int balance = this->balance_factor(curr);

    //left rotation
    if(balance < -1 && value > curr->right->data)
    {
        curr = this->leftRotation(curr);
    }
    //right left rotation
    else if(balance < -1 && value < curr->right->data)
    {
        curr->right = this->rightRotation(curr->right);
        curr = this->leftRotation(curr);
    }
    //right rotation
    else if(balance > 1 && value < curr->left->data)
    {
        curr = this->rightRotation(curr);
    }
    //left right rotation
    else if(balance > 1 && value > curr->left->data)
    {
        curr->left = this->leftRotation(curr->left);
        curr = this->rightRotation(curr);
    }
    return curr;

}

void Avl::inorder()
{
    this->inorderRecursive(this->root);
}

void Avl::inorderRecursive(node*& curr)
{
    if(curr == nullptr)
    {
        return;
    }
    this->inorderRecursive(curr->left);

    std::cout<<curr->data<<" ";

    this->inorderRecursive(curr->right);
}

void Avl::levelOrder()
{
    if(this->root == nullptr)
    {
        return;
    }
    node* curr = nullptr;

    std::queue<node*> nodes;

    nodes.push(this->root);

    while(!nodes.empty())
    {
        curr = nodes.front();

        nodes.pop();

        std::cout<<curr->data<<" ";

        if(curr->left != nullptr)
        {
            nodes.push(curr->left);
        }

        if(curr->right != nullptr)
        {
            nodes.push(curr->right);
        }
    }
    std::cout<<std::endl;
}

int Avl::heigh(node*& curr)
{
    if(curr == nullptr)
    {
        return 0;
    }
    return 1 + std::max(this->heigh(curr->left) , this->heigh(curr->right));
}

int Avl::balance_factor(node*& curr)
{
    return this->heigh(curr->left) - this->heigh(curr->right);
}

node* Avl::rightRotation(node*& y)
{
    if(y == nullptr)
    {
        throw std::invalid_argument(nullptr);
    }

    node* ptr = y->left;

    y->left = ptr->right;

    ptr->right = y;

    y->heigh = 1 + std::max(this->heigh(y->left) , this->heigh(y->right));

    ptr->heigh = 1 + std::max(this->heigh(ptr->left) , this->heigh(ptr->right));


    return ptr;
}

node* Avl::leftRotation(node*& y)
{
    if(y == nullptr)
    {
        throw std::invalid_argument("nullpytr");
    }
    node* ptr = y->right;

    y->right = ptr->left;

    ptr->left = y;

    y->heigh = 1 + std::max(this->heigh(y->left) , this->heigh(y->right));

    ptr->heigh = 1 + std::max(this->heigh(ptr->left) , this->heigh(ptr->right));

    return ptr;
}

node* Avl::copy(node*& curr, node*& other)
{
    if(other == nullptr)
    {
        return nullptr;
    }
    curr = new node(other->data , other->heigh , nullptr , nullptr);
    curr->left = this->copy(curr->left , other->left);
    curr->right = this->copy(curr->right , other->right);
    return curr;

}

void Avl::destroy(node*& curr)
{
    if(curr == nullptr)
    {
        return;
    }
    this->destroy(curr->left);
    this->destroy(curr->right);
    delete curr;
    curr = nullptr;
}

#endif