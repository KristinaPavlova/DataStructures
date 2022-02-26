#pragma once
#include<iostream>


template<typename Type>
class DynamicArray
{
    private:
    Type* data{};
    size_t size{};
    size_t capacity{0};

    void resize(size_t);


    public:

    DynamicArray();

    explicit DynamicArray(const int& capacity);

    DynamicArray(const DynamicArray<Type>& );

    DynamicArray<Type>& operator=(const DynamicArray<Type>& );

    ~DynamicArray();

    void push_back(const Type&); // invalidate iterator 

    void pop_back();

    const Type& operator[](const size_t& )const;

    Type& operator[](const size_t& );

    const size_t& getCapacity()const;

    const size_t& getSize()const;


    class Iterator
    {
        private:
        Type* ptr{};

        
        Iterator(Type* data_):ptr(data_){}
        friend DynamicArray;

        public:

        Type* operator->()
        {
            return ptr;
        }

        bool operator!=(const Iterator& other)const
        {
            return !(ptr == other.ptr);

        }
        Type& operator*()
        {
            return *ptr;
        }
        Iterator& operator++()
        {
            ptr++;
            return *this;
        }


    };

    Iterator begin()
    {
        return  Iterator(this->data);
    }
    Iterator end()
    {
        return  Iterator(this->data + this->size);
    }

    static Type* allocateMemory(const size_t& capacity_)
    {
        return static_cast<Type*>(operator new((sizeof(Type))*capacity_));
    }

    
    static void constructRange(Type* begin , Type* end)
    {
        while(begin != end)
        {
            new(begin)Type(); 
            ++begin;
        }
    }

    static void copyRange(Type* begin , Type* end , Type* location)
    {
        
        while(begin != end)
        {
            new(location)Type(*begin);
            ++location;
            ++begin;
        }
    }
    
    static void destructRange(Type* begin , Type* end)
    {
        while(begin != end)
        {
            begin->~Type(); 
            ++begin;
        }
    }

    static void destructAndDeleteRange(Type* begin , Type* end)
    {
        destructRange(begin , end);
        operator delete(begin);

    }

};
#include"DynamicArray.inl"