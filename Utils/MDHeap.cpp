//
//  MDHeap.cpp
//  MDCollisionDetection
//
//  Created by Artem Kravchenko on 5/16/14.
//  Copyright (c) 2014 ShowTime. All rights reserved.
//

#include "MDHeap.h"
Heap::Heap()
{
}

Heap::~Heap()
{
}

void Heap::Insert(int element)
{
    _heap.push_back(element);
    HeapIfYUp(static_cast<int>(_heap.size() - 1));
}

int Heap::DeleteMin()
{
    int min = _heap.front();
    _heap[0] = _heap.at(_heap.size() - 1);
    _heap.pop_back();
    HeapIfYDown(0);
    return min;
}

void Heap::HeapIfYUp(int index)
{
    //cout << "index=" << index << endl;
    //cout << "parent(index)=" << parent(index) << endl;
    //cout << "heap[parent(index)]=" << heap[parent(index)] << endl;
    //cout << "heap[index]=" << heap[index] << endl;
    while ( ( index > 0 ) && ( Parent(index) >= 0 ) &&
           ( _heap[Parent(index)] > _heap[index] ) )
    {
        int tmp = _heap[Parent(index)];
        _heap[Parent(index)] = _heap[index];
        _heap[index] = tmp;
        index = Parent(index);
    }
}

void Heap::HeapIfYDown(int index)
{
    //cout << "index=" << index << endl;
    //cout << "left(index)=" << left(index) << endl;
    //cout << "right(index)=" << right(index) << endl;
    int child = Left(index);
    if ( ( child > 0 ) && ( Right(index) > 0 ) &&
        ( _heap[child] > _heap[Right(index)] ) )
    {
        child = Right(index);
    }
    if ( child > 0 )
    {
        int tmp = _heap[index];
        _heap[index] = _heap[child];
        _heap[child] = tmp;
        HeapIfYDown(child);
    }
}

int Heap::Left(int parent)
{
    int i = ( parent << 1 ) + 1; // 2 * parent + 1
    return ( i < _heap.size() ) ? i : -1;
}

int Heap::Right(int parent)
{
    int i = ( parent << 1 ) + 2; // 2 * parent + 2
    return ( i < _heap.size() ) ? i : -1;
}

int Heap::Parent(int child)
{
    if (child != 0)
    {
        int i = (child - 1) >> 1;
        return i;
    }
    return -1;
}