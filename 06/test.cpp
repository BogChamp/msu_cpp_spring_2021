#include <cassert>
#include <iostream>
#include "format.hpp"

void TestCorrectness() {
    auto text = format("{1}+{1} = {0}", 2, "one");
    assert(text == "one+one = 2");

    text = format("no brackets");
    assert(text == "no brackets");

    text = format("no brackets 2 part", 23, "text", 0.5);
    assert(text == "no brackets 2 part");

    text = format("{0}{1}{2}", 1,2,3);
    assert(text == "123");

    text = format("{4} is {3} {0} {2} {1}", "language", "world", "in the", "the best","C++");
    assert(text == "C++ is the best language in the world");

    text = format("not {1}  {3} ", 0, "all", 0, "args");
    assert(text == "not all  args ");

    text = format("",1,"char");
    assert(text == "");
}

void TestException() {
    std::string text = "";

    int key = 0;
    try {
        text = format("{0", "string");
    } catch(brackets&) {
        ++key;
    }
    assert(key == 1);

    try {
        text = format("{{1}}", 0, 1);
    } catch(wrong_number&) {
        ++key;
    }
    assert(key == 2);

    try {
        text = format("Text {text}");
    } catch(wrong_number&) {
        ++key;
    }
    assert(key == 3);

    try {
        text = format("{0}, {1}", 5);
    } catch(no_arg&) {
        ++key;
    }
    assert(key == 4);

    try {
        text = format("My name is {}", "Steve");
    } catch (no_number&) {
        ++key;
    }
    assert(key == 5);
}

int main() {
    TestCorrectness();
    TestException();
}
