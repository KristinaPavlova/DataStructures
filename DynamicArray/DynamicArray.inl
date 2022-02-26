#pragma once
#include<exception>
#include<assert.h>



template <typename Type>
void DynamicArray<Type>::resize(size_t newCapacity) 
{
    Type* newArray = allocateMemory(newCapacity);

    assert(newArray != nullptr);

    copyRange(this->data , this->data+size , newArray);

    std::swap(this->data , newArray);

    this->capacity = newCapacity;

    destructAndDeleteRange(newArray , (newArray + this->size));

 
}

template <typename Type>
DynamicArray<Type>::DynamicArray():size(0) , capacity(0) , data(nullptr) 
{
}

template <typename Type>
DynamicArray<Type>::DynamicArray(const int &size_):size(0) , capacity(size_) 
{
    try
    {
        this->data = allocateMemory(size_);
        
    }
    catch(...)
    {
        throw std::out_of_range("can't allocate memory");
    }
    
}

template <typename Type>
DynamicArray<Type>::DynamicArray(const DynamicArray<Type> & other)
{
    this->size = other.size; 
    
    this->capacity = other.capacity;
    this->data = allocateMemory(capacity);
    
    Type* location = this->data;
    this->copyRange(other.data , other.data + other.size , location);
}

template <typename Type>
DynamicArray<Type> &DynamicArray<Type>::operator=(const DynamicArray<Type> &other)
{
    if(this != &other)
    {
        DynamicArray<Type> cpy(other);

        std::swap(this->data, cpy.data);

        std::swap(this->size, cpy.size);

        std::swap(this->capacity, cpy.capacity);
    }
    return *this;
}

template <typename Type>
DynamicArray<Type>::~DynamicArray()
{
    destructAndDeleteRange(this->data , this->data+size);
}

template <typename Type>
void DynamicArray<Type>::push_back(const Type & item)
{

    if(this->size == capacity )
    {  
        capacity = (capacity ? capacity : 1);
        this->resize(this->capacity*2);
    }

    new(this->data+size)Type(item);

    this->size++;
}

template <typename Type>
void DynamicArray<Type>::pop_back()
{
    if(this->size > 0)
    {
        (this->data + (size-1)) ->~Type();
      
        this->size--;
    }
}

template <typename Type>
const Type &DynamicArray<Type>::operator[](const size_t & index) const
{
    assert(index < size );

    return this->data[index];
}

template <typename Type>
Type &DynamicArray<Type>::operator[](const size_t &index)
{
    assert(index < size);
    
    return this->data[index];

}

template <typename Type>
inline const size_t &DynamicArray<Type>::getCapacity()const
{
    return this->capacity;

}

template <typename Type>
inline const size_t &DynamicArray<Type>::getSize()const
{
    
    return this->size;

}