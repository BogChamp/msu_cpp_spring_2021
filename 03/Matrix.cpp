#include "Matrix.h"

Matrix::Matrix(size_t row, size_t col) {
    if (((signed long)col <= 0) || ((signed long)row <= 0))
        throw std::out_of_range("Matrix can't be this size");
    columns = col;
    rows = row;

    matrix = new ProxyRow[rows];
    for(size_t i = 0; i < rows; ++i)
        matrix[i] = ProxyRow(columns);
}

Matrix::Matrix(const Matrix& other) {
    columns = other.column_count();
    rows = other.row_count();
    matrix = new ProxyRow[rows];

    for(size_t i = 0; i < rows; ++i) {
        matrix[i] = ProxyRow(columns);
        for(size_t j = 0; j < columns; ++j) {
            matrix[i][j] = other[i][j];
        }
    }
}

Matrix::~Matrix() {
    delete[] matrix;
}

size_t Matrix::column_count() const {return columns;}

size_t Matrix::row_count() const {return rows;}

ProxyRow& Matrix::operator[](size_t index) const{
    if (index < rows) {
        return matrix[index];
    }
    throw std::out_of_range("Out of row range");
}

Matrix Matrix::operator*(int32_t num) const{
    Matrix tmp(*this);
    for(size_t i = 0; i < rows; ++i) {
        for(size_t j = 0; j < columns; ++j) {
            tmp[i][j] *= num;
        }
    }
    return tmp;
}

Matrix& Matrix::operator*=(int32_t num) {
    for(size_t i = 0; i < rows; ++i) {
        for(size_t j = 0; j < columns; ++j) {
            matrix[i][j] *= num;
        }
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix& other) const {
    if ((rows != other.row_count()) || (columns != other.column_count()))
        throw std::out_of_range("Size's of matricies should be the same");
    Matrix tmp(*this);
    for(size_t i = 0; i < rows; ++i) {
        for(size_t j = 0; j < columns; ++j) {
            tmp[i][j] += other[i][j];
        }
    }
    return tmp;
}

Matrix& Matrix::operator=(const Matrix& other) {
    if ((rows != other.row_count()) || (columns != other.column_count()))
        throw std::out_of_range("Size's of matricies should be the same");
    for(size_t i = 0; i < rows; ++i) {
        for(size_t j = 0; j < columns; ++j) {
            matrix[i][j] = other[i][j];
        }
    }
    return *this;
}

bool Matrix::operator==(const Matrix& other) const {
    if ((rows != other.row_count()) || (columns != other.column_count()))
        return false;
    for(size_t i = 0; i < rows; ++i) {
        for(size_t j = 0; j < columns; ++j) {
            if (matrix[i][j] != other[i][j])
                return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& other) const {
    return !((*this) == other);
}

std::ostream& operator<<(std::ostream &out, const Matrix& other) {
    for (size_t i = 0; i < other.row_count(); ++i) {
        for (size_t j = 0; j < other.column_count(); ++j) {
            out << other[i][j] << " ";
        }
        out << "\n";
    }
    return out;
}

ProxyRow::ProxyRow(size_t len) {
    if (len < 1) {
        length = 0;
        data_ = nullptr;
    } else {
        length = len;
        data_ = new int32_t[length];
    }
}

ProxyRow::~ProxyRow() {
    if (data_ != nullptr)
        delete[] data_;
}

ProxyRow::ProxyRow(const ProxyRow& other) {
    length = other.get_length();
    data_ = new int32_t[length];
    for(size_t i = 0; i < length; ++i)
        data_[i] = other[i];
}

int32_t& ProxyRow::operator[](size_t index) const{ 
    if (index < length) {
        return data_[index];
    }
    throw std::out_of_range("Out of column range");
}

size_t ProxyRow::get_length() const {return length;}

bool ProxyRow::operator==(const ProxyRow& other) const {
    if (length != other.get_length())
        return false;
    for(size_t i = 0; i < length; ++i) {
        if (data_[i] != other[i])
            return false;
    }
    return true;
}

ProxyRow& ProxyRow::operator=(const ProxyRow& other) {
    if ((*this) == other)
        return *this;
    
    if (data_ != nullptr)
        delete[] data_;
    length = other.get_length();
    data_ = new int32_t[length];

    for(size_t i = 0; i < length; ++i)
        data_[i] = other[i];
    return *this;
}
