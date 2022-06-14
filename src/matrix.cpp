#include <matrix.hpp>
#include <vector>

/* Matrixクラス */
Matrix::Matrix(const vector<vector<double>>& v)
    : row(v.size()), column(v.front().size()), v(v)
{
}

Matrix::Matrix(int row, int column)
    : row(row),
      column(column),
      v(vector<vector<double>>(row, vector<double>(column)))
{
}

Matrix Matrix::operator*(const Matrix& mat) const
{
    Matrix ret(row, mat.column);
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < mat.column; j++) {
            ret[i][j] = 0.0;
            for(int k = 0; k < column; k++) {
                ret[i][j] += v[i][k] * mat[k][j];
            }
        }
    }
    return ret;
}

void Matrix::identity()
{
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < column; j++) {
            (*this)[i][j] = 0.0;
        }
        (*this)[i][i] = 1.0;
    }
}

const vector<double>& Matrix::operator[](int x) const { return v[x]; }
vector<double>& Matrix::operator[](int x) { return v[x]; }
