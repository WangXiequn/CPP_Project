//
// Created by 11383 on 2021/5/13.
//

#ifndef CPP_PROJECT_MATRIX_H
#define CPP_PROJECT_MATRIX_H

#include <bits/stdc++.h>
#include <ostream>
#define err 0.00001

using namespace std;
template<typename T>
class Matrix{
private:
    int row,col;
    vector<vector<T>> mat;
    vector<vector<complex<double>>> d_matrix;
    vector<vector<double>> eig_vectors;
    vector<complex<double>> eig_values;
    void reduce_to_hessenberg(vector<vector<double>> &h);
    void reduce_to_schur(vector<vector<double>> &h);
public:
    explicit Matrix<T>(const vector<vector< T>> & mat);
    explicit Matrix<T>(int row,int col);
    Matrix<T>();
    bool change_item_by_index(int row_index,int col_index,T value);
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
    bool isSquare();
    T trace();
    void gauss_elimination(vector<vector<T>> & m);
    Matrix<T> inverse();
    void reshape(int row_length,int col_length);
    Matrix<T> slicing(int up_row,int down_row,int left_col,int right_col);
    T max();
    T min();
    T sum();
    T avg();
    bool is_sym();
    void eig();

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
            this->mat[i].push_back(static_cast<T>(0));
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
    T answer;
    if (this->isSquare()){
        vector<vector<T>> tempMat(this->mat);
        gauss_elimination(tempMat);
        answer = tempMat[0][0];
        for (int i = 1; i < this->row; ++i) {
            answer*=tempMat[i][i];
        }
    }
    return answer;
}
/*
 * 越界报错未添加
 */
template<typename T>
vector<T> & Matrix<T>::operator[](int index) {
    return mat[index];
}

template<typename T>
bool Matrix<T>::isSquare() {
    return this->row==this->col;
}
/*
 * 未添加报错
 */
template<typename T>
T Matrix<T>::trace() {
    T answer;
    if (this->isSquare()){
        answer = this->mat[0][0];
        for (int i = 1; i < row; ++i) {
            answer+= this->mat[i][i];
        }
    }
    return answer;
}

template<typename T>
void Matrix<T>::gauss_elimination(vector<vector<T>> &m) {
    if (m.size()==m[0].size()){
        int length = m.size();
        bool flag = false;
        for (int i = 0; i < length; ++i) {
            if (m[i][i]==0){
                for (int k = i+1; k < length; ++k) {
                    if (m[i][i]!=0){
                        for (int l = 0; l < length; ++l) {
                            swap(m[i][l],m[k][l]);
                        }
                        break;
                    }
                    if (k==length-1){
                        flag= true;
                    }
                }
            }
            if (flag){
                continue;
            }
            for (int j = i+1; j < length; ++j) {

                T multiple = m[j][i]/m[i][i];
                for (int k = 0; k < length; ++k) {
                    m[j][k]-= multiple*m[i][k];
                }
            }
        }
    }
}

template<typename T>
Matrix<T>::Matrix() {
    this->mat= nullptr;
    this->row=0;
    this->col=0;
}

template<typename T>
Matrix<T> Matrix<T>::inverse() {
    int length = this->row;
    Matrix<T> answer(this->row,this->row);
    if (this->det()!=0) {
        Matrix<T> mat = *this;

        for (int i = 0; i < this->row; ++i) {
            answer[i][i] = 1;
        }
        for (int i = 0; i < length; ++i) {
            if (mat[i][i] == 0) {
                for (int k = i + 1; k < length; ++k) {
                    if (mat[i][i] != 0) {
                        for (int l = 0; l < length; ++l) {
                            swap(mat[i][l], mat[k][l]);
                            swap(answer[i][l], answer[k][l]);
                        }
                        break;
                    }
                }
            }

            for (int j = i + 1; j < length; ++j) {
                T multiple = mat[j][i] / mat[i][i];
                for (int k = 0; k < length; ++k) {
                    mat[j][k] -= multiple * mat[i][k];
                    answer[j][k] -= multiple * answer[i][k];
                }
            }
        }
        for (int i = length-1; i >=1 ; --i) {
            for (int j = i-1; j >=0 ; --j) {
                T multiple = mat[j][i]/mat[i][i];
                for (int k = 0; k < length; ++k) {
                    mat[j][k] -= multiple * mat[i][k];
                    answer[j][k] -= multiple * answer[i][k];
                }
            }
        }
        for (int i = 0; i < length; ++i) {
            T multiple = 1/mat[i][i];
            for (int j = 0; j < length; ++j) {
                answer[i][j]*=multiple;
            }
        }

    }
    return answer;
    }

template<typename T>
void Matrix<T>::reshape(int row_length, int col_length) {
    vector<vector<T>> reshape_matrix;

    for (int i = 0; i < row_length; ++i) {
        vector<T> col;
        reshape_matrix.push_back(col);
        for (int j = 0; j < col_length; ++j) {
            reshape_matrix[i].push_back(static_cast<T>(0));
        }
    }

    for (int i = 0; i < this->row*this->col; ++i) {
        if (i==row_length*col_length){
            break;
        }
        reshape_matrix[i/col_length][i-(i/col_length)*col_length] = this->mat[i/this->col][i-(i/this->col)*this->col];
    }
    this->row=row_length;
    this->col=col_length;
    this->mat=reshape_matrix;
}

template<typename T>
Matrix<T> Matrix<T>::slicing(int up_row, int down_row, int left_col, int right_col) {
    Matrix<T> answer(down_row-up_row,right_col-left_col);
    for (int i = up_row-1; i <down_row ; ++i) {
        for (int j = left_col-1; j <right_col ; ++j) {
            answer[i-up_row+1][j-left_col+1]= this->mat[i][j];
        }
    }
    return answer;
}

template<typename T>
T Matrix<T>::max() {
    T max = this->mat[0][0];
    for (int i = 0; i < this->row; ++i) {
        for (int j = 0; j < this->col; ++j) {
            if (max<this->mat[i][j]){
                max=this->mat[i][j];
            }
        }
    }
    return max;
}

template<typename T>
T Matrix<T>::min() {
    T min = this->mat[0][0];
    for (int i = 0; i < this->row; ++i) {
        for (int j = 0; j < this->col; ++j) {
            if (min>this->mat[i][j]){
                min=this->mat[i][j];
            }
        }
    }
    return min;
}

template<typename T>
T Matrix<T>::sum() {
    T sum = static_cast<T>(0);
    for (int i = 0; i < this->row; ++i) {
        for (int j = 0; j < this->col; ++j) {
            sum+=this->mat[i][j];
        }
    }
}
/*
 * 除零
 */
template<typename T>
T Matrix<T>::avg() {
    return sum()/(this->row* this->col);
}



template<typename T>
bool Matrix<T>::is_sym() {
    if (this->row!=this->col){
        return false;
    }
    for (int i = 0; i < this->row; ++i) {
        for (int j = 0; j <i; ++j) {
            if (this->mat[i][j]!=this->mat[j][i]){
                return false;
            }
        }
        return true;
    }
}

template<typename T>
void Matrix<T>::eig() {

    if (isSquare()){
        vector<vector<double>> hess;
        vector<double> temp_double;
        for (int i = 0; i < this->row; ++i) {
            eig_vectors.push_back(temp_double);
            hess.push_back(temp_double);
            eig_values.template emplace_back(0);
            for (int j = 0; j < this->row; ++j) {
                eig_vectors[i].push_back(0);
                double d =this->mat[i][j];
                hess[i].push_back(d);
            }

        }
        for (int i = 0; i < this->row; ++i) {
            for (int j = 0; j < this->col; ++j) {
                eig_vectors[i][j] = (i==j)?1:0;
            }
        }
        reduce_to_hessenberg(hess);
        reduce_to_schur(hess);
    }
}

template<typename T>
void Matrix<T>::reduce_to_hessenberg(vector<vector<double>> &h) {
    vector<double> temp;
    for (int i = 0; i < this->row; ++i) {
        temp.push_back(0);
    }
    for (int i = 1; i < this->row-1; ++i) {
        double s = 0;
        for (int j = i; j < this->row; ++j) {
            s+= abs(h[j][i-1]);
        }
        if (s>err){
            double hs = 0;
            for (int j = this->row-1; j >=i ; --j) {
                double s = h[j][i-1]/s;
                temp[j] = s;
                hs+=temp[j]*temp[j];
            }
            double a = sqrt(hs);
           a = temp[i]>0?-a:a;
           hs -=temp[i]*a;
           temp[i] -= a;
            for (int j = i; j < this->row; ++j) {
                double hss = 0;
                for (int k = this->row-1; k >=i ; --k) {
                    hss+=temp[k]*h[k][j];
                }
                hss/=hs;
                for (int k = i; k <this->row ; ++k) {
                    h[k][j] -= hss*temp[k];
                }
            }
            for (int j = 0; j < this->row; ++j) {
                double hss = 0;
                for (int k = this->row-1; k >=i; --k) {
                    hss+=temp[k]*h[j][k];
                }
                hss/=hs;
                for (int k = i; k <this->row ; ++k) {
                    h[j][k] -= hss*temp[k];
                }
            }
            temp[i] = s*temp[i];
            h[i][i-1] = s*a;
        }

    }
    for (int i = this->row-2; i <1 ; --i) {
        if (abs(h[i][i-1])>err){
            for (int j = i+1; j <this->row ; ++j) {
                temp[j] = h[j][i-1];
            }
            for (int j = i; j < this->row ; ++j) {
                double d  = 0;
                for (int k = i; k <this->row ; ++k) {
                    d+=temp[k]*eig_vectors[k][j];
                }
                d/=temp[i];
                d/=h[i][i-1];
                for (int k = i; k <this->row ; ++k) {
                    eig_vectors[k][j] +=d*temp[k];
                }
            }
        }
    }

}
template<typename T>
void Matrix<T>::reduce_to_schur(vector<vector<double>> &h){

}

#endif //CPP_PROJECT_MATRIX_H
