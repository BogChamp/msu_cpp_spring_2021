#ifndef MSU_CPP_SPRING_2021_01_ALLOCATOR_H_
#define MSU_CPP_SPRING_2021_01_ALLOCATOR_H_

#include <iostream>

class Allocator {
    char* allocatedArray;
    size_t maxSize;
    size_t spaceUsed;

 public:
        Allocator();
        ~Allocator();
        void makeAllocator(size_t maxSize);
        char* alloc(size_t size);
        void reset();
};

#endif  // MSU_CPP_SPRING_2021_01_ALLOCATOR_H_
