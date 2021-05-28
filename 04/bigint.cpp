#include "bigint.h"

size_t INIT_CHUNK_COUNT = 4;
size_t MAX_SIZE = 1000000000;

BigInt::BigInt(int32_t num) {
    length = 1;
    vector =  new uint32_t[length];
    if (num < 0) {
        sign = false;
        num = -num;
    } else {
        sign = true;
    }
    vector[0] = num;
}

BigInt::BigInt(const std::string& num) {
    if (!num.length()) {
        sign = true;
        length = 1;
        vector =  new uint32_t[length];
        vector[0] = 0;
    } else {
        if ((num[0] == '-') && (num.length() > 1))
            sign = false;
        else
            sign = true;

        read_num(std::move(num));
    }
}

BigInt::BigInt(const BigInt& other) {
    length = other.length;
    sign = other.sign;
    vector = new uint32_t[length];
    for (size_t i = 0; i < length; ++i)
        vector[i] = other.vector[i];
}

BigInt::BigInt(BigInt&& other) {
    length = other.length;
    sign = other.sign;
    vector = other.vector;

    other.vector = nullptr;
    other.sign = true;
    other.length = 0;
}

BigInt BigInt::operator+(const BigInt& other) const {
    if (length > other.length) {
        if (sign == other.sign)
            return sum(*this, other);
        else
            return dif(*this, other);
    } else if (length < other.length) {
        if (sign == other.sign)
            return sum(other, *this);
        else
            return dif(other, *this);
    } else {
        if (sign == other.sign) {
            return sum(*this, other);
        } else {
            for (size_t i = 0; i < length; ++i) {
                if (vector[length - i - 1] < other.vector[length - i - 1])
                    return dif(other, *this);
                else if (vector[length - i - 1] > other.vector[length - i - 1])
                    return dif(*this, other);
            }
            return BigInt();
        }
    }
}

BigInt BigInt::operator-(const BigInt& other) const {
    if (length > other.length) {
        if (sign == other.sign)
            return dif(*this, other);
        else
            return sum(*this, other);
    } else if (length < other.length) {
        BigInt tmp(other);
        tmp.sign = !tmp.sign;
        if (sign == other.sign)
            return dif(tmp, *this);
        else
            return sum(tmp, *this);
    } else {
        if (sign != other.sign) {
            return sum(*this, other);
        } else {
            for (size_t i = 0; i < length; ++i) {
                if (vector[length - i - 1] < other.vector[length - i - 1]) {
                    BigInt tmp(other);
                    tmp.sign = !tmp.sign;
                    return dif(tmp, *this);
                } else if (vector[length - i - 1] > other.vector[length - i - 1]) {
                    return dif(*this, other);
                }
            }
            return BigInt();
        }
    }
}

BigInt BigInt::operator*(const BigInt& other) const {
    BigInt tmp;
    tmp.length = length + other.length;
    tmp.sign = (sign == other.sign);

    delete[] tmp.vector;
    tmp.vector = new uint32_t[tmp.length];
    for (size_t i = 0; i < tmp.length; ++i)
        tmp.vector[i] = 0;
    size_t add = 0;

    for (size_t i = 0; i < other.length; ++i) {
        for (size_t j = 0; j < length; ++j) {
            add += 1UL * vector[j] * other.vector[i] + tmp.vector[i + j];
            tmp.vector[i + j] = add % MAX_SIZE;
            add /= MAX_SIZE;
        }
        tmp.vector[i + length] = add;
        add = 0;
    }

    for (size_t i = 0; i < (length + other.length); ++i) {
        if (tmp.vector[length + other.length - i - 1] == 0)
            --tmp.length;
        else
            break;
    }

    if (tmp.length == 0) {
        tmp.sign = true;
        tmp.length = 1;
    }

    return tmp;
}

BigInt& BigInt::operator=(const BigInt& other) {
    sign = other.sign;
    length = other.length;
    if (vector)
        delete[] vector;
    vector = new uint32_t[length];

    for (size_t i = 0; i < length; ++i)
        vector[i] = other.vector[i];

    return *this;
}

BigInt& BigInt::operator=(BigInt&& other) {
    sign = other.sign;
    length = other.length;
    if (vector)
        delete[] vector;
    vector = other.vector;
    other.vector = nullptr;

    return *this;
}

BigInt BigInt::operator-() {
    BigInt tmp(*this);
    if (tmp != 0)
        tmp.sign = !tmp.sign;
    return tmp;
}

bool BigInt::operator==(const BigInt& other) const {
    if ((sign != other.sign) || (length != other.length))
        return false;

    for (size_t i = 0; i < length; ++i) {
        if (vector[i] != other.vector[i])
            return false;
    }

    return true;
}

bool BigInt::operator!=(const BigInt& other) const {
    return !((*this) == other);
}

bool BigInt::operator<(const BigInt& other) const {
    if (sign && (!other.sign))
        return false;
    else if ((!sign) && other.sign)
        return true;

    if (length < other.length)
        return sign;
    else if (length > other.length)
        return !sign;

    for (size_t i = 0; i < length; ++i) {
        if (vector[length - i - 1] > other.vector[length - i - 1])
            return !sign;
        if (vector[length - i - 1] < other.vector[length - i - 1])
            return sign;
    }
    return false;
}

bool BigInt::operator>(const BigInt& other) const {
    if (sign && (!other.sign))
        return true;
    else if ((!sign) && other.sign)
        return false;

    if (length < other.length)
        return !sign;
    else if (length > other.length)
        return sign;

    for (size_t i = 0; i < length; ++i) {
        if (vector[length - i - 1] > other.vector[length - i - 1])
            return sign;
        if (vector[length - i - 1] < other.vector[length - i - 1])
            return !sign;
    }
    return false;
}

bool BigInt::operator<=(const BigInt& other) const {
    return !((*this) > other);
}

bool BigInt::operator>=(const BigInt& other) const {
    return !((*this) < other);
}

std::ostream& operator<<(std::ostream& out, const BigInt& num) {
    if (!num.sign)
        out << "-";

    std::ostringstream os;

    for (size_t i = 0; i < num.length; ++i) {
        os << num.vector[num.length - i - 1];
        if (i != 0) {
            for (size_t j = 0; j < (9 - os.str().length()); ++j)
                out << '0';
        }

        out << os.str();
        os.str("");
    }
    return out;
}

BigInt::~BigInt() {
    if (vector)
        delete[] vector;
}

void BigInt::read_num(const std::string&& num) {
    std::string::const_iterator it = num.end() - 1;
    size_t chunks_count = INIT_CHUNK_COUNT;
    vector = new uint32_t[chunks_count];
    length = 0;
    size_t chunk = 0;
    size_t mul = 1;

    for ( ; it >= num.begin(); --it) {
        if (!isdigit(*it)) {
            if ((it != num.begin()) || (*it != '-')) {
                delete[] vector;
                throw "Wrong Number!";
            }
            break;
        }

        chunk = (*it - '0') * mul + chunk;
        mul *= 10;
        if (mul == MAX_SIZE) {
            if (length == chunks_count) {
                uint32_t* tmp = vector;
                vector = new uint32_t[chunks_count + INIT_CHUNK_COUNT];
                for (size_t i = 0; i < chunks_count; ++i)
                    vector[i] = tmp[i];
                delete[] tmp;
                chunks_count += INIT_CHUNK_COUNT;
            }

            vector[length] = (uint32_t)chunk;

            ++length;
            chunk = 0;
            mul = 1;
        }
    }

    if ((chunk) || (!length)) {
        uint32_t* tmp = vector;
        vector = new uint32_t[length + 1];
        for (size_t i = 0; i < length; ++i)
            vector[i] = tmp[i];
        delete[] tmp;

        vector[length] = (uint32_t)chunk;
        ++length;
    }
}

BigInt BigInt::sum(const BigInt& first, const BigInt& second) const {
    BigInt tmp;
    tmp.length = first.length;
    delete[] tmp.vector;
    tmp.vector = new uint32_t[tmp.length + 1];
    tmp.sign = first.sign;
    int64_t add = 0;

    for (size_t i = 0; i < second.length; ++i) {
        add += first.vector[i] + second.vector[i];
        if (add >= (int64_t)MAX_SIZE) {
            tmp.vector[i] = add % MAX_SIZE;
            add /= MAX_SIZE;
        } else {
            tmp.vector[i] = add;
            add = 0;
        }
    }

    for (size_t i = second.length; i < first.length; ++i) {
        add += first.vector[i];
        if (add >= (int64_t)MAX_SIZE) {
            tmp.vector[i] = add % MAX_SIZE;
            add /= MAX_SIZE;
        } else {
            tmp.vector[i] = add;
            add = 0;
        }
    }

    tmp.vector[tmp.length] = (uint32_t)add;
    if (add != 0)
        ++tmp.length;

    return tmp;
}

BigInt BigInt::dif(const BigInt& first, const BigInt& second) const {
    BigInt tmp;
    tmp.length = first.length;
    delete[] tmp.vector;
    tmp.vector = new uint32_t[tmp.length];
    tmp.sign = first.sign;
    int32_t add = 0;

    for (size_t i = 0; i < second.length; ++i) {
        add = first.vector[i] - second.vector[i] - (int32_t)(add < 0);
        if (add < 0) {
            tmp.vector[i] = add + MAX_SIZE;
        } else {
            tmp.vector[i] = add;
        }
    }

    for (size_t i = second.length; i < first.length; ++i) {
        add = first.vector[i] - (int32_t)(add < 0);
        if (add < 0) {
            tmp.vector[i] = add + MAX_SIZE;
        } else {
            tmp.vector[i] = add;
        }
    }

    for (size_t i = 0; i < first.length; ++i) {
        if (tmp.vector[first.length - i - 1] == 0)
            --tmp.length;
        else
            break;
    }

    if (tmp.length == 0) {
        tmp.sign = true;
        tmp.length = 1;
    }
    return tmp;
}
