#ifndef MATX_H
#define MATX_H

#include <vector>
#include "num.h"
#include <string>

class matx {
public:
    std::vector<std::vector<num>> matrix;

    matx();
    matx(int rows, int cols);

    matx operator+(const matx& other) const;
    matx operator-(const matx& other) const;
    matx operator*(const matx& other) const;
    matx operator/(const matx& other) const;
    
    matx& operator=(const matx& other);
    
    bool operator==(const matx& other) const;
    bool operator!=(const matx& other) const;
    bool operator<(const matx& other) const;
    bool operator<=(const matx& other) const;
    bool operator>(const matx& other) const;
    bool operator>=(const matx& other) const;

    friend std::ostream& operator<<(std::ostream& os, const matx& mtx);

private:
    void checkSize(const matx& other) const;
};

#endif
