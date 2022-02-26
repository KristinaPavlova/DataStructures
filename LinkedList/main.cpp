#include<iostream>
#include"LinkedList.hpp"


int main()
{
    LinkedList<int> ls;
    ls.push_front(5);
    ls.push_front(4);
    ls.push_front(3);
    ls.push_front(2);
    ls.push_front(1);
    ls.print();

    for(LinkedList<int>::Iterator it = ls.begin() ; it != ls.end() ; ++it)
    {
        std::cout<<*it<<" ";

    }
    std::cout<<std::endl;
    ls.deleteElemOnPosition(1);
    ls.print();
    ls.insertElemOnPosition(9 , 3);
    ls.print();
    std::cout<<ls.getElemOnPosition(2)<<std::endl;

    LinkedList<int> ls2(ls);
    ls.print();

    return 0;
}