#include "Allocator.h"

Allocator::Allocator() {
    this->allocatedArray = nullptr;
    this->maxSize = 0;
    this->spaceUsed = 0;
}


Allocator::~Allocator() {
    if (this->allocatedArray) {
        delete[] this->allocatedArray;
    }
}

void Allocator::makeAllocator(size_t maxSize) {
    if (this->allocatedArray) {
        delete[] this->allocatedArray;
        this->reset();
    }

    this->allocatedArray = new char[maxSize];
    this->maxSize = maxSize;
}


char* Allocator::alloc(size_t size) {
    if (!this->allocatedArray)
        return nullptr;

    if (this->maxSize < this->spaceUsed + size)
        return nullptr;

    char* result = this->allocatedArray + this->spaceUsed;
    this->spaceUsed += size;

    return result;
}

void Allocator::reset() {
    this->spaceUsed = 0;
}
