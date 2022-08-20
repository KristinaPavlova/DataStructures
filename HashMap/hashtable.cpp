#ifndef HASHTABLE_CPP
#define HASHTABLE_CPP
#include"hashtable.h"

HashTable::HashTable()
{
    this->arr = new HashTable::LList*[10];
    for(int i = 0 ; i < 10 ; ++i)
    {
        arr[i] = nullptr;
    }
    this->size = 10;
}

HashTable::HashTable(const int& size)
{
    this->arr = new HashTable::LList*[size];
    for(int i = 0 ; i < size ; ++i)
    {
        arr[i] = nullptr;
    }
    this->size = size;
}

HashTable::HashTable(const std::string& fileName)
{
    std::ifstream in(fileName);
    if(in.good())
    {   
        std::string value;
        int key;
        char sign;
        this->size = 10;
        this->arr = new HashTable::LList* [10];
        while(!in.eof())
        {
            in>>key;
            in>>sign;
            in>>value;
            pair p{key , value};
            this->addPair(p);
            
        }
        in.close();

    }
    else
    {
        throw std::invalid_argument("wrong file name");
    }
}

HashTable::HashTable(const HashTable& other)
{
    if(other.arr != nullptr)
    {
        this->arr = new HashTable::LList *[other.size];
        this->size = other.size;
        for (int i = 0; i < this->size; ++i)
        {
            if(other.arr[i] == nullptr )
            {
                arr[i ] = nullptr;
            }
            else
            {
                arr[i] = new HashTable::LList(*(other.arr[i]));
            }
        }
    }
}

HashTable& HashTable::operator=(const HashTable& other)
{
    if(this != &other)
    {
        HashTable cpy(other);
        std::swap(this->arr , cpy.arr);
        std::swap(this->size , cpy.size);
    }
}

HashTable::~HashTable()
{
    if(this->arr != nullptr)
    {
        for(int i = 0 ; i < size ; ++i)
        {
            delete this->arr[i];
        }
        delete[] arr;
    }
}

void HashTable::addPair(const pair& pairToAdd)
{
    int index = this->hashFunction(pairToAdd.key);
    if(index > this->size || index < 0)
    {
        throw std::invalid_argument("wrong hashFunction");
    }
    if(this->arr[index] == nullptr)
    {
        this->arr[index] = new HashTable::LList();
        this->arr[index]->push_front(pairToAdd);
    }
    else
    {
       this->arr[index]->push_front(pairToAdd); 
    }
    
}

void HashTable::removePair(const pair& pairToDel)
{
    int index = this->hashFunction(pairToDel.key);
    if(index > this->size || index < 0)
    {
        throw std::invalid_argument("wrong hashFunction");
    }
    if(this->arr[index] == nullptr)
    {
        throw std::invalid_argument("pair doesnt exists");
    }
    else
    {
       this->arr[index]->remove(pairToDel); 
    }
    
}

void HashTable::printTable()const
{
    if(this->arr == nullptr)
    {
        return;
    }
    for(int i = 0 ; i < this->size ; ++i)
    {
        if(arr[i] != nullptr)
        {
            arr[i]->print();
        }
    }    
}

void HashTable::writeInFile(const std::string &fileName)
{
    if (this->arr == nullptr) // create empty file
    {
        std::ofstream out(fileName);
        out.close();
        return;
    }
    else
    {
       for (int i = 0 ; i < this->size ; ++i)
       {
           if(arr[i] != nullptr)
           {
               arr[i]->writeListInFile(fileName);
           }
       } 
    }
    
}

HashTable::LList::LList()
{
    this->head = nullptr;
}

HashTable::LList::LList(const HashTable::LList& other)
{
    if(other.head != nullptr)
    {
        node* currOther = other.head;
        node* curr = new node(currOther->data);
        this->head = curr;
        currOther = currOther->next;
        
        while(currOther)
        {
            curr->next = new node(currOther->data);
            curr = curr->next;
            currOther = currOther->next;
        }

    }
}

HashTable::LList::~LList()
{
    if(this->head != nullptr)
    {
        node *curr = this->head;
        node *toDel = nullptr;
        while (curr != nullptr)
        {
            toDel = curr;
            curr = curr->next;
            delete toDel;
            toDel = nullptr;
        }
    }
}

void HashTable::LList::push_front(const pair& valueToAdd)
{
    node* toAdd = new node(valueToAdd);
    toAdd->next = this->head;
    this->head = toAdd;
}

void HashTable::LList::pop_front()
{
    if(this->head != nullptr)
    {
        node *toDel = this->head;
        this->head = this->head->next;
        delete toDel;
    }
}

void HashTable::LList::print()const
{
    if(this->head == nullptr)
    {
        return;
    }
    node* curr = this->head;
    while(curr != nullptr)
    {
        std::cout<<curr->data.key<<"-"<<curr->data.value<<"  ";
        curr = curr->next;
    }
    std::cout<<"\n";
}

void HashTable::LList::writeListInFile(const std::string& fileName)
{
    std::ofstream out(fileName);
    if(out.good())
    {
        node* curr = this->head;
        while(curr != nullptr)
        {
            out<<curr->data.key<<" - "<<curr->data.value<<"\n";
            curr = curr->next;
        }
        out.close();
    }
    else
    {
        throw std::invalid_argument("wrong file name");
    }
}

void HashTable::LList::remove(const pair& searchedPair)
{
    if(this->head == nullptr)
    {
        throw std::invalid_argument("empty list");
    }
    if(this->head->data == searchedPair)
    {
        this->pop_front();
        return;
    }
    node* curr = this->head;
    node* toDel = nullptr;
    node* prev = nullptr;
    while(curr != nullptr)
    {
        prev = curr;
        curr = curr->next;
        if(curr != nullptr && curr->data == searchedPair)
        {
            toDel = curr;
            curr = curr->next;
            prev->next = curr;
            delete toDel;
        }
    }
}


int HashTable::hashFunction(const int& keyValue)
{
    return std::abs(keyValue % this->size);
}

#endif