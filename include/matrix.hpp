#pragma once

#include <vector>

using namespace std;

class Matrix
{
private:
    int row;
    int column;
    vector<vector<double>> v;

public:
    Matrix(const vector<vector<double>>& v);
    Matrix(int row, int column);
    Matrix operator*(const Matrix& mat) const;
    const vector<double>& operator[](int x) const;
    vector<double>& operator[](int x);
    void identity();
};