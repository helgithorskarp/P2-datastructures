#include "heap.h"
#include <cassert>
#include <iostream>

using std::cout;
using std::cin;
using std::ws;


Heap<int> my_heaps[1000];
int main() {
    int q;
    cin >> q;

    for (int i = 0; i < q; i++) {
        int instance;
        cin >> instance;

        instance--;

        cin >> ws;
        char op;
        cin >> op;

        if (op == 'a') {
            int other;
            cin >> other;
            other--;
            my_heaps[instance] = my_heaps[other];
        }
        else if (op == '+') {
            int value;
            cin >> value;
            my_heaps[instance].Push(value);
        }
        else if (op == '-') {
            my_heaps[instance].Pop();
        }
        else if (op == 'p') {
            cout << my_heaps[instance].Peek();
            cout << "\n";
        }
        else if (op == 's') {
            cout << my_heaps[instance].size();
            cout << "\n";
        }
        else {
            //
        }

    

    }
}