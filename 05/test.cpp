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

int main() {
    Data x { 1, true, 2 };

    std::stringstream stream;

    Serializer serializer(stream);
    const Error err1 = serializer.save(x);
    assert(err1 != Error::CorruptedArchive);
    Data y { 0, false, 0 };

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    assert(err == Error::NoError);

    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);

    Data e {1323, false, (uint64_t)-3};
    serializer.save(e);
    Data m { 0, false, 0 };

    const Error err2 = deserializer.load(m);

    assert(err2 == Error::NoError);

    assert(m.a == 1323);
    assert(m.b == false);
    assert(m.c == (uint64_t)-3);
}
