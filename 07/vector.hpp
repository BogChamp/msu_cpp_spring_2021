#pragma once
#include <iostream>
#include "iterators.hpp"
#include "allocator.hpp"

template <class T>
class Vector {
    T* array;
    size_t _size;
    size_t _capacity;
    Allocator<T> allocator;

 public:
    Vector();
    explicit Vector(size_t size_);
    Vector(size_t size_, const T& arg);
    Vector(const Vector<T>& other);
    Vector(Vector<T>&& other);
    Vector(std::initializer_list<T> args);
    ~Vector();
    Vector<T>& operator=(const Vector<T>& arg);
    Vector<T>& operator=(Vector<T>&& arg);
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    void push_back(const T& arg);
    void push_back(T&& arg);
    void pop_back();

    template <class... Args>
    void emplace_back(T&& arg, Args&&... args) {
        push_back(arg);
        emplace_back(std::forward<Args>(args) ...);
    }

    void emplace_back(T&& args) {
        push_back(args);
    }

    bool empty() const noexcept;
    size_t size() const noexcept;
    void clear() noexcept;
    Iterator<T> begin() noexcept;
    ReverseIterator<T> rbegin() noexcept;
    Iterator<T> end() noexcept;
    ReverseIterator<T> rend() noexcept;
    void resize(size_t size_);
    void resize(size_t size_, const T& arg);
    void reserve(size_t size_);
    size_t capacity() const noexcept;
};

template <class T>
Vector<T>::Vector() {
    _size = 0;
    _capacity = 8;
    array = allocator.allocate(_capacity);
}

template <class T>
Vector<T>::Vector(size_t size_) {
    _size = size_;
    _capacity = size_;
    array = allocator.allocate(_capacity);
}

template <class T>
Vector<T>::Vector(size_t size_, const T& arg) {
    _size = size_;
    _capacity = size_;
    array = allocator.allocate(_capacity);
    for (size_t i = 0; i < _capacity; ++i)
        array[i] = arg;
}

template <class T>
Vector<T>::Vector(const Vector<T>& other) {
    _size = other._size;
    _capacity = other._capacity;
    array = allocator.allocate(_capacity);
    for (size_t i = 0; i < _size; ++i)
        array[i] = other.array[i];
}

template <class T>
Vector<T>::Vector(Vector<T>&& other) {
    _size = other._size;
    _capacity = other._capacity;
    array = other.array;
    other.array = nullptr;
}

template <class T>
Vector<T>::Vector(std::initializer_list<T> args) {
    _size = args.size();
    _capacity = args.size();
    if (_size) {
        array = allocator.allocate(_capacity);
        std::copy(args.begin(), args.end(), array);
    } else {
        array = nullptr;
    }
}

template <class T>
Vector<T>::~Vector() {
    allocator.deallocate(array);
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
    if (array == other.array)
        return *this;
    _size = other._size;
    _capacity = other._capacity;

    allocator.deallocate(array);
    array = allocator.allocate(_capacity);
    for (size_t i = 0; i < _size; ++i)
        array[i] = other.array[i];

    return *this;
}

template<class T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) {
    if (array == other.array)
        return *this;
    _size = other._size;
    _capacity = other._capacity;

    allocator.deallocate(array);
    array = other.array;
    other.array = nullptr;

    return *this;
}

template <class T>
T& Vector<T>::operator[](size_t index) {
    if (index >= _size)
        throw std::out_of_range("wrong index");

    return array[index];
}

template <class T>
const T& Vector<T>::operator[](size_t index) const {
    if (index >= _size)
        throw std::out_of_range("wrong index");

    return array[index];
}

template <class T>
void Vector<T>::push_back(const T& arg) {
    if (_size >= _capacity)
        this->reserve(2 * _capacity);
    array[_size++] = arg;
}

template <class T>
void Vector<T>::push_back(T&& arg) {
    if (_size >= _capacity)
        this->reserve(2 * _capacity);
    array[_size++] = arg;
}

template <class T>
void Vector<T>::pop_back() {
    if (_size)
        --_size;
}

template <class T>
bool Vector<T>::empty() const noexcept {
    return (_size == 0);
}

template <class T>
size_t Vector<T>::size() const noexcept {
    return _size;
}

template <class T>
void Vector<T>::clear() noexcept {
    _size = 0;
}

template <class T>
Iterator<T> Vector<T>::begin() noexcept {
    return Iterator<T>(array);
}

template <class T>
ReverseIterator<T> Vector<T>::rbegin() noexcept {
    return ReverseIterator<T>(array + _size - 1);
}

template <class T>
Iterator<T> Vector<T>::end() noexcept {
    return Iterator<T>(array + _size);
}

template <class T>
ReverseIterator<T> Vector<T>::rend() noexcept {
    return ReverseIterator<T>(array - 1);
}

template <class T>
void Vector<T>::resize(size_t size_) {
    if (size_ > _capacity) {
        T* tmp = array;
        _capacity = (_capacity * 2 > size_) ? (_capacity * 2) : size_;
        array = allocator.allocate(_capacity);

        for (size_t i = 0; i < _size; ++i)
            array[i] = tmp[i];
        allocator.deallocate(tmp);
    }
    _size = size_;
}

template <class T>
void Vector<T>::resize(size_t size_, const T& arg) {
    if (size_ > _size) {
        if (size_ > _capacity) {
            T* tmp = array;
            _capacity = (_capacity * 2 > size_) ? (_capacity * 2) : size_;
            array = allocator.allocate(_capacity);

            for (size_t i = 0; i < _size; ++i)
                array[i] = tmp[i];
            allocator.deallocate(tmp);
        }
        for (size_t i = _size; i < size_; ++i)
            array[i] = arg;
    }
    _size = size_;
}

template <class T>
void Vector<T>::reserve(size_t size_) {
    if (size_ > _capacity) {
        T* tmp = array;
        _capacity = (_capacity * 2 > size_) ? (_capacity * 2) : size_;
        array = allocator.allocate(_capacity);

        for (size_t i = 0; i < _size; ++i)
            array[i] = tmp[i];
        allocator.deallocate(tmp);
    }
}

template <class T>
size_t Vector<T>::capacity() const noexcept {
    return _capacity;
}
