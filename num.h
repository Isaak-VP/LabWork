#ifndef NUM_H
#define NUM_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class num {
public:
    std::string n;                  
    std::vector<int> number;        
    bool isNegative = false;        

    num();
    num(const std::string& numStr);

    num operator+(const num& other) const;
    num operator-(const num& other) const;
    num operator*(const num& other) const;
    num operator/(const num& other) const;

    num& operator=(const num& other);

    friend std::ostream& operator<<(std::ostream& os, const num& obj);

    bool operator<(const num& other) const;
    bool operator>(const num& other) const;
    bool operator<=(const num& other) const;
    bool operator>=(const num& other) const;
    bool operator==(const num& other) const;
    bool operator!=(const num& other) const;

private:
    std::vector<int> addVectors(const std::vector<int>& v1, const std::vector<int>& v2) const;
    std::vector<int> subtractVectors(const std::vector<int>& v1, const std::vector<int>& v2) const;
    std::vector<int> multiplyVectors(const std::vector<int>& v1, const std::vector<int>& v2) const;
    std::vector<int> divideVectors(const std::vector<int>& num1, const std::vector<int>& num2) const;
    int compareAbs(const std::vector<int>& v1, const std::vector<int>& v2) const;
};

#endif