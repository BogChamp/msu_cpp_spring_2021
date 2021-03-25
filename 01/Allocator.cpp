#include "Allocator.h"

Allocator::Allocator() {
    allocatedArray = nullptr;
    maxSize = 0;
    spaceUsed = 0;
}


Allocator::~Allocator() {
    if (allocatedArray) {
        delete[] allocatedArray;
    }
}

void Allocator::makeAllocator(size_t othermaxSize) {
    if (allocatedArray) {
        delete[] allocatedArray;
        reset();
    }

    if (static_cast<int>(othermaxSize) <= 0)
        allocatedArray = nullptr;
    else
        allocatedArray = new char[othermaxSize];

    maxSize = othermaxSize;
}


char* Allocator::alloc(size_t size) {
    if (!allocatedArray)
        return nullptr;

    if (static_cast<int>(size) <= 0)
        return nullptr;

    if (maxSize < spaceUsed + size)
        return nullptr;

    

    char* result = allocatedArray + spaceUsed;
    spaceUsed += size;

    return result;
}

void Allocator::reset() {
    spaceUsed = 0;
}
