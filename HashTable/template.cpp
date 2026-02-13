#include "HashTable.h"
#include <cassert>
#include <iostream>

using std::cout;
using std::cin;
using std::ws;

HashTable<int, int> tables[1000];

int main() {
    int count;
    cin >> count;

    for (int i = 0; i < count; ++i) {
        int instance;
        cin >> instance;
        --instance;

        cin >> ws;
        char op;
        cin >> op;

        if (op == 'a') {
            int other;
            cin >> other;
            --other;
            tables[instance] = tables[other];
        }
        else if (op == 'i') {
            int key, value;
            cin >> key >> value;
            tables[instance].insert(key, value);
        }
        else if (op == 'e') {
            int key;
            cin >> key;
            tables[instance].erase(key);
        }
        else if (op == 'g') {
            int key;
            cin >> key;
            int *result = tables[instance].find(key);
            if (result != nullptr) {
                cout << *result << '\n';
            }
            else {
                cout << '-' << '\n';
            }
        }
        else if (op == 's') {
            int key, value;
            cin >> key >> value;
            tables[instance][key] = value;
        }
        else if (op == 'z') {
            cout << tables[instance].size() << '\n';
        }
    }
}