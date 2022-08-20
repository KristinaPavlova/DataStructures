#ifndef NTREE_CPP
#define NTREE_CPP
#include"Ntree.h"


Ntree::Ntree(const Ntree& other)
{
    node* otherRoor = const_cast<node*>(other.root);
    this->root = this->copy(this->root , otherRoor);
}

Ntree::Ntree(const int& value)
{
    try
    {
        this->root = new node(value);
    }
    catch(const std::exception& e)
    {
        this->root = nullptr;
        throw std::bad_alloc();
    }
    
}

Ntree& Ntree::operator=(const Ntree& other)
{
    if(this != &other)
    {
        Ntree cpy(other);
        std::swap(this->root , cpy.root);
    }
}

Ntree::~Ntree()
{
    this->destroy(this->root);
    this->root = nullptr;
}

void Ntree::insert(const int& parent , const int& newValue)
{
    if(this->exists(this->root , newValue))
    {
        
        throw std::invalid_argument("this value already exists");
    }
    std::queue<node*> nodes;
    node* curr = nullptr;
    nodes.push(this->root);
    while(!nodes.empty())
    {
        curr = nodes.front();

        nodes.pop();

        if(curr->data == parent)
        {
            curr->children.push_back(new node(newValue));
            return;
        }

        for(auto it = curr->children.begin() ; it != curr->children.end() ; ++it)
        {
            nodes.push(*it);
        }
    }
    throw std::invalid_argument("incorrect parent");
}

void Ntree::levelOrder()
{
    if(this->root == nullptr)
    {
        return;
    }
    std::queue<node*> nodes;

    nodes.push(this->root);

    node* current = nullptr;
    while(!nodes.empty())
    {
        current = nodes.front();

        nodes.pop();

        std::cout<<current->data<<" ";
        for(auto it = current->children.begin() ; it != current->children.end() ; ++it)
        {
            nodes.push(*it);
        }
    }
    std::cout<<"\n";

}

void Ntree::reverseLevelOrder()
{
    if(this->root == nullptr)
    {
        return;
    }

    std::stack<node*> reverseNodes;

    std::queue<node*> nodes;

    nodes.push(this->root);

    node* current = nullptr;

    while (!nodes.empty())
    {
        current = nodes.front();

        nodes.pop();

        reverseNodes.push(current);

        for(auto it = current->children.rbegin() ; it != current->children.rend() ; ++it)
        {
            nodes.push(*it);
        }
    }

    while(!reverseNodes.empty())
    {
        current = reverseNodes.top();

        reverseNodes.pop();

        std::cout<<current->data <<" ";
    }
    std::cout<<"\n";
    
}

void Ntree::elemsOnKthLevel(const int& level)
{
    if(this->root == nullptr)
    {
        return;
    }
    std::vector<int> elements;
    this->elemsOnKthLevelRecursive(elements , this->root , level);
    for(auto it = elements.begin() ; it != elements.end() ; ++it)
    {
        std::cout<<*it<<" ";
    }
    std::cout<<"\n";
}

void Ntree::pathFromLeavesToRoot()
{
    if(this->root == nullptr)
    {
        throw std::invalid_argument("empty tree");
    }

    std::unordered_map<node* , node*> map;

    std::queue<node*> nodes;

    node* curr = nullptr;

    nodes.push(this->root);

    while(!nodes.empty())
    {
        curr = nodes.front();

        nodes.pop();

        if(curr->children.empty())
        {
            this->printPathToRoot(curr , map);
        }   

        for(auto it = curr->children.begin() ; it != curr->children.end() ; ++it)
        {
            nodes.push(*it);

            map[*it] = curr;
        }
    }
}

bool Ntree::containsSubtree(const Ntree& other)
{
    if(other.root == nullptr)
    {
        return true;
    }
    
    node* otherRoot = const_cast<node*>(other.root);

    std::queue<node*> nodes;

    std::stack<node*> reverseNodes;

    nodes.push(this->root);

    node* curr = nullptr;

    while(!nodes.empty())
    {
        curr = nodes.front();

        nodes.pop();

        reverseNodes.push(curr);

        for(auto it = curr->children.begin() ; it != curr->children.end() ; ++it)
        {
            nodes.push(*it);
        }
    }

    while (!reverseNodes.empty())
    {
        curr = reverseNodes.top();

        reverseNodes.pop();

        if(contains(curr , otherRoot))
        {
            return true;
        }
    }
    return false;
    
}

bool Ntree::contains(node*& curr, node*& other)
{
    if(curr == nullptr)
    {
        return false;
    }

    if(curr->data != other->data)
    {
        return false;
    }

    node* treeNode = nullptr;

    node* subtreeNode = nullptr;

    std::queue<node*> currNodes;

    currNodes.push(curr);

    std::queue<node*> otherNOdes;

    otherNOdes.push(other);

    while(!otherNOdes.empty())
    {
        treeNode = currNodes.front();

        currNodes.pop();

        subtreeNode = otherNOdes.front();

        otherNOdes.pop();

        for(auto it = subtreeNode->children.begin() ; it != subtreeNode->children.end() ; ++it)
        {
            node* found = this->find(treeNode->children , (*it)->data);

            if(found == nullptr)
            {
                return false;
            }

            otherNOdes.push(*it);

            currNodes.push(found);
        }

    }

    return true;

}

node* Ntree::find(std::vector<node*>& children , const int& data)
{
    for(auto it = children.begin() ; it != children.end() ; ++it)
    {
        if((*it)->data == data)
        {
            return (*it);
        }
    }

    return nullptr;
}

void Ntree::printPathToRoot(node* curr, std::unordered_map<node* , node*>& map)
{
    if(curr == nullptr)
    {
        throw std::invalid_argument("incorrect node");
    }
    std::cout<<curr->data;
    while (curr->data != this->root->data)
    {
        curr = map[curr];

        std::cout<<"-> "<<curr->data;
    }
    std::cout<<"\n";
    
}

void Ntree::elemsOnKthLevelRecursive(std::vector<int>& elems, node*& curr,  const int& goal)
{
    if(curr == nullptr)
    {
        return;
    }
    if(goal == 0)
    {
        elems.push_back(this->root->data);
        return;
    }
    int currLevel = 0;
    std::list<node*> nodes;
    nodes.push_back(this->root);
    node* currentNode = nullptr;
    int size;
    while(!nodes.empty())
    {
        size = nodes.size();

        while(size)
        {
            currentNode = nodes.front();

            nodes.pop_front();

            if(currLevel == goal)
            {
                elems.push_back(currentNode->data);
            }

            for(auto it = currentNode->children.begin() ; it != currentNode->children.end() ; ++it)
            {
                nodes.push_back(*it);
            }
            size--;
        }
        currLevel++;
    }
    
}

bool Ntree::exists(node*& curr, const int& value)
{
    if(this->root == nullptr)
    {
        return false;
    }
    std::queue<node*> nodes;
    nodes.push(curr);

    node* current = nullptr;
    while(!nodes.empty())
    {
        current = nodes.front();

        nodes.pop();

        if(current->data == value)
        {
            return true;
        }

        for(auto it = current->children.begin() ; it != current->children.end() ; ++it)
        {
            nodes.push(*it);
        }
    }

    return false;
}

node* Ntree::copy(node*& curr, node*& other)
{
    if(other == nullptr)
    {
        return nullptr;
    }
    curr = new node(other->data);

    for(auto it = other->children.begin() ; it != other->children.end() ; ++it)
    {
        node* newChild = copy(newChild , *it);
        if(newChild != nullptr)
        {
            curr->children.push_back(newChild);
        }
    }
    return curr;
}

void  Ntree::destroy(node*& curr)
{
    if(curr == nullptr)
    {
        return;
    }
    for(auto it = curr->children.begin() ; it != curr->children.end() ; ++it)
    {
        this->destroy(*it);
    }
    delete curr;
}


#endif