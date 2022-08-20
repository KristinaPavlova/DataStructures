#ifndef MAXHEAP_CPP
#define MAXHEAP_CPP
#include"maxHeap.h"

void MaxHeap::insert(const int& value)
{
    if(this->heap.empty())
    {
        this->heap.push_back(value);
        return;
    }
    this->heap.push_back(value);
    int currIndex = this->heap.size() - 1;
    int parentId = this->parentId(currIndex);
    while(parentId >= 0 && heap[parentId] < heap[currIndex])
    {
        std::swap( heap[parentId] , heap[currIndex]);
        currIndex = parentId;
        parentId = this->parentId(currIndex);
    }
}

int MaxHeap::getMax()const
{
    if(heap.empty())
    {
        throw std::invalid_argument("empty heap");
    }
    return heap[0];
}

void MaxHeap::remove()
{
    if(this->heap.empty())
    {
        throw std::invalid_argument("empty heap");
    }
    else if(this->heap.size() == 1)
    {
        this->heap.pop_back();
    }
    else
    {
        int lastId = this->heap.size() - 1;
        std::swap(this->heap[0] , this->heap[lastId]);
        this->heap.pop_back();
        if (this->heap.size() == 1)
        {
            return;
        }
        this->heapify(0);
    }
}

bool MaxHeap::empty()const
{
    return this->heap.empty();
}

int MaxHeap::size()const
{
   return this->heap.size();
}

void MaxHeap::print()const
{
    for(auto it = this->heap.begin() ; it != this->heap.end() ; ++it)
    {
        std::cout<<*it<<" ";
    }
    std::cout<<"\n";
}

void MaxHeap::heapify(int index)
{
    int leftIndex = this->leftChildID(index);
    int rightIndex = this->rightChildID(index);
    int n = this->heap.size();
    int indexToSwap = index;
    while(leftIndex < n || rightIndex < n )
    {
        if(leftIndex < n && this->heap[leftIndex] >= this->heap[index])
        {
            indexToSwap = leftIndex;
        }
        if(rightIndex < n && this->heap[rightIndex] >= this->heap[indexToSwap])
        {
            indexToSwap = rightIndex;
        }
        std::swap(this->heap[index], this->heap[indexToSwap]);
        index = indexToSwap;
        leftIndex = this->leftChildID(index);
        rightIndex = this->rightChildID(index);
    }
}
#endif