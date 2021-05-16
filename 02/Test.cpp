#include <iostream>
#include "parser.h"

void f1(uint64_t a) {
    std::cout << "Numerical token " << a << std::endl;
}

void f2(const std::string a) {
    std::cout << "String Token " << a <<std::endl;
}

void f3(uint64_t a) {
    std::cout << "Num " << a << std::endl;
}

void f4(const std::string a) {
    std::cout << "String " << a << std::endl;
}

void start() {
    std::cout << "We are starting to parse!" << std::endl;
}

void end() {
    std::cout << "We ended to parse!" << std::endl;
}

void TEST1() {  // проверка, работают ли колбеки для чисел и цифр.
    Parser parser;
    parser.set_digit_callback(f1);
    parser.set_str_callback(f2);
    parser.parse("20 50 100   18446744073709551615 9999999999999999999999999999");
    parser.parse("It's a text. Just text. 6 8 10 1000  Just numbers.");
}

void TEST2() {  // проверка, работают ли колбеки перед началом и после
    Parser parser;
    parser.set_start_callback(start);
    parser.set_end_callback(end);
    parser.set_digit_callback(f3);
    parser.set_str_callback(f4);
    // здесь 000564 должно превратится в 564
    parser.parse("Haudy ho! Ho-ho-ho! 12 90 849 457435 000564 . NUMBERS! back");
}
// если запустить тесты, то можно увидеть, что все токены опознаются верно
int main() {
    TEST1();
    TEST2();
}
