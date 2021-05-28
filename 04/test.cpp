#include <iostream>
#include <cassert>
#include "bigint.h"

void TestPlus() {
    BigInt a1 = 100;
    BigInt a2("200");
    assert(a1 + a2 == BigInt(300));
    assert(a1 - a2 == BigInt(-100));

    BigInt b1 = BigInt("100000000000000033333333332222222");
    BigInt b2 = BigInt("8475934943430420345983905829");
    assert(b1 + b2 == BigInt("100008475934943463753679316128051"));
    assert(b1 + b2 == b2 + b1);

    BigInt c1("99999999999999");
    BigInt c2("1");
    assert(c1 + c2 == BigInt("100000000000000"));
    assert(c2 + c1 == BigInt("100000000000000"));
    assert(c1 + c1 == BigInt("199999999999998"));

    a1 = BigInt("-34534654765865");
    assert(a1 + c2 == c2 + a1);
    assert(a1 + c2 == BigInt("-34534654765864"));

    a2 = BigInt("34534654765865");
    assert(a1 + a2 == a2 + a1);
    assert(a1 + a2 == BigInt("0"));

    c2 = BigInt ("-1");
    c1 = BigInt("100000000000000");
    assert(c1 + c2 == BigInt("99999999999999"));
}

void TestMinus() {
    BigInt a1("-2423654376538457876");
    BigInt a2("2345325345");
    assert(a1 - a2 == BigInt("-2423654378883783221"));
    assert(a2 - a1 == BigInt("2423654378883783221"));

    BigInt b1("0");
    BigInt b2("2353456547657");
    assert(b1 - b2 == BigInt("-2353456547657"));
    assert(b2 - b1 == BigInt("2353456547657"));

    BigInt c1("111111110000000000000000000000");
    BigInt c2("21");
    assert(c1 - c2 == BigInt("111111109999999999999999999979"));
    assert(c2 - c1 == BigInt("-111111109999999999999999999979"));

    BigInt y1("10000000000000000000000000");
    BigInt y2("123");
    assert(y1 - y2 == BigInt("9999999999999999999999877"));
    assert(y2 - y1 == BigInt("-9999999999999999999999877"));

    BigInt q1("14234668867865835623");
    BigInt q2("2352354326521");
    assert(q1 - q2 == BigInt("14234666515511509102"));
    assert(q2 - q1 == BigInt("-14234666515511509102"));

    BigInt z1("1234567212");
    BigInt z2("2346545634");
    assert(z1 - z2 == BigInt("-1111978422"));
    assert(z2 - z1 == BigInt("1111978422"));

    z1 = BigInt("1001");
    z2 = BigInt("1001");
    assert(z1 - z2 == BigInt("0"));
    assert(z1 - z1 == BigInt("0"));
    assert(c1 + c1 == BigInt("222222220000000000000000000000"));
}

void TestMul() {
    BigInt p1("2342354345435235235");
    BigInt p2("2344543134");
    assert(p1 * p2 == BigInt("5491750797985245011894126490"));
    assert(p2 * p1 == BigInt("5491750797985245011894126490"));

    BigInt q1("-95928403724957234");
    BigInt q2("14234254232345");
    assert(q1 * q2 == BigInt("-1365469286724072371368624533730"));
    assert(q2 * q1 == BigInt("-1365469286724072371368624533730"));

    BigInt z1("-2353465463546354");
    BigInt z2("-97473485342");
    assert(z1 * z2 == BigInt("229400481363888771956543068"));
    assert(z2 * z1 == BigInt("229400481363888771956543068"));

    BigInt a1(0);
    BigInt a2("635479269");
    assert(a1 * a2 == BigInt("0"));
    assert(a2 * a1 == BigInt("0"));
}

void TestUnarMinus() {
    BigInt a = 1;
    assert(-a == -1);
    BigInt b = 0;
    assert(-b == b);
    assert(-b == 0);
    BigInt c("5354737345335435235");
    assert (-c == BigInt("-5354737345335435235"));
    BigInt d("-183781937421432");
    assert (-d == BigInt("183781937421432"));
}

void TestCompare() {
    BigInt a = 100;
    BigInt b = 3829;
    assert(a < b);
    assert(a <= b);

    BigInt c("2142432345");
    BigInt d("32234345");
    assert(c != d);
    assert(c > d);
    assert(c >= d);

    BigInt e("-214235345346436233423423424");
    BigInt f = 123456;
    BigInt t = 0;
    assert(e < f);
    assert(t > e);
    assert(f > t);
}

void TestInt() {
    BigInt a = 5000;
    assert(a > 1000);
    assert(a < 5001);
    assert(a > 0);

    assert(a + 10 == 5010);
    assert(a - 1000 == 4000);
    assert(a * 2 == 10000);
    assert(a - 5001 == -1);
    assert(BigInt(0) == 0);
}

void TestOther() {
    BigInt a = 1;
    BigInt b("123456789012345678901234567890");
    BigInt c = a * b + 2;
    BigInt d;
    d = std::move(c);
    assert(d == a * b + 2);
    a = d + b;
    std::cout << a << std::endl;
}

int main() {
    TestPlus();
    TestMinus();
    TestMul();
    TestUnarMinus();
    TestCompare();
    TestInt();
    TestOther();
}