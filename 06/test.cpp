#include <cassert>
#include <iostream>
#include "format.hpp"

void TestCorrectness() {
    auto text = format("{1}+{1} = {0}", 2, "one");
    assert(text == "one+one = 2");

    text = format("no brackets");
    assert(text == "no brackets");

    text = format("{0}{1}{2}", 1, 2, 3);
    assert(text == "123");

    text = format("{4} is {3} {0} {2} {1}", "language", "world", "in the", "the best", "C++");
    assert(text == "C++ is the best language in the world");
}

void TestException() {
    std::string text = "";

    int key = 0;
    try {
        text = format("{0", "string");
    } catch(brackets& e) {
        ++key;
    }
    assert(key == 1);

    try {
        text = format("{{1}}", 0, 1);
    } catch(brackets&) {
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
        text = format("My name is {}", "Steve");
    } catch (no_number&) {
        ++key;
    }
    assert(key == 4);
}

void OneArgTest() {
    auto text = format("{0}", "only");
    assert(text == "only");

    int key = 0;
    try {
        text = format("{0}");
    } catch(no_such_arg&) {
        ++key;
    }
    assert(key == 1);

    try {
        text = format("{1}", 2);
    } catch(no_such_arg&) {
        ++key;
    }
    assert(key == 2);
}

void ErrorTest() {
    auto text = format("{0}", 5);

    int key = 0;
    try {
        text = format("{0}{", "string");
    } catch(brackets&) {
        ++key;
    }
    assert(key == 1);

    try {
       text = format("Just {0}}", "testing");
    }
    catch(brackets&){
        ++key;
    }
    assert(key == 2);

    try {
        text = format("Some {{0} in {1}}", "words", "test");
    } catch(brackets&) {
        ++key;
    }
    assert(key == 3);

    try {
        text = format("Some {0}} word", "test");
    } catch(brackets&) {
        ++key;
    }
    assert(key == 4);
}

void WrongNumInBrackets() {
    std::string text = "";

    int key = 0;
    try {
        text = format("{}");
    } catch(no_number&) {
        ++key;
    }
    assert(key == 1);

    try {
        text = format("{{}}{}");
    } catch(brackets&) {
        ++key;
    }
    assert(key == 2);

    try {
        text = format("{string}", "string");
    } catch(wrong_number&) {
        ++key;
    }
    assert(key == 3);

    try {
        text = format("Text {0str} !", 0);
    } catch(wrong_number&) {
        ++key;
    }
    assert(key == 4);

    try {
        text = format("{f1i0}", "text");
    } catch(wrong_number&) {
        ++key;
    }
    assert(key == 5);

    try {
        text = format("{18446744073709551616}", "big num");
    } catch(wrong_number&) {
        ++key;
    }
    assert(key == 6);

    try {
        text = format("{18446744073709551615}", "big num");
    } catch(no_such_arg&) {
        ++key;
    }
    assert(key == 7);
}

void WrongArgs() {
    std::string text;
    int key = 0;
    try {
        text = format("Unused {1}", 1, "args");
    } catch(unused_args&) {
        ++key;
    }
    assert(key == 1);

    try {
        text = format("no brackets 2 part", 23, "text", 0.5);
    } catch(unused_args&) {
        ++key;
    }
    assert(key == 2);

    try {
        text = format("{0}, {1}", 5);
    } catch(no_such_arg&) {
        ++key;
    }
    assert(key == 3);

    try {
        text = format("", 1, "char");
    } catch(unused_args&) {
        ++key;
    }
    assert(key == 4);
}

int main() {
    TestCorrectness();
    TestException();
    OneArgTest();
    ErrorTest();
    WrongNumInBrackets();
    WrongArgs();
}
