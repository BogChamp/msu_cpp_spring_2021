#pragma once

template <class T>
class Allocator {
 public:
    T* allocate(size_t size);
    void deallocate(T* array);
};

template <class T>
T* Allocator<T>::allocate(size_t size) {
    if (size)
        return new T[size];
    else
        return nullptr;
}

template <class T>
void Allocator<T>::deallocate(T* array) {
    if (array) {
        delete[] array;
        array = nullptr;
    }
}
