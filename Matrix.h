//
// Created by 11383 on 2021/5/13.
//

#ifndef CPP_PROJECT_MATRIX_H
#define CPP_PROJECT_MATRIX_H

#include <bits/stdc++.h>
#include <ostream>


using namespace std;
template<typename T>
class Matrix{
private:
    int row,col;
    vector<vector<T>> mat;
public:
    explicit Matrix<T>(const vector<vector< T>> & mat);
    explicit Matrix<T>(int row,int col);

    bool change_item_by_index(int row_index,int col_index,T value);
    
    Matrix<T> operator+(const Matrix<T> & m);
    Matrix<T> operator-(const Matrix<T> & m);
    Matrix<T> operator*(const Matrix<T> & m);
    friend ostream &operator<<(ostream &os, const Matrix<T> &matrix){
        for (int i = 0; i < matrix.row; ++i) {
            os<<"[";
            for (int j = 0; j < matrix.col; ++j) {
                os<<matrix.mat[i][j];
                if (j==matrix.col-1){
                    os<<"]";
                } else{
                    os<<",";
                }
            }
            os<<endl;
        }
        return os;
    }
    T det();
    vector<T> &operator[](int index);

};

class Matrix_notCompare_Exception : public exception
{
    public:
    string error;
    Matrix_notCompare_Exception(string e) {error = e;}
    const char* what() const {return error.c_str();}

};

template<typename T>
Matrix<T>::Matrix(int row, int col) {
    this->row = row;
    this->col = col;
    vector<vector<T>> s;
    this->mat = s;
    for (int i = 0; i < row; ++i) {
        vector<T> temp;
        this->mat.push_back(temp);
        for (int j = 0; j < col; ++j) {
            this->mat[i].push_back(static_cast<T>(0));
        }
    }
}

template<typename T>
Matrix<T>::Matrix(const vector <vector<T>> &mat) {
    this->row = mat.size();
    int max = 0;
    for (vector<T> s:mat) {
        if (max<s.size()){
            max = s.size();
        }
    }
    vector<vector<T>> s;
    this->mat = s;
    for (int i = 0; i < mat.size(); ++i) {
        vector<T> temp;
        this->mat.push_back(temp);
        for (int j = 0; j < s[i].size(); ++j) {
            this->mat[i].push_back(mat[i][j]);
        }
        for (int j = s[i].size(); j <max ; ++j) {
            this->mat.push_back(static_cast<T>(0));
        }
    }
}

template<typename T>
bool Matrix<T>::change_item_by_index(int row_index, int col_index, T value) {
    if (row_index>this->row||col_index>this->col||row_index<1||col_index<1){
        return false;
    }
    this->mat[row_index-1][col_index-1] = value;
    return true;
}

template<typename T>
T Matrix<T>::det() {
    return nullptr;
}
/*
 * 越界报错未添加
 */
template<typename T>
vector<T> & Matrix<T>::operator[](int index) {
    return mat[index];
}

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
            throw Matrix_notCompare_Exception("Matrix not compared.");
        }
    catch(Matrix_notCompare_Exception e)
    {
        cout << e.error << endl;
    }
      
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> & m) 
{
    try
    {
        if(this->row == m.row && this->col == m.col)
        {
            Matrix<T> total(row,col);
            for(int i = 0; i < this->row; i++)
                for(int j = 0; j < this->col; j++)
                    total.mat[i][j] = this->mat[i][j] - m.mat[i][j];
            return total;
        }
        else
            throw Matrix_notCompare_Exception("Matrix not compared.");
        }
    catch(Matrix_notCompare_Exception e)
    {
        cout << e.error << endl;
    }
      
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> & m)
{
    try{
        if(this->col == m.row)
        {
            Matrix<T> total(this->row,m.col);
            for(int k = 0; k < m.row; k++)
                for(int i = 0; i < this->row; i++)
                {
                    int r = this->mat[i][k];
                    for(int j = 0; j < m.col; j++)
                        total[i][j] += r * m[k][j];
                }   
            return total;
        }
        else{
            throw Matrix_notCompare_Exception("The column of first matrix not same with the row of the second matrix.");
        }
    }catch(exception e){
        cout << e.error << endl;
    }

}


#endif //CPP_PROJECT_MATRIX_H
