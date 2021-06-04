#include <iostream>
#include "Matrix.h"
int main() {
    Matrix<int> mat(3,2);
    mat.change_item_by_index(1,2,4);
    mat.change_item_by_index(2,2,6);
    std::cout<<mat;
    return 0;
}
