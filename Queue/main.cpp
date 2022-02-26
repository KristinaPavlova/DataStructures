#include<iostream>
#include"Queue.h"


int main()
{
    Queue<int> queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);
    queue.push(4);
    queue.push(5);

    std::cout<<queue.size()<<std::endl;
    int size = queue.size();

    for(int i = 0 ; i < size ; ++i)
    {
        std::cout<<queue.top()<<" ";
        queue.pop();
    }
    std::cout<<std::endl;

    return 0;
}