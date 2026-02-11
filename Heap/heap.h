#include "DynamicArray.h"


/// assumption, we can compare elements of item T (<, >, <=, >=)
template <typename T>
struct Heap {
    int m_size;
    DynamicArray<T> m_arr;

    Heap(): m_size(0) {
        m_arr.push_back(T()); /// first element ignored for convenience in heap
    }

   /// O(n), deep copy of array
    Heap(const Heap& other)
        : m_size(other.m_size),
        m_arr(other.m_arr)   // calls DynamicArray copy constructor
    {}

    /// log(n), a heap is always perfectly balanced so in worst case leaf floating up can go log(n) steps
    /// where n is the amount of items in the heap
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

    /// O(1)
    void swap(int i, int j) {
        T temp = m_arr[i];
        m_arr[i] = m_arr[j];
        m_arr[j] = temp;
    }

    /// worst case is O(n), since heap is always perfectly balanced, a node swimming down can at most go down log(n) layers down
    /// where n is the amount of items in the heap
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
            
            /// if child 1 is smaller than item and also smaller than child 2 then we swap eith parent
            if (child1 < item && child1 <= child2) {
                swap(child1_idx, item_idx);
                item_idx = child1_idx; /// set parent to the child we swapped it with
                continue;
            }

            /// if child 2 is the smallest swap  with parent
            if (child2 < item && child2 <= child1) {
                swap(child2_idx, item_idx);
                item_idx = child2_idx;  /// set parent to the child we swapped it with
                continue;
            }

            break;
        }
    }

    /// Amortized O(log n): push_back is amortized O(1), floatUp is O(log n).
    /// Worst-case O(n) if push_back triggers a resize (copy).
    void Push(T el) {
        m_arr.push_back(el);
        m_size++;
        floatUp();
    }
    
    /// O(log n) wost case swim down operation is log n
    T Pop() {
        if (m_size == 0) return T();
        T returnItem = m_arr[1];

        swap(1, m_size); /// set the root to the end, and then remove the item from the back
        m_arr.pop_back();   
        m_size--;

        if (m_size > 0) swimDown();
        return returnItem;
    }

    /// O(1)
    T Peek() {
        if (m_size == 0) return T(); /// heap is empty

        return m_arr[1];

    }

    /// O(n) the assignment operation is implement in the dynamic array
    Heap& operator=(const Heap& other) {
        if (this == &other) return *this;

        m_size = other.m_size;
        m_arr  = other.m_arr; 
        return *this;
    }

    // O(1)
    int size() {
        return m_size;
    }


};