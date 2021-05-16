#include <iostream>
#include "Matrix.h"
#include <cassert>

void TEST1() {
    Matrix b(5, 8);
    // проверяем, верное ли количество строк/столбцов
    assert(b.column_count() == 8);
    assert(b.row_count() == 5);
}

void TEST2() {
    Matrix b(3, 4);
    b[0][1] = 5;
    b[1][2] = 6;
    // проверяем, работает ли индексация нормально
    assert(b[0][1] == 5);
    assert(b[1][2] == 6);
}

void TEST3() {  // проверяем, работает ли нормально сравнение
    Matrix b(3, 4);
    for (size_t i = 0; i < b.row_count(); ++i) {
        for (size_t j = 0; j < b.column_count(); ++j) {
            b[i][j] = (int32_t)(i+j);
        }
    }

    for (size_t i = 0; i < b.row_count(); ++i) {
        for (size_t j = 0; j < b.column_count(); ++j) {
            assert(b[i][j] == (int32_t)(i + j));
        }
    }

    Matrix a(3, 4);
    for (size_t i = 0; i < a.row_count(); ++i) {
        for (size_t j = 0; j < a.column_count(); ++j) {
            a[i][j] = (int32_t)(2*i);
        }
    }
    assert(a != b);
    a = b;
    assert(a == b);
    for (size_t i = 0; i < a.row_count(); ++i) {
        for (size_t j = 0; j < a.column_count(); ++j) {
            assert(a[i][j] == (int32_t)(i + j));
        }
    }

    Matrix v(1, 2);
    assert(v != b);
}

void TEST4() {
    // проверяем, работает ли нормально умножение и сложение
    Matrix b(4, 4);
    for (size_t i = 0; i < b.row_count(); ++i) {
        for (size_t j = 0; j < b.column_count(); ++j) {
            b[i][j] = (int32_t)(i - j);
        }
    }
    b *= 5;
    for (size_t i = 0; i < b.row_count(); ++i) {
        for (size_t j = 0; j < b.column_count(); ++j) {
            assert(b[i][j] == (int32_t)(5 * (i - j)));
        }
    }

    Matrix v(4, 4);
    for (size_t i = 0; i < v.row_count(); ++i) {
        for (size_t j = 0; j < v.column_count(); ++j) {
            v[i][j] = (int32_t)(i * j);
        }
    }
    Matrix r(4, 4);
    r = b + v;
    // здесь выводятся на экран 3 матрицы
    std::cout << b << std::endl;
    std::cout << v << std::endl;
    std::cout << r << std::endl;
    for (size_t i = 0; i < r.row_count(); ++i) {
        for (size_t j = 0; j < r.column_count(); ++j) {
            assert(r[i][j] == (int32_t)(i * j + 5 * (i - j)));
        }
    }
}

void TEST5() {  // проверям, работают ли исключения
    Matrix v(4, 4);

    for (size_t i = 0; i < v.row_count(); ++i) {
        for (size_t j = 0; j < v.column_count(); ++j) {
            v[i][j] = (int32_t)(i * j);
        }
    }

    try {
        v[4][2] = 3;
    }
    catch(const std::out_of_range& ) {
        std::cout << "Cauht exception, wrong index row" << std::endl;
    }

    try {
        v[1][6] = 3;
    }
    catch(const std::out_of_range& ) {
        std::cout << "Cauht exception, wrong index column" << std::endl;
    }

    try {
        Matrix g(-1, 6);
    }
    catch(const std::out_of_range& ) {
        std::cout << "Cauht exception, wrong matrix size" << std::endl;
    }
}

int main() {
    TEST1();
    TEST2();
    TEST3();
    TEST4();
    TEST5();
}
