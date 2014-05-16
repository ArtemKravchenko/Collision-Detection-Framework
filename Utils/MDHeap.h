//
//  MDHeap.h
//  MDCollisionDetection
//
//  Created by Artem Kravchenko on 5/16/14.
//  Copyright (c) 2014 ShowTime. All rights reserved.
//

#ifndef __MDCollisionDetection__MDHeap__
#define __MDCollisionDetection__MDHeap__

#include <iostream>
#include <vector>

class Heap {
public:
    Heap();
    ~Heap();
    void Insert(int element);
    int DeleteMin();
    unsigned long Size() { return _heap.size(); }
private:
    int Left(int parent);
    int Right(int parent);
    int Parent(int child);
    void HeapIfYUp(int index);
    void HeapIfYDown(int index);
private:
    std::vector<int> _heap;
};
#endif /* defined(__MDCollisionDetection__MDHeap__) */
