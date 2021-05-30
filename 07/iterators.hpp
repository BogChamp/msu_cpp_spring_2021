#pragma once

template <class T>
class ParentIterator : std::iterator<std::random_access_iterator_tag, T> {
 protected:
    T* ptr;
 public:
    explicit ParentIterator(T* ptr_) { ptr = ptr_;}
    bool operator==(const ParentIterator<T>& other) const { return ptr == other.ptr; }
    bool operator!=(const ParentIterator<T>& other) const { return ptr != other.ptr; }
    bool operator<(const ParentIterator<T>& other) const { return ptr < other.ptr; }
    bool operator<=(const ParentIterator<T>& other) const { return ptr <= other.ptr; }
    bool operator>(const ParentIterator<T>& other) const { return ptr > other.ptr; }
    bool operator>=(const ParentIterator<T>& other) const {return ptr >= other.ptr; }
    T& operator*() { return *ptr; }
    const T& operator*() const { return *ptr; }
    T& operator[](size_t index) { return ptr[index]; }
    const T& operator[](size_t index) const { return ptr[index]; }
};

template <class T>
class Iterator : public ParentIterator<T> {
 public:
    explicit Iterator(T* ptr_) : ParentIterator<T>(ptr_) {}
    Iterator<T> operator+(size_t shift) const;
    Iterator<T>& operator+=(size_t shift);
    Iterator<T>& operator++();
    Iterator<T> operator-(size_t shift) const;
    Iterator<T>& operator-=(size_t shift);
    Iterator<T>& operator--();
};

template <class T>
class ReverseIterator : public ParentIterator<T> {
 public:
    explicit ReverseIterator(T* ptr_) : ParentIterator<T>(ptr_) {}
    ReverseIterator<T> operator+(size_t shift) const;
    ReverseIterator<T>& operator+=(size_t shift);
    ReverseIterator<T>& operator++();
    ReverseIterator<T> operator-(size_t shift) const;
    ReverseIterator<T>& operator-=(size_t shift);
    ReverseIterator<T>& operator--();
};

template <class T>
Iterator<T> Iterator<T>::operator+(size_t shift) const {
    return Iterator(ParentIterator<T>::ptr + shift);
}

template <class T>
Iterator<T>& Iterator<T>::operator+=(size_t shift) {
    ParentIterator<T>::ptr += shift;
    return *this;
}

template <class T>
Iterator<T>& Iterator<T>::operator++() {
    ++ParentIterator<T>::ptr;
    return *this;
}

template <class T>
Iterator<T> Iterator<T>::operator-(size_t shift) const {
    return Iterator(ParentIterator<T>::ptr - shift);
}

template <class T>
Iterator<T>& Iterator<T>::operator-=(size_t shift) {
    ParentIterator<T>::ptr -= shift;
    return *this;
}

template <class T>
Iterator<T>& Iterator<T>::operator--() {
    --ParentIterator<T>::ptr;
    return *this;
}

template <class T>
ReverseIterator<T> ReverseIterator<T>::operator+(size_t shift) const {
    return ReverseIterator(ParentIterator<T>::ptr - shift);
}

template <class T>
ReverseIterator<T>& ReverseIterator<T>::operator+=(size_t shift) {
    ParentIterator<T>::ptr -= shift;
    return *this;
}

template <class T>
ReverseIterator<T>& ReverseIterator<T>::operator++() {
    --ParentIterator<T>::ptr;
    return *this;
}

template <class T>
ReverseIterator<T> ReverseIterator<T>::operator-(size_t shift) const {
    return ReverseIterator(ParentIterator<T>::ptr + shift);
}

template <class T>
ReverseIterator<T>& ReverseIterator<T>::operator-=(size_t shift) {
    ParentIterator<T>::ptr += shift;
    return *this;
}

template <class T>
ReverseIterator<T>& ReverseIterator<T>::operator--() {
    ++ParentIterator<T>::ptr;
    return *this;
}
