#pragma once
#include <vector>

using namespace std;

class Matrix {
    /* 行列のクラス */
private:
    // 行列のサイズ
    int row;
    int column;

protected:
    // 行列本体
    vector<vector<double>> v;

public:
    Matrix(const vector<vector<double>> &v);
    Matrix(int row, int column);
    Matrix operator*(const Matrix &mat) const;
    const vector<double> &operator[](int x) const;
    vector<double> &operator[](int x);
    void identity();
    void zeros();
};