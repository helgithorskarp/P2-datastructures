#include "DynamicArray.h"


/// assumption, we can compare elements of item T (<, >, <=, >=)
template <typename T>
struct Heap {
    int m_size;
    DynamicArray<T> m_arr;

    Heap(): m_size(0) {
        m_arr.push_back(T()); /// first element ignored for convenience in heap
    }


    void floatUp() {
        // last inserted item bubbles up
        int item_idx = m_size;

        while (item_idx > 1) {
            int parent_idx = item_idx / 2;

            if (m_arr[item_idx] < m_arr[parent_idx]) {
                swap(parent_idx, item_idx);
                item_idx = parent_idx;      // move up to parent position
            } else {
                break;
            }
        }
    }


    void swap(int i, int j) {
        T temp = m_arr[i];
        m_arr[i] = m_arr[j];
        m_arr[j] = temp;
    }

        void swimDown() {
        int item_idx = 1;

        while (true) {
            int child1_idx = item_idx * 2;
            int child2_idx = item_idx * 2 + 1;

            // no left child
            if (child1_idx > m_size) break;

            // only left child
            if (child2_idx > m_size) {
                if (m_arr[child1_idx] < m_arr[item_idx]) {
                    swap(child1_idx, item_idx);
                }
                break;
            }

            T child1 = m_arr[child1_idx];
            T child2 = m_arr[child2_idx];
            T item   = m_arr[item_idx];

            if (child1 < item && child1 <= child2) {
                swap(child1_idx, item_idx);
                item_idx = child1_idx;
                continue;
            }

            if (child2 < item && child2 <= child1) {
                swap(child2_idx, item_idx);
                item_idx = child2_idx;
                continue;
            }

            break;
        }
    }

    void Push(T el) {
        m_arr.push_back(el);
        m_size++;
        floatUp();
    }

    T Pop() {
        if (m_size == 0) return T();
        T returnItem = m_arr[1];

        swap(1, m_size);
        m_arr.pop_back();   
        m_size--;

        if (m_size > 0) swimDown();
        return returnItem;
    }

    T Peek() {
        if (m_size == 0) return T(); /// heap is empty

        return m_arr[1];

    }

    Heap& operator=(const Heap& other) {
        if (this == &other) return *this;

        m_size = other.m_size;
        m_arr  = other.m_arr; 
        return *this;
    }

    int size() {
        return m_size;
    }


};