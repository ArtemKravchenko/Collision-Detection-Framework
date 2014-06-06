//
//  CDHeap.h
//  CDCollisionDetection
//
//  Created by Artem Kravchenko on 5/16/14.
//  Copyright (c) 2014 ShowTime. All rights reserved.
//

#ifndef __CDCollisionDetection__CDHeap__
#define __CDCollisionDetection__CDHeap__

#include <vector>
#include <cmath>

template<typename T>
class DSHeap {
private:
    T                   *_heap;
    int                 _heapSize;
    int                 _powerOtTwo;
    int                 _initialSize;
    
    
    /*
     If first element grather than second   -> 1
     If first element equal second          -> 0
     If first element less than second      -> -1
     */
    typedef int (*comparerFunction)(T, T);
    comparerFunction    _comparer;
    
    //--------------------------------------------------------------------
    // Private functions
    //--------------------------------------------------------------------
    void inline distribution (int index, int *firstObject, int *secondObject)
    {
        int rest = index % 2;
        if (rest == 0)
        {
            *firstObject = index;
            *secondObject = index + 1;
        }
        else
        {
            *firstObject = index - 1;
            *secondObject = index;
        }
    }
    
public:
    //--------------------------------------------------------------------
    // Constructors and destructors
    //--------------------------------------------------------------------
    DSHeap<T>(T *initialArray, int size, comparerFunction cf)
    {
        _comparer = cf;
        _initialSize = size;
        // Compute heap size
        _powerOtTwo = 0;
        _heapSize = 0;
        float stepValue = pow(2, _powerOtTwo);
        
        while (stepValue < _initialSize) {
            _heapSize += stepValue;
            _powerOtTwo++;
            stepValue = pow(2, _powerOtTwo);
        }
        _heapSize += stepValue;
        
        _heap = new T[_heapSize];
        
        // Filling _heapElements
        for (unsigned i = 0; i < _initialSize; i++) {
            _heap[i] = initialArray[i];
        }
        
        for (int i = 0; i < _initialSize; i++) {
            this->insert(i);
        }
    }
    
    DSHeap<T>(std::vector<T> *initialArray, comparerFunction cf)
    {
        _comparer = cf;
        _initialSize = static_cast<int>(initialArray->size());
        // Compute heap size
        _powerOtTwo = 0;
        _heapSize = 0;
        float stepValue = pow(2, _powerOtTwo);
        
        while (stepValue < _initialSize) {
            _heapSize += stepValue;
            _powerOtTwo++;
            stepValue = pow(2, _powerOtTwo);
        }
        _heapSize += stepValue;
        
        _heap = new T[_heapSize];
        
        // Filling _heapElements
        for (unsigned i = 0; i < _initialSize; i++) {
            _heap[i] = initialArray->at(i);
        }
        
        for (int i = 0; i < _initialSize; i++) {
            this->insert(i);
        }
    }
    
    ~DSHeap<T>()
    {
        delete _heap;
        _heap = 0;
    }
    //--------------------------------------------------------------------
    // Public functions
    //--------------------------------------------------------------------
    void insert(int index)
    {
        int firstComparedObject, secondComparedObject, totalCountOfElementThatLeft = 0, result, indexOfNextCell;
        int localPowerOfTwo = _powerOtTwo;
        int subtreeIndex = 0;
        
        distribution(index, &firstComparedObject, &secondComparedObject);
        
        while (true)
        {
            T obj1 = _heap[firstComparedObject];
            T obj2 = _heap[secondComparedObject];
            if (obj1 == NULL)
                result = 1;
            else if (obj2 == NULL)
                result = -1;
            else
                result = _comparer(obj1, obj2);
            // Compute index of next cell in _heap
            subtreeIndex = (secondComparedObject - totalCountOfElementThatLeft) / 2;
            totalCountOfElementThatLeft += pow(2, localPowerOfTwo--);
            indexOfNextCell = totalCountOfElementThatLeft + subtreeIndex;
            if (result < 1) {
                _heap[indexOfNextCell] = _heap[firstComparedObject];
            } else {
                _heap[indexOfNextCell] = _heap[secondComparedObject];
            }
            // The next element is not a top of heap - continue computation
            if (indexOfNextCell != _heapSize - 1)
            {
                distribution(indexOfNextCell, &firstComparedObject, &secondComparedObject);
            }
            else
            {
                break;
            }
        }
        
    }
    
    T top() { return _heap[_heapSize - 1]; }
    
    unsigned long size() { return _heapSize; }
};
#endif /* defined(__CDCollisionDetection__CDHeap__) */


