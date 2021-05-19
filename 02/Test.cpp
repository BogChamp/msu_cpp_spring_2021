#include <iostream>
#include <vector>
#include <cassert>
#include "parser.h"

std::vector<uint64_t> digits;  // сохраняем числа
std::vector<std::string> string;  // сохраняем строки

void f1(uint64_t digit) {
    digits.push_back(digit);
}

void f2(std::string str) {
    string.push_back(str);
}

void start() {
    string.push_back("START");
}

void end() {
    string.push_back("END");
}

void TestParser() {  // проверка, работают ли колбеки для чисел и цифр.
    Parser parser;
    parser.set_digit_callback(f1);
    parser.set_str_callback(f2);
    parser.parse("20 50 100  18446744073709551615 9999999999999999999999999999");
    assert(digits[0] == 20);
    assert(digits[1] == 50);
    assert(digits[2] == 100);
    uint64_t max = -1;
    assert(digits[3] == max);
    assert(string[0] == "9999999999999999999999999999");
    digits.clear();
    string.clear();
    parser.parse("It's a text. Just text. 6 8 10 1000  Just numbers.");
    assert(digits[0] == 6);
    assert(digits[1] == 8);
    assert(digits[2] == 10);
    assert(digits[3] == 1000);
    assert(string[0] == "It's");
    assert(string[1] == "a");
    assert(string[2] == "text.");
    assert(string[3] == "Just");
    assert(string[4] == "text.");
    assert(string[5] == "Just");
    assert(string[6] == "numbers.");
    digits.clear();
    string.clear();
}

void TestAllCallbacks() {  // проверка, работают ли колбеки перед началом и после
    Parser parser;
    parser.set_start_callback(start);
    parser.set_end_callback(end);
    parser.set_digit_callback(f1);
    parser.set_str_callback(f2);
    // здесь 000564 должно превратится в 564
    parser.parse("Haudy ho! Ho-ho-ho! 12 90 849 457435 000564 . NUMBERS! back");
    assert(digits[0] == 12);
    assert(digits[1] == 90);
    assert(digits[2] == 849);
    assert(digits[3] == 457435);
    assert(digits[4] == 564);
    assert(string[0] == "START");
    assert(string[1] == "Haudy");
    assert(string[2] == "ho!");
    assert(string[3] == "Ho-ho-ho!");
    assert(string[4] == ".");
    assert(string[5] == "NUMBERS!");
    assert(string[6] == "back");
    assert(string[7] == "END");
    digits.clear();
    string.clear();
}

void TestMonoTokens() {
    Parser parser;
    parser.set_digit_callback(f1);
    parser.set_str_callback(f2);
    parser.parse("");
    assert(digits.empty());
    assert(string.empty());
    parser.parse("248");
    assert(digits[0] == 248);
    parser.parse("qwerty");
    assert(string[0] == "qwerty");
    parser.parse("5");
    assert(digits[1] == 5);
    parser.parse("y");
    assert(string[1] == "y");
    parser.parse("M");
    assert(string[2] == "M");
    digits.clear();
    string.clear();
}

void TestDigits() {
    Parser parser;
    parser.set_digit_callback(f1);
    parser.set_str_callback(f2);
    parser.parse("0 -1 234 18446744073709551615 0044000");
    assert(digits[0] == 0);
    assert(digits[1] == 234);
    assert(digits[2] == (uint64_t)-1);
    assert(digits[3] == 44000);
    assert(string[0] == "-1");
    parser.parse("0.23 18446744073709551616 18446744073709551614 000");
    assert(digits[4] == (uint64_t)-2);
    assert(digits[5] == 0);
    assert(string[1] == "0.23");
    assert(string[2] == "18446744073709551616");
    digits.clear();
    string.clear();
}

void TestSeparator() {
    Parser parser;
    parser.set_digit_callback(f1);
    parser.set_str_callback(f2);
    parser.parse("A\n +23 \t\t ");
    assert(string[0] == "A");
    assert(string[1] == "+23");
    parser.parse("\n   \t\t   \n ");
    assert(digits.size() == 0);
    assert(string.size() == 2);
    parser.parse("Hello!\nYear\t2021\t");
    assert(string[2] == "Hello!");
    assert(string[3] == "Year");
    assert(digits[0] == 2021);
    digits.clear();
    string.clear();
}

void TestSmesy() {
    Parser parser;
    parser.set_digit_callback(f1);
    parser.set_str_callback(f2);
    parser.parse("l 54r tt344 00y U32) 7+8 0001");
    assert(string[0] == "l");
    assert(string[1] == "54r");
    assert(string[2] == "tt344");
    assert(string[3] == "00y");
    assert(string[4] == "U32)");
    assert(string[5] == "7+8");
    assert(digits[0] == 1);
    digits.clear();
    string.clear();
}
// если запустить тесты, то можно увидеть, что все токены опознаются верно
int main() {
    TestParser();
    TestAllCallbacks();
    TestMonoTokens();
    TestDigits();
    TestSeparator();
    TestSmesy();
}
