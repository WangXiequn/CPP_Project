//
// Created by 11383 on 2021/5/13.
//

#ifndef CPP_PROJECT_MATRIX_H
#define CPP_PROJECT_MATRIX_H

#include <bits/stdc++.h>
using namespace std;
template<typename T>
class Matrix{
private:
    int row,col;
    vector<vector<T>> mat;
public:
    explicit Matrix<T>(const vector<vector< T>>& mat);
    explicit Matrix<T>(int row,int col);

    Matrix<T> operator+(const Matrix<T> & m);
};

class Matrix_notCompare_Exception : public exception
{
    public:
    string error;
    Matrix_notCompare_Exception(string e) {error = e;}
    const char* what() const {return error.c_str();}

};

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & m) 
{
    try
    {
        if(this->row == m.row && this->col == m.col)
        {
            Matrix<T> total(row,col);
            for(int i = 0; i < this->row; i++)
                for(int j = 0; j < this->col; j++)
                    total.mat[i][j] = this->mat[i][j] + m.mat[i][j];
            return total;
        }
        else
            throw "Error";
        }
    catch()
    {
        
    }

        
}


#endif //CPP_PROJECT_MATRIX_H
