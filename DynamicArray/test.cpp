#include <cassert>
#include <iostream>

using std::cout;
using std::cin;
using std::ws;

int* operation(){
    int array_1[9];

    return array_1;
}

int main(){
    int *ip = operation();

    for(int i = 0; i < 10; i++){
        cout << ip[i] << ", ";
    }
}