#include<iostream>
#include"DynamicArray.h"

int main()
{
    DynamicArray<int> arr(5);
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.push_back(4);
    arr.push_back(5);
    arr.push_back(6);
    arr.push_back(7);
    arr.push_back(9);

    std::cout<<arr.getSize()<<std::endl;
    std::cout<<arr.getCapacity()<<std::endl;

    for(typename DynamicArray<int>::Iterator it = arr.begin()  ; it != arr.end() ; ++it)
    {
        std::cout<<*it<<" ";
    }

    arr.pop_back();
    std::cout<<std::endl;
    std::cout<<arr.getSize()<<std::endl;
    std::cout<<arr.getCapacity()<<std::endl;

    for(typename DynamicArray<int>::Iterator it = arr.begin()  ; it != arr.end() ; ++it)
    {
        std::cout<<*it<<" ";
    }
    std::cout<<std::endl;
    DynamicArray<int> arr2(arr);
     for(int i = 0 ; i < arr2.getSize() ; ++i)
    {
        std::cout<<arr2[i]<<" ";
    }

    return 0;
}