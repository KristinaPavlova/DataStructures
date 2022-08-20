#ifndef BST_CPP
#define BST_CPP
#include"BST.h"

template<typename T>
BST<T>::BST()
{
    this->root = nullptr;
}

template<typename T>
BST<T>::BST(const BST& other)
{
    if(other.root != nullptr)
    {
        node<T>* otherRoor = const_cast<node<T>*>(other.root);
        this->root = copy(this->root , otherRoor);
    }
}

template<typename T>
BST<T>& BST<T>::operator=(const BST<T>& other)
{
    if(this != &other)
    {
        BST<T> cpy(other);
        std::swap(this->root , cpy.root);
    }
}

template<typename T>
BST<T>::~BST()
{
    this->destroy(this->root);
}

template<typename T>
void BST<T>::add(const T& value)
{
    this->root = insertRecursive(this->root , value);
}

template<typename T>
void BST<T>::remove(const T& value)
{
    this->root = removeRecursive(this->root , value);
}

template<typename T>
void BST<T>::inorder()
{
    this->inorderRecursive(this->root);
}

template<typename T>
void BST<T>::preorder()
{
    this->preorderRecursive(this->root);
}

template<typename T>
void BST<T>::postorder()
{
    this->postorderRecursive(this->root);
}

template<typename T>
int BST<T>::heigh()
{
    return this->heighRecursive(this->root);
}

template<typename T>
void BST<T>::loadFromFile(const std::string& fileName)
{
    std::ifstream in(fileName);
    if(in.good())
    {
        int num;
        while(in>>num)
        {
            this->add(num);
        }
        in.close();
    }
    else
    {
        throw std::invalid_argument("wrong path");
    }

    
}

template<typename T>
void BST<T>::writeInFile(const std::string& fileName)
{
    //write in file level order traversal
    std::ofstream out(fileName);
    if(out.good())
    {
        std::queue<node<T>*> nums;
        nums.push(this->root);
        node<T>* curr = nullptr;
        while(!nums.empty())
        {
            curr = nums.front();
            nums.pop();
            out<<curr->data<<" ";
            if(curr->left)
            {
                nums.push(curr->left);
            }
            
            if(curr->right)
            {
               nums.push(curr->right); 
            }
            
        }
        out.close();
    }
    else
    {
        throw std::invalid_argument("wrong path");
    }

    
}

template<typename T>
node<T>* BST<T>::copy(node<T>*& curr, node<T>*& other)
{
    if(other == nullptr)
    {
        return nullptr;
    }
    curr = new node<T>(other->data, nullptr, nullptr);
    curr->left = copy(curr->left, other->left);
    curr->right = copy(curr->right, other->right);
    return curr;
}

template<typename T>
void BST<T>::destroy(node<T>*& curr)
{
    if(curr == nullptr)
    {
        return;
    }
    this->destroy(curr->left);

    this->destroy(curr->right);

    delete curr;
}

template<typename T>
node<T>* BST<T>::minNode(node<T>*& curr)
{
    if(curr == nullptr)
    {
        throw std::invalid_argument("empty tree");
    }
    node<T>* ptr = curr;
    while(ptr->left)
    {
        ptr = ptr->left;
    }
    return ptr;
}

template<typename T>
node<T> *BST<T>::insertRecursive(node<T>*& curr, const T &value)
{
    if(curr == nullptr)
    {
        return new node<T>(value , nullptr , nullptr);
    }
    else if(curr->data == value)
    {
        return curr;
    }
    else if(curr->data > value)
    {
        curr->left = this->insertRecursive(curr->left , value);
    }
    else if(curr->data < value)
    {
        curr->right = this->insertRecursive(curr->right , value);
    }
    return curr;
}

template<typename T>
node<T>* BST<T>::removeRecursive(node<T>*& curr, const T& value)
{
    if(curr == nullptr)
    {
        return nullptr;
    }
    else if(curr->data > value)
    {
        curr->left = this->removeRecursive(curr->left , value);
    }
    else if(curr->data < value)
    {
        curr->right = this->removeRecursive(curr->right , value);
    }
    else if(curr->data == value)
    {
        // no children
        if(curr->left == nullptr && curr->right == nullptr)
        {
            delete curr;
            return nullptr;
        }
        else if(curr->right == nullptr) //only left child
        {
            curr->data = curr->left->data;
            delete curr->left;
            curr->left = nullptr;
            return curr;
        }
        else if(curr->left == nullptr) //only right child
        {
            curr->data = curr->right->data;
            delete curr->right;
            curr->right = nullptr;
            return curr;
        }
        //two children
        else
        {
            node<T>* minElem = this->minNode(curr->right);
            std::swap(curr->data , minElem->data);
            curr->right = removeRecursive(curr->right , minElem->data);
        }

    }
    return curr;
}

template<typename T>
void BST<T>::inorderRecursive(node<T>* curr)
{
    if(curr == nullptr)
    {
        return;
    }

    this->inorderRecursive(curr->left);

    std::cout<<curr->data<<" ";

    this->inorderRecursive(curr->right);
}

template<typename T>
void BST<T>::preorderRecursive(node<T>* curr)
{
    if(curr == nullptr)
    {
        return;
    }

    std::cout<<curr->data<<" ";

    this->preorderRecursive(curr->left);

    this->preorderRecursive(curr->right);
}

template<typename T>
void BST<T>::postorderRecursive(node<T>* curr)
{
    if(curr == nullptr)
    {
        return;
    }

    this->postorderRecursive(curr->left);

    this->postorderRecursive(curr->right);

    std::cout<<curr->data<<" ";
}

template<typename T>
int BST<T>::heighRecursive(node<T>* curr)
{
    if(curr == nullptr)
    {
        return 0;
    }

    return 1 + std::max( (heighRecursive(curr->left)) , (heighRecursive(curr->right)) );
}

#endif
