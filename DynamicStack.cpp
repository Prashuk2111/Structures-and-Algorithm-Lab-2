#include "DynamicStack.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

typedef DynamicStack::StackItem StackItem;  // for simplicity
const StackItem DynamicStack::EMPTY_STACK = -999;

DynamicStack::DynamicStack()
{
    init_capacity_ = 16;
    capacity_ = 16;
    items_ = new StackItem[capacity_];
    size_ = 0;
}

DynamicStack::DynamicStack(unsigned int capacity)
{
    if (capacity == 0)
        capacity_ = 16;
    else
        capacity_ = capacity;
    init_capacity_ = capacity;
    size_ = 0;
    items_ = new StackItem[capacity_];
}

DynamicStack::~DynamicStack()
{
    delete [] items_;
    items_ = NULL;
}

bool DynamicStack::empty() const
{
    // if size is 0, return true
    return !size_;
}

int DynamicStack::size() const
{
    return size_;
}

void DynamicStack::push(StackItem value)
{
    if(size_ == 0){
        items_[0] = value;
        size_++;
    }
    
    else if(size_ < capacity_){
        // shift everything
        for (int i=0; i<size_; i++) {
            items_[i+1] = items_[i];
        }
        items_[0] = value;
        size_++;
    }
    else{
        StackItem* temp = items_;
        capacity_=capacity_*2;
        items_ = new StackItem[capacity_];
        for(int i=0;i<size_; i++)
        {
            items_[i+1]=temp[i];
        }
        items_[0]=value;
        size_++;
        delete[] temp;
        temp=NULL;
    }
}

StackItem DynamicStack::pop()
{
    if(empty())
        return EMPTY_STACK;
    int temp = items_[0];
    for(int i=0; i<size_-1; i++){
        items_[i] = items_[i+1];
    }
    size_--;
    if(size_ <= 0.25*capacity_ && capacity_>init_capacity_){
        StackItem* tempStack = items_;
        capacity_ /= 2;
        items_ = new StackItem[capacity_];
        for(int j=0; j<size_; j++){
            items_[j] = tempStack[j];
        }
        delete [] tempStack;
    }
    return temp;
}

StackItem DynamicStack::peek() const
{
    if(empty()){
        return EMPTY_STACK;
    }
    return items_[0];
}

void DynamicStack::print() const
{
    for(int i=0; i<size_; i++){
        cout << items_[i];
    }
}
