#ifndef MSU_CPP_SPRING_2021_04_BIGINT_H_
#define MSU_CPP_SPRING_2021_04_BIGINT_H_
#include <iostream>
#include <sstream>

class BigInt {
    bool sign;
    uint32_t* vector;
    size_t length;

 public:
    BigInt(int32_t num = 0);
    BigInt(const std::string& num);
    BigInt(const BigInt& other);
    BigInt(BigInt&& other);
    BigInt operator+(const BigInt& other) const;
    BigInt operator-(const BigInt& other) const;
    BigInt operator*(const BigInt& other) const;
    BigInt& operator=(const BigInt& other);
    BigInt& operator=(BigInt&& other);
    BigInt operator-();
    bool operator==(const BigInt& other) const;
    bool operator!=(const BigInt& other) const;
    bool operator<(const BigInt& other) const;
    bool operator>(const BigInt& other) const;
    bool operator<=(const BigInt& other) const;
    bool operator>=(const BigInt& other) const;
    friend std::ostream& operator<<(std::ostream& os, const BigInt& num);
    ~BigInt();
    void read_num(const std::string&& num);
    BigInt sum(const BigInt& first, const BigInt& second) const;
    BigInt dif(const BigInt& first, const BigInt& second) const;
};
#endif  // MSU_CPP_SPRING_2021_04_BIGINT_H_
