#include<cstring>
#include<iostream>
#include "CircularQueue.hpp"
using namespace std;

typedef CircularQueue::QueueItem QueueItem;
const QueueItem CircularQueue::EMPTY_QUEUE = -999;

CircularQueue::CircularQueue()
{
    head_ = 0;
    size_ = 0;
    tail_ = 0;
    capacity_= 16;
    items_ = new QueueItem(capacity_);
}

CircularQueue::CircularQueue(unsigned int capacity)
{
    head_ = 0;
    size_ = 0;
    tail_ = 0;
    capacity_= capacity;
    items_ = new QueueItem(capacity_);
}

CircularQueue::~CircularQueue()
{
    delete [] items_;
    items_ = NULL;
}

bool CircularQueue::empty() const
{
    return (!size_);
}

bool CircularQueue::full() const
{
    return (size_ == capacity_);
}

int CircularQueue::size() const
{
    return size_;
}

bool CircularQueue::enqueue(QueueItem value)
{
    if(full())
        return 0;
    items_[tail_] = value;
    size_++;
    tail_ = (tail_+1)%capacity_;
    return 1;
}

QueueItem CircularQueue::dequeue()
{
    if(empty())
        return EMPTY_QUEUE;
    size_--;
    QueueItem temp;
    temp = items_[head_];
    head_ = (head_+1)%capacity_;
    return temp;
}

QueueItem CircularQueue::peek() const
{
    if(empty())
        return EMPTY_QUEUE;
    return items_[head_];
}

void CircularQueue::print() const
{
    for (int i=0; i<size(); i++) {
        cout << items_[(head_+i)%capacity_];
    }
}
