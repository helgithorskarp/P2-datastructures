
template<typename T>
struct DynamicArray {
    int m_capacity;
    int m_size;
    T* m_array;

    DynamicArray(): m_capacity(16), m_size(0) {
        m_array = new T[m_capacity];
    }

    /// O(n) where n is the size of other array, have to copy everything over
    DynamicArray(const DynamicArray& other){
        m_capacity = other.m_capacity;
        m_size = other.m_size;
        m_array = new T[m_capacity];

        for (int i = 0; i < m_size; i++) {
            m_array[i] = other.m_array[i];
        }
    }


/// Time complexity: O(N) where N is the size of the array in use
/// have have to create a new array of the new capacity and copy all elements over
void reserve(int new_capacity)
{
    if (new_capacity <= m_capacity) return; /// do nothing if n new capacity is not larger

    T* new_array = new T[new_capacity];


    for (int i = 0; i < m_size; ++i) {
        new_array[i] = m_array[i];
    }

    delete[] m_array;

    m_array = new_array;
    m_capacity = new_capacity;
}


/// time complexity is O(1) if new size is smaller than old one, just change the pointer of the size
/// if size is greater than the capacity then the time complexity is O(n) we have to copy to a new array
/// if the size is larger than old size but not greater than capicity then its O(new_size - old_size)
void resize(int new_size) {
    int old_size = m_size;

    if (new_size > m_capacity) {
        reserve(new_size);
    }

    if (new_size > old_size) {
        for (int i = old_size; i < new_size; i++) {
            m_array[i] = T();   /// assume T has a default constructor
        }
    }
    m_size = new_size;
}



/// Amortized O(1). On average, the operation is constant time except when resizing occurs.
    void push_back(T item) {
        if (m_size == m_capacity) { /// array is full double array size
            reserve(m_capacity * 2);
        }

        m_array[m_size++] = item;
    }


/// O(1)
    T pop_back() {
        if (m_size == 0) return T();   

        T value = m_array[m_size - 1];
        --m_size;
        return value;
    }


/// time complexity is O(n) worst case we have to shift all elements to the right
    void insert(int index, T value) {
        if (index < 0 || index > m_size) return;

        if (m_size == m_capacity) {
            reserve(2 * m_capacity);
        }

        for (int i = m_size; i > index; i--) {
            m_array[i] = m_array[i - 1];
        }

        m_array[index] = value;
        ++m_size;
    }

/// time complexity is O(n) worst case we have to shift all elements to the right
    T erase(int index) {
        if (index < 0 || index >= m_size) {
            return T();
        }

        T return_item = m_array[index];

        for (int i = index; i < m_size - 1; i++) {
            m_array[i] = m_array[i + 1];
        }

        --m_size;
        return return_item;
    }

    //O(1)
    T& operator[](int index) {
        return m_array[index];
    }

    // O(1)
    ~DynamicArray() {
        delete[] m_array;
    }

/// O(n) where n is the size of the other array we have to copy everything over
    DynamicArray& operator=(const DynamicArray& other) {
        if (this == &other) return *this;


        T * new_array = new T[other.m_capacity];

        for (int i = 0; i < other.m_size; i++) {
            new_array[i] = other.m_array[i];
        }

        delete[] m_array;
        m_array = new_array;
        m_capacity = other.m_capacity;
        m_size = other.m_size;

        return *this;
    }


};