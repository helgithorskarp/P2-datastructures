template <typename T>
struct Deque {
    T* m_data;
    int m_size;
    int m_capacity;
    int m_front;

    Deque(): m_size(0), m_capacity(8), m_front(0) {
        m_data = new T[m_capacity];
    }
    
    /// O(n) where n is the size of other deque, have to copy everything over
    Deque(const Deque& other) {
        m_data = new T[other.m_capacity];
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_front = 0;

        for (int i = 0; i < other.m_size; i++) {
            m_data[i] = other[i];
        }
    }

    /// O(n) where n is the size of the other deque, have to copy everything over
    void resize(int newCap) {
        T* newData = new T[newCap];

        for (int i = 0; i < m_size; i++)
            newData[i] = (*this)[i];

        delete[] m_data;
        m_data = newData;
        m_capacity = newCap;
        m_front = 0;
    }
    
    /// Worst case: O(n) if resize is triggered
    /// Otherwise: O(1) since we just change some pointers and add the element to the back
    void push_back(T el) {
        if (m_size == m_capacity) {
            resize(m_capacity * 2);
        }
        m_data[(m_front + m_size) % m_capacity] = el;
        m_size++;
    }

    /// O(1) since we just change some pointers and remove the element from the back
    T pop_back() {
        if (m_size == 0) return T();
        T returnItem = m_data[(m_front + m_size - 1) % m_capacity];
        m_size--;
        return returnItem;
    }

    /// Worst case: O(n) if resize is triggered
    /// Otherwise: O(1) since we just change some pointers and add the element to the back
    void push_front(T el) {
        if (m_size == m_capacity) {
            resize(m_capacity * 2);
        }
        m_front = (m_front - 1 + m_capacity) % m_capacity;
        m_data[m_front] = el;
        m_size++;
    }

    /// O(1) since we just change some pointers and remove the element from the front
    T pop_front() {
        if (m_size == 0) return T();
        T returnItem = m_data[m_front];
        m_front = (m_front + 1) % m_capacity;
        m_size--;
        return returnItem;
    }

    /// O(1)
    T& front() {
        return m_data[m_front];
    }
    /// O(1)
    const T& front() const {
        return m_data[m_front];
    }

    /// O(1)
    T& back() {
        return m_data[(m_front + m_size - 1) % m_capacity];
    }
    /// O(1)
    const T& back() const {
        return m_data[(m_front + m_size - 1) % m_capacity];
    }

    //O(1)
    T& operator[](int index) {
        return m_data[(m_front + index) % m_capacity];
    }
    //O(1)
    const T& operator[](int index) const {
        return m_data[(m_front + index) % m_capacity];
    }

    //O(1)
    ~Deque() {
        delete[] m_data;
    }

    /// O(n) where n is the size of the other deque we have to copy everything over
    Deque& operator=(const Deque& other) {
        if (this == &other) return *this;

        T* new_data = new T[other.m_capacity];

        for (int i = 0; i < other.m_size; i++) {
            new_data[i] = other[i];
        }

        delete[] m_data;
        m_data = new_data;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_front = 0;
        return *this;
    }

    /// O(1)
    int size() const {
        return m_size;
    }


};