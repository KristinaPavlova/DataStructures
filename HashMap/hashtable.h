#ifndef HASHTABLE_H
#define HASHTABLE_H
#include<string>
#include<exception>
#include<iostream>
#include<fstream>
#include<sstream>

struct pair
{
    int key;
    std::string value;

    bool operator==(const pair& other)
    {
        return this->key == other.key && this->value == other.value;
    }
};

struct node
{
    pair data;
    node* next;
    node(const pair& data_):data(data_){}
};


class HashTable
{
    public:

    HashTable();

    HashTable(const int&);

    //construct from file
    HashTable(const std::string&);

    HashTable(const HashTable& );

    HashTable& operator=(const HashTable& );

    ~HashTable();

    void addPair(const pair&);

    void removePair(const pair&);

    void printTable()const;

    void writeInFile(const std::string&);


    private:

    class LList
    {
        public:
        
        LList();

        LList(const HashTable::LList& );

        ~LList();

        bool empty()const;

        void push_front(const pair&);

        void pop_front();

        void print()const;

        void writeListInFile(const std::string& fileName);

        void remove(const pair&);

        private:
        node* head{};

    };

    //array of pointers to llist
    LList** arr{};

    int size{};

    int hashFunction(const int&);


};

#endif