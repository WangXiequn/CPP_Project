//
// Created by 11383 on 2021/5/13.
//

#ifndef CPP_PROJECT_MATRIX_H
#define CPP_PROJECT_MATRIX_H

#include <bits/stdc++.h>
using namespace std;
template<typename T>class Matrix{
private:
    int row,col;
    vector<vector<T>> mat;
public:
    explicit Matrix<T>(const vector<vector< T>> & mat);
    explicit Matrix<T>(int row,int col);
};




template<typename T>
Matrix<T>::Matrix(int row, int col) {
    this->row = row;
    this->col = col;
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
    vector<T> temp;
    this->mat = s;
    for (int i = 0; i < mat.size(); ++i) {
        this->mat.push_back(temp);
        for (int j = 0; j < s[i].size(); ++j) {
            this->mat[i].push_back(mat[i][j]);
        }
        for (int j = s[i].size(); j <max ; ++j) {
            this->mat.push_back(static_cast<T>(0));
        }
    }
}


#endif //CPP_PROJECT_MATRIX_H
