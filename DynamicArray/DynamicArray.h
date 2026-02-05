
template<typename T>
struct DynamicArray {
    int m_capacity;
    int m_size;
    T* m_array;

    DynamicArray(): m_capacity(16), m_size(0) {
        m_array = new T[m_capacity];
    }
    DynamicArray(const DynamicArray& other){
        m_capacity = other.m_capacity;
        m_size = other.m_size;
        m_array = new T[m_capacity];

        for (int i = 0; i < m_size; i++) {
            m_array[i] = other.m_array[i];
        }
    }

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


    void push_back(T item) {
        if (m_size == m_capacity) { /// array is full double array size
            reserve(m_capacity * 2);
        }

        m_array[m_size++] = item;
    }


    T pop_back() {
        if (m_size == 0) return T{};   

        T value = m_array[m_size - 1];
        --m_size;
        return value;
    }


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


    T erase(int index) {
        if (index < 0 || index >= m_size) {
            return T{};
        }

        T return_item = m_array[index];

        for (int i = index; i < m_size - 1; i++) {
            m_array[i] = m_array[i + 1];
        }

        --m_size;
        return return_item;
    }


    T& operator[](int index) {
        return m_array[index];
    }

    ~DynamicArray() {
        delete[] m_array;
    }

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