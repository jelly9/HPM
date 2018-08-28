/**
  * @file itypetraits.c
  * @author xiaoguodong jellyxio@qq.com
  * @date 2018-08-28
  * @brief
  *
  **/


#include <iostream>
#include "itypetraits.h"

using namespace std;

struct A{
    int i;
};

int main(){
    
    if ( TypeTraits<int>::IsPODType() ) {
        cout << "is POD type" << endl; //
    } else {
        cout << "not POD type" << endl;
    }
 
    if ( TypeTraits<A>::IsPODType() ) {
        cout << "is POD type" << endl;
    } else {
        cout << "not POD type" << endl; //
    }
    
    return 0;
}
