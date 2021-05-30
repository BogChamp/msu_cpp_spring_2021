#include <vector>
#include <cassert>
#include "vector.hpp"

void TestElements() {
    Vector<int> a = {1, 2, 3, 4, 5};
    for (int i = 1; i < 6; ++i)
        assert(a[i - 1] == i);

    assert(a.size() == 5);
    a.pop_back();
    assert(a.size() == 4);
    a.push_back(10);
    assert(a[a.size() - 1] == 10);

    assert(a.empty() == false);
    a.clear();
    assert(a.empty() == true);
    assert(a.size() == 0);

    a.emplace_back(78, 56, 300, 45, 9);
    assert(a.size() == 5);
    Vector<int> b = a;

    for (size_t i = 0; i < a.size(); ++i)
        assert(a[i] == b[i]);
}

void TestIterators() {
    Vector<int> a = {-1 , 0, 1, 189};
    std::vector<int> b = {-1, 0, 1, 189};
    int i = 0;
    for (auto it = a.begin(); it < a.end(); ++it) {
        assert(*it == b[i]);
        ++i;
    }

    for (auto it = a.rbegin(); it > a.rend(); ++it) {
        --i;
        assert(*it == b[i]);
    }

    assert(a.size() == b.size());
}

void TestAllocs() {
    Vector<int> a;
    for (int i = 0; i < 5; ++i)
        a.push_back(i);

    assert(a.size() == 5);
    a.resize(2);
    assert(a.size() == 2);
    for (size_t i = 0; i < a.size(); ++i)
        assert(a[i] == static_cast<int>(i));

    size_t tmp = a.capacity();
    a.reserve(100);
    assert(tmp != a.capacity());
    assert(a.capacity() == 100);

    tmp = a.size();
    a.resize(10, 9);
    for (size_t i = tmp; i < a.size(); ++i)
        assert(a[i] == 9);
}

int main() {
    TestElements();
    TestIterators();
    TestAllocs();
}
