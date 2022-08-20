#ifndef MAXHEAP_H
#define MAXHEAP_H
#include<vector>
#include<exception>
#include<iostream>

class MaxHeap
{
    public:

    MaxHeap() = default;

    void insert(const int&);

    int getMax()const;

    void remove(); // remove biggest element (root)

    bool empty()const;

    int size()const;

    void print()const;


    private:

    void heapify(int);

    int parentId(const int&  id)
    {

        return (id -1)/2;
    }

    int leftChildID(const int&  id)
    {
        return (id*2 + 1);
    }

    int rightChildID(const int&  id)
    {
        return (id*2 + 2);
    }

    std::vector<int> heap{};
};

#endif