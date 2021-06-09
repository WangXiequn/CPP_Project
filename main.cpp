#include <bits/stdc++.h>
#include "Matrix.h"
using namespace std;
int main(){
    Matrix<int> m(4,4);
    Matrix<int> n(4,4);
    int k = 1;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            m[i][j] = k++;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            n[i][j] = i+j;
    cout << n << endl;
    cout << m << endl;
    cout << m+n << endl;
    cout << n-m << endl;
    cout << m*n << endl;
    cout << n.mul(m) << endl;
    cout << n/1 << endl;   
    cout << m.Tr() << endl;
}