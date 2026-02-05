#include <cassert>
#include <iostream>
#include "DynamicArray.h"

using std::cout;
using std::cin;
using std::ws;

DynamicArray<int> vecs[1000];

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
            vecs[instance] = DynamicArray<int>(vecs[other]); 
        }
        else if (op == '+') {
            int value;
            cin >> value;
            vecs[instance].push_back(value);
        }
        else if (op == '-') {
            vecs[instance].pop_back();
        }
        else if (op == 'i') {
            int index, value;
            cin >> index >> value;
            vecs[instance].insert(index, value);
        }
        else if (op == 'e') {
            int index;
            cin >> index;
            vecs[instance].erase(index);
        }
        else if (op == 'g') {
            int index;
            cin >> index;
            cout << vecs[instance][index] << "\n";
        }
        else if (op == 's') {
            int index, value;
            cin >> index >> value;
            vecs[instance][index] = value;
        }
        else if (op == 'r') {
            int sz;
            cin >> sz;
            vecs[instance].resize(sz);
        }
        else if (op == 'p') {
            cout << vecs[instance].m_size << "\n";
            if (vecs[instance].m_size > 0) {
                for (int j = 0; j < vecs[instance].m_size; j++) {
                    if (j != 0) cout << " ";
                    cout << vecs[instance][j]; // print the vluae of instance index j
                }
                cout << "\n"; // new line
            }
        }
        else {
            assert(false);
        }
    }

    return 0;
}
