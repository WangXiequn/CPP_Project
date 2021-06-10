#include <bits/stdc++.h>
#include <opencv4/opencv2/opencv.hpp>
#include "Matrix.h"
using namespace std;
int main(){
    Matrix<int> m(4,4);
    Matrix<int> n(4,4);
    Matrix<complex<float>> m1(4,4);
    int k = 1;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            m[i][j] = k++;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            n[i][j] = i+j;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            m1[i][j] = complex<float>(i,j);

    vector<int> u;
    Matrix<int> m2(1,3);
    for(int i = 0; i < 3; i++)
        u.push_back(3-i);
    for(int i = 0; i < 3; i++)
        m2[0][i] = i+1;
    vector<int> v = m2.cross(u);
    //vector<int> v2 = m2*u;
    cout << n << endl;
    cout << m << endl;
    cout << m+n << endl;
    cout << n-m << endl;
    cout << m*n << endl;
    cout << n.mul(m) << endl;
    cout << n/1 << endl;   
    cout << m * 3 << endl;
    cout << 3 * m << endl;
    cout << m2 << endl;
    
    cout << m2.dot(u) << endl;
    //cout << m2.v_mul(u) << endl;
    for(int i = 0; i < 3; i++)
        cout << v[i] << " ";
    cout << endl;
    for(int i = 0; i < 1; i++)
        cout << v2[i] << " ";
    cout << endl;
    cout << m.Tr() << endl;
    cout << m1.conjgg() << endl;

}