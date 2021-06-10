//
// Created by 11383 on 2021/5/13.
//

#ifndef CPP_PROJECT_MATRIX_H
#define CPP_PROJECT_MATRIX_H

#include <bits/stdc++.h>
#include <ostream>
#include <complex>

using namespace std;
template<typename T>
class Matrix{
private:
    int row,col;
    vector<vector<T>> mat;
public:
    explicit Matrix<T>(const vector<vector<T>> & mat);
    explicit Matrix<T>(int row,int col);

    bool change_item_by_index(int row_index,int col_index,T value);
    T dot(const Matrix<T> & m);
    T dot(const vector<T> & m);
    vector<T> cross(const vector<T> & m);
    Matrix<T> cross(const Matrix<T> & m);
    vector<T> v_mul(const vector<T> & v);
    Matrix<T> mul(const Matrix<T> & m);
    Matrix<T> Tr();
    Matrix<T> conjgg();

    Matrix<T> operator+(const Matrix<T> & m);
    Matrix<T> operator-(const Matrix<T> & m);
    Matrix<T> operator*(Matrix<T> & m);
    Matrix<T> operator/(const T & v);
    
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
    
    friend Matrix<T> operator*(const Matrix<T> & m, const T v)
    {
        Matrix<T> total(m.row,m.col);
        if(v == 0)
            return total;
        for(int i = 0; i < m.row; i++)
            for(int j = 0; j < m.col; j++)
                total[i][j] = m.mat[i][j] * v;
        return total;
    }

    friend Matrix<T> operator*(const T v, const Matrix<T> & m)
    {
        Matrix<T> total(m.row,m.col);
        if(v == 0)
            return total;
        for(int i = 0; i < m.row; i++)
            for(int j = 0; j < m.col; j++)
                total[i][j] = m.mat[i][j] * v;
        return total;
    }

    T det();
    vector<T> &operator[](int index);

};

//If the input matrix is not compared according to the matrix design, use this exception
//add exception message in the ()
//e.g. throw Matrix_notCompare_Exception("Matrix not compared")
class Matrix_notCompare_Exception : public exception
{
    public:
    string error;
    Matrix_notCompare_Exception(string e) {error = e;}
    const char* what() {return error.c_str();}
};

//When divide a zero, it may cost problem, We give a exception to call for zero exception.
class Divide_zero_Exception : public exception
{
    public:
    string error;
    Divide_zero_Exception(string e) {error = e;}
    const char* what() {return error.c_str();}
};

//elegant check if the matrix is a type of complex or a real.
template<typename U, typename = void>
struct is_complex_imp : false_type {};

template<typename U>
struct is_complex_imp<std::complex<U>> : true_type {};

template<typename U>
constexpr bool is_complex() { return is_complex_imp<U>(); }

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

//vector dot
template<typename T>
T Matrix<T>::dot(const Matrix<T> & m)
{
    if(this->row == 1 && m.row == 1 && this->col == m.col)
    {
        T result;
        for(int i = 0; i < col; i++)
            result += this->mat[0][i] * m.mat[0][i];
        return result;
    }
    else
        throw Matrix_notCompare_Exception("It is not vector, no dot product.");
}

//vector dot
template<typename T>
T Matrix<T>::dot(const vector<T> & m)
{
    if(this->row == 1 && m.size() == this->col)
    {
        T result = 0;
        for(int i = 0; i < col; i++)
            result += this->mat[0][i] * m[i];

            
        return result;
    }
    else
        throw Matrix_notCompare_Exception("It is not vector, no dot product.");
}

//vecotor cross
template<typename T>
Matrix<T> Matrix<T>::cross(const Matrix<T> & m)
{
    if(m.row == 1 && m.col == 3 && this->row == 1 && this->col == 3 ) 
    {
        Matrix<T> cross_result(1,3);
        cross_result->mat[0][0] = this->mat[0][1]*m.mat[1][2]-this->mat[0][2]*m.mat[1][1];
        cross_result->mat[0][1] = this->mat[0][2]*m.mat[1][0]-this->mat[0][0]*m.mat[1][2];
        cross_result->mat[0][2] = this->mat[0][0]*m.mat[1][1]-this->mat[0][1]*m.mat[1][0];
        return cross_result;
    } 
    else 
        throw Matrix_notCompare_Exception("We only support a matrix with one row of three column and a vector with 3 vcalue's cross product.");

}

//vector cross
template<typename T>
vector<T> Matrix<T>::cross(const vector<T> & m)
{
    if( m.size() == 3 && this->row == 1 && this->col == 3 ) 
    {
        vector<T> cross_result;
        cross_result.push_back(this->mat[0][1]*m[2]-this->mat[0][2]*m[1]);
        cross_result.push_back(this->mat[0][2]*m[0]-this->mat[0][0]*m[2]);
        cross_result.push_back(this->mat[0][0]*m[1]-this->mat[0][1]*m[0]);
        return cross_result;
    } 
    else 
        throw Matrix_notCompare_Exception("We only support a matrix with one row of three column and a vector with 3 vcalue's cross product.");

}

//matrix-vector multiplication
template<typename T>
vector<T> Matrix<T>::v_mul(const vector<T> & v)
{
    if ( col == v.size()) {
        vector<T> result;
        for(int i = 0; i < col; i++)
        {
            T middle;
            for(int j = 0; j < row; j++)
                middle += mat[i][j] * v[i];
            result.push_back(middle);
        }
        return result;                    
    } else 
        throw Matrix_notCompare_Exception("the col of the matrix and the size of v not compared.");

}

//Matrix conjugation
template<typename T>
Matrix<T> Matrix<T>::conjgg()
{
    if constexpr(is_complex<T>()) 
    {
        Matrix<T> cg_m(col,row);
        for(int i = 0; i < col; i++)
            for(int j = 0; j < row; j++)
                cg_m[i][j] = conj(mat[j][i]);
        return cg_m; 
    }
    else 
        return this->Tr();
     
}

//element-wise multiplication
template<typename T>
Matrix<T> Matrix<T>::mul(const Matrix<T> & m)
{
    if(this->row == m.row && this->col == m.col)
    {
        Matrix<T> total(row,col);
        for(int i = 0; i < this->row; i++)
            for(int j = 0; j < this->col; j++)
                total.mat[i][j] = this->mat[i][j] * m.mat[i][j];
        return total;
    }
    else
        throw Matrix_notCompare_Exception("Matrix not compared, you should give two matrix with the same col and row");
}

//Transposition matrix
template<typename T>
Matrix<T> Matrix<T>::Tr()
{
    Matrix<T> tr_m(col,row);
    for(int i = 0; i < col; i++)
        for(int j = 0; j < row; j++) 
            tr_m.mat[i][j] = mat[j][i];
    return tr_m;
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

//matrix add
template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & m) 
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
        throw Matrix_notCompare_Exception("matrix not compared, you should give two matrix with the same col and row");
}

//matrix minus
template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> & m) 
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
        throw Matrix_notCompare_Exception("matrix not compared, you should give two matrix with the same col and row");
}

//matrix multiply
template<typename T>
Matrix<T> Matrix<T>::operator*(Matrix<T> & m)
{

    if(this->col == m.row)
    {
        Matrix<T> total(this->row,m.col);
        for(int k = 0; k < m.row; k++)
            for(int i = 0; i < this->row; i++)
            {
                int r = this->mat[i][k];
                for(int j = 0; j < m.col; j++)
                    total[i][j] += m[k][j] * r;
            }   
        return total;
    }
    else
        throw Matrix_notCompare_Exception("the column of first matrix not same with the row of the second matrix");

}

//scalar divide
template<typename T>
Matrix<T> Matrix<T>::operator/(const T & v)
{
    if(v != 0)
    {
        Matrix<T> total(row,col);
        for(int i = 0; i < this->row; i++)
            for(int j = 0; j < this->col; j++)
                total.mat[i][j] = this->mat[i][j]/v;
        return total;    
    }
    else
        throw Divide_zero_Exception("You can't divide zero");
    
}


#endif //CPP_PROJECT_MATRIX_H
