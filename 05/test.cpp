#include <iostream>
#include <cassert>
#include <sstream>
#include "serializer.h"


struct Data {
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer) {
        return serializer(a, b, c);
    }
};

struct UintData {
    uint64_t a;

    template <class Serializer>
    Error serialize(Serializer& serializer) {
        return serializer(a);
    }
};

struct BoolData {
    bool b;

    template <class Serializer>
    Error serialize(Serializer& serializer) {
        return serializer(b);
    }
};

struct String {
    std::string text;
    std::string text2;
    std::string text3;

    template <class Serializer>
    Error serialize(Serializer& serializer) {
        return serializer(text);
    }
};

void WorkTest() {
    Data x { 1, true, 2 };

    std::stringstream stream;

    Serializer serializer(stream);
    const Error err1 = serializer.save(x);
    assert(err1 != Error::CorruptedArchive);
    assert(stream.str() == "1 true 2 ");
    Data y { 0, false, 0 };

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    assert(err == Error::NoError);

    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);

    stream.str("");
    Data e {1323, false, (uint64_t)-3};
    assert(serializer.save(e) == Error::NoError);
    assert(stream.str() == "1323 false 18446744073709551613 ");
    Data m { 0, false, 0 };

    const Error err2 = deserializer.load(m);

    assert(err2 == Error::NoError);

    assert(m.a == 1323);
    assert(m.b == false);
    assert(m.c == (uint64_t)-3);
}

void SingleDataTest() {
    UintData x{23};
    std::stringstream stream;

    Serializer serializer(stream);
    const Error err1 = serializer.save(x);
    assert(err1 == Error::NoError);
    assert(stream.str() == "23 ");
    Deserializer deserializer(stream);
    UintData y{0};
    const Error err2 = deserializer.load(y);
    assert(err2 == Error::NoError);
    assert(y.a == 23);

    stream.str("");
    BoolData a{true};
    assert(serializer.save(a) == Error::NoError);
    assert(stream.str() == "true ");
    BoolData b{false};
    assert(deserializer.load(b) == Error::NoError);
    assert(b.b == true);
}

void DeserializeTest() {
    Data x{0, true, 1};
    std::stringstream stream;

    Serializer serializer(stream);
    Deserializer deserializer(stream);
    assert(serializer.save(x) == Error::NoError);
    assert(stream.str() == "0 true 1 ");

    UintData y{1000};
    assert(deserializer.load(y) == Error::CorruptedArchive);
    stream.str("");
    BoolData z{true};
    assert(serializer.save(x) == Error::NoError);
    assert(stream.str() == "0 true 1 ");
    assert(deserializer.load(z) == Error::CorruptedArchive);
    stream.str("");

    UintData c{678};
    assert(serializer.save(c) == Error::NoError);
    assert(stream.str() == "678 ");
    assert(deserializer.load(x) == Error::CorruptedArchive);
}

void InvalidTest() {
    BoolData x{0};

    std::stringstream stream;
    Serializer serializer(stream);
    Deserializer deserializer(stream);

    assert(serializer.save(x) == Error::NoError);
    assert(stream.str() == "false ");

    BoolData y{1};
    assert(deserializer.load(y) == Error::NoError);
    assert(y.b == false);
    stream.str("");

    UintData a{true};
    assert(serializer.save(a) == Error::NoError);
    assert(stream.str() == "1 ");
    UintData b{false};
    assert(deserializer.load(b) == Error::NoError);
    assert(b.a == 1);
    stream.str("");

    assert(serializer.save(a) == Error::NoError);
    assert(deserializer.load(x) == Error::CorruptedArchive);
    stream.str("");
    Data data{0, 1, true};
    assert(serializer.save(data) == Error::NoError);
    assert(stream.str() == "0 true 1 ");
    Data data2{5, true, 9};
    assert(deserializer.load(data2) == Error::NoError);
    assert(data2.a == 0);
    assert(data2.b == true);
    assert(data2.c == 1);

    String data3{"e", "bbb", "a"};
    assert(serializer.save(data3) == Error::CorruptedArchive);
    stream.str("");;
}

int main() {
    WorkTest();
    SingleDataTest();
    //DeserializeTest();
    InvalidTest();
}
