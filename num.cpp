#include "num.h"

num::num() {}

num::num(const std::string& numStr) {
    if (numStr[0] == '-') {
        isNegative = true;
        n = numStr.substr(1);
    } else {
        n = numStr;
    }

    for (char symbol : n) {
        if (isdigit(symbol)) {
            number.push_back(symbol - '0');
        }
    }

    while (number.size() > 1 && number[0] == 0) {
        number.erase(number.begin());
    }
}

num num::operator+(const num& other) const {
    num result;
    if (this->isNegative == other.isNegative) {
        result.number = addVectors(this->number, other.number);
        result.isNegative = this->isNegative;
    } else {
        if (compareAbs(this->number, other.number) >= 0) {
            result.number = subtractVectors(this->number, other.number);
            result.isNegative = this->isNegative;
        } else {
            result.number = subtractVectors(other.number, this->number);
            result.isNegative = other.isNegative;
        }
    }
    return result;
}

num num::operator-(const num& other) const {
    num result;
    if (this->isNegative != other.isNegative) {
        result.number = addVectors(this->number, other.number);
        result.isNegative = this->isNegative;
    } else {
        if (compareAbs(this->number, other.number) >= 0) {
            result.number = subtractVectors(this->number, other.number);
            result.isNegative = this->isNegative;
        } else {
            result.number = subtractVectors(other.number, this->number);
            result.isNegative = !this->isNegative;
        }
    }
    return result;
}

num num::operator*(const num& other) const {
    num result;
    result.number = multiplyVectors(this->number, other.number);
    result.isNegative = this->isNegative != other.isNegative;
    return result;
}

num num::operator/(const num& other) const {
    num result;
    result.number = divideVectors(this->number, other.number);
    result.isNegative = this->isNegative != other.isNegative;
    return result;
}

num& num::operator=(const num& other) {
    if (this == &other) return *this;
    this->n = other.n;
    this->number = other.number;
    this->isNegative = other.isNegative;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const num& obj) {
    if (obj.isNegative && !obj.number.empty()) {
        os << "-";
    }
    for (int digit : obj.number) {
        os << digit;
    }
    return os;
}

bool num::operator<(const num& other) const {
    if (this->isNegative != other.isNegative) {
        return this->isNegative;
    }
    if (this->isNegative) {
        return compareAbs(this->number, other.number) > 0;
    } else {
        return compareAbs(this->number, other.number) < 0;
    }
}

bool num::operator>(const num& other) const {
    return other < *this;
}

bool num::operator<=(const num& other) const {
    return !(other < *this);
}

bool num::operator>=(const num& other) const {
    return !(*this < other);
}

bool num::operator==(const num& other) const {
    return this->isNegative == other.isNegative && compareAbs(this->number, other.number) == 0;
}

bool num::operator!=(const num& other) const {
    return !(*this == other);
}

std::vector<int> num::addVectors(const std::vector<int>& v1, const std::vector<int>& v2) const {
    std::vector<int> result;
    int carry = 0;

    std::vector<int> num1 = v1;
    std::vector<int> num2 = v2;

    if (num1.size() < num2.size()) {
        num1.insert(num1.begin(), num2.size() - num1.size(), 0);
    } else if (num2.size() < num1.size()) {
        num2.insert(num2.begin(), num1.size() - num2.size(), 0);
    }

    for (int i = num1.size() - 1; i >= 0; --i) {
        int sum = num1[i] + num2[i] + carry;
        carry = sum / 10;
        result.insert(result.begin(), sum % 10);
    }

    if (carry > 0) {
        result.insert(result.begin(), carry);
    }

    return result;
}

std::vector<int> num::subtractVectors(const std::vector<int>& v1, const std::vector<int>& v2) const {
    std::vector<int> result;
    int borrow = 0;

    std::vector<int> num1 = v1;
    std::vector<int> num2 = v2;

    if (num1.size() < num2.size()) {
        num1.insert(num1.begin(), num2.size() - num1.size(), 0);
    } else if (num2.size() < num1.size()) {
        num2.insert(num2.begin(), num1.size() - num2.size(), 0);
    }

    for (int i = num1.size() - 1; i >= 0; --i) {
        int diff = num1[i] - num2[i] - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.insert(result.begin(), diff);
    }

    while (result.size() > 1 && result[0] == 0) {
        result.erase(result.begin());
    }

    return result;
}

std::vector<int> num::multiplyVectors(const std::vector<int>& v1, const std::vector<int>& v2) const {
    std::vector<int> result(v1.size() + v2.size(), 0);

    for (int i = v1.size() - 1; i >= 0; --i) {
        for (int j = v2.size() - 1; j >= 0; --j) {
            int mul = v1[i] * v2[j];
            int sum = result[i + j + 1] + mul;
            result[i + j + 1] = sum % 10;
            result[i + j] += sum / 10;
        }
    }

    while (result.size() > 1 && result[0] == 0) {
        result.erase(result.begin());
    }

    return result;
}

std::vector<int> num::divideVectors(const std::vector<int>& num1, const std::vector<int>& num2) const {
    std::vector<int> result;
    std::vector<int> current;

    for (int i = 0; i < num1.size(); ++i) {
        current.push_back(num1[i]);

        int count = 0;
        while (compareAbs(current, num2) >= 0) {
            current = subtractVectors(current, num2);
            ++count;
        }

        result.push_back(count);
    }

    while (result.size() > 1 && result[0] == 0) {
        result.erase(result.begin());
    }

    return result;
}

int num::compareAbs(const std::vector<int>& v1, const std::vector<int>& v2) const {
    if (v1.size() > v2.size()) return 1;
    if (v1.size() < v2.size()) return -1;
    for (size_t i = 0; i < v1.size(); ++i) {
        if (v1[i] > v2[i]) return 1;
        if (v1[i] < v2[i]) return -1;
    }
    return 0;
}
