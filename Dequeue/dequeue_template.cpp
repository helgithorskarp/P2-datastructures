#include <cassert>
#include <iostream>
#include "dequeue.h"

using std::cout;
using std::cin;
using std::ws;

Deque<int> vecs[1000];

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
            vecs[instance] = Deque<int>(vecs[other]); 
        }
        else if (op == '+') {
            char subop;
            cin >> subop;
            if (subop == 'f') {
                int value;
                cin >> value;
                vecs[instance].push_front(value);
            }
            else if (subop == 'b') {
                int value;
                cin >> value;
                vecs[instance].push_back(value);
            }
            else {
                assert(false);
            }
        }
        else if (op == '-') {
            char subop;
            cin >> subop;
            if (subop == 'f') {
                vecs[instance].pop_front();
            }
            else if (subop == 'b') {
                vecs[instance].pop_back();
            }
            else {
                assert(false);
            }
        }
        else if (op == 'f'){
            if (vecs[instance].m_size > 0) {
                cout << vecs[instance].front() << "\n";
            }
        }
        else if (op == 'b'){
            if (vecs[instance].m_size > 0) {
                cout << vecs[instance].back() << "\n";
            }
        }
        else if (op == 's') {
            cout << vecs[instance].size() << "\n";
        }
        else {
            assert(false);
        }
    }

    return 0;
}