#ifndef MSU_CPP_SPRING_2021_02_MATRIX_H_
#define MSU_CPP_SPRING_2021_02_MATRIX_H_
#include <iostream>

class ProxyRow {  // прокси-класс
    size_t length;
    int32_t *data_;
 public:
    ProxyRow(size_t len = 0);
    ~ProxyRow();
    ProxyRow(const ProxyRow& other);
    int32_t& operator[](size_t index) const;
    size_t get_length() const;
    bool operator==(const ProxyRow& other) const;
    ProxyRow& operator=(const ProxyRow& other);
};

class Matrix {
    size_t columns;
    size_t rows;
    ProxyRow* matrix;
 public:
    Matrix(size_t col = 10, size_t row = 10);
    Matrix(const Matrix& other);
    ~Matrix();
    size_t row_count() const;
    size_t column_count() const;
    ProxyRow& operator[](size_t index) const;
    Matrix operator*(int32_t num) const;
    Matrix& operator*=(int32_t num);
    Matrix operator+(const Matrix& other) const;
    Matrix& operator=(const Matrix& other);
    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;
    friend std::ostream& operator<<(std::ostream &out, const Matrix& other);
};

#endif // MSU_CPP_SPRING_2021_02_MATRIX_H_
