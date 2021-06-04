#include <iostream>
//#include "Matrix.h"
using namespace std;

class M_Exception : public exception
{
    public:
    string error;
    M_Exception(string name)
    {
        error = name;
    }

    const char* what() const noexcept override
    {
        return error.c_str();
    }
};


int test(int a)
{
    try{
        if(a == 1)
        throw M_Exception("Error");
    }catch(M_Exception e){
        cout << e.error;
    }

    return a+1;
}

int main() 
{
    int a = 1;
    a = test(a);
    cout << a << endl;
    

    return 0;
}
