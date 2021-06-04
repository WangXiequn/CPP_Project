//
// Created by 11383 on 2021/5/13.
//

#ifndef CS205_PROJECT_MATRIX_H
#define CS205_PROJECT_MATRIX_H

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


template<typename T>
Matrix<T>::Matrix<T>(int row, int col) {

}

template<typename T>
Matrix<T>::Matrix<T>(const vector <vector<T>> &mat) {
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
        this->mat.push_back(vector<T>);
        for (int j = 0; j < s[i].size(); ++j) {
            this->mat[i].push_back(mat[i][j]);
        }
    }
}


#endif //CS205_PROJECT_MATRIX_H
