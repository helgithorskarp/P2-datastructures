// Generic hash: O(1)
template<typename T>
int _hash(T key, int capacity) {
    int res = key % capacity;
    if (res < 0) {
        res += capacity;
    }
    return res;
}

// Fowler-Noll-Vo hash for C strings: O(n) where n is each byte of the key
// Templated keys do not seem to work for strings as of now :(
template<>
int _hash<char *>(char *key, int capacity) {
    unsigned long fnvOffsetBasis = 2166136261;
    unsigned long fnvPrime = 16777619;

    while (*key != '\0') {
        fnvOffsetBasis = (fnvOffsetBasis ^ static_cast<unsigned char>(*key)) * fnvPrime;
        ++key;
    }

    unsigned int index = fnvOffsetBasis % capacity;

    return (int) index;
}

template <typename K, typename V>
struct HashTable {
    private:
    // Linked list as buckets
    struct m_Node {
        K key;
        V value;
        m_Node *next;
    
        m_Node(K k, V v) : key(k), value(v), next(nullptr) {};
    };

    // Array of linked lists buckets
    m_Node **m_array;
    int m_capacity;
    int m_size;

    // Deep copy linked list: O(n) where n is # of nodes
    m_Node *deepCopyList(m_Node *node) {
        if (node == nullptr) {
            return nullptr;
        }
        
        m_Node *newNode = new m_Node(node->key, node->value);
        newNode->next = deepCopyList(node->next);
        return newNode;
    }

    // Deep delete nodes: O(n) where n is # of nodes
    m_Node *deepDeleteNode(m_Node *node) {
        if (node == nullptr) {
            return nullptr;
        }

        deepDeleteNode(node->next);
        delete node;
        return nullptr;
    }

    // Hash: see _hash()
    int hash(K key) {
        return _hash<K>(key, m_capacity);
    }
    
    public:
    // Default constructor: O(n) where n is capacity
    HashTable<K, V>() : m_capacity(16), m_size(0) {
        m_array = new m_Node*[m_capacity];
        for (int i = 0; i < m_capacity; ++i) {
            m_array[i] = nullptr;
        }
    }

    // Copy constructor: O(n + m) where n is capacity
    // and m is # of nodes
    HashTable<K, V>(const HashTable& other) {
        m_capacity = other.m_capacity;
        m_size = other.m_size;
        m_array = new m_Node*[m_capacity];
        
        for (int i = 0; i < m_capacity; ++i) {
            m_array[i] = deepCopyList(other.m_array[i]);
        }
    }

    // Destructor: O(n + m) where n is capacity and
    // m is # of nodes
    ~HashTable<K, V>() {
        for (int i = 0; i < m_capacity; ++i) {
            deepDeleteNode(m_array[i]);
        }

        delete[] m_array;
    }

    // [] overload: find or insert unique key, see _find()
    V& operator[](K key) {
        m_Node *node = _find(key);
        return node->value; 
    }

    // Assign overload: O(n + m) where n is total capacity
    // and m is total # of nodes
    HashTable &operator=(const HashTable& other) {
        if (this == &other) {
            return *this;
        }

        for (int i = 0; i < m_capacity; ++i) {
            deepDeleteNode(m_array[i]);
        }
        delete[] m_array;

        m_Node **newArray = new m_Node*[other.m_capacity];

        for (int i = 0; i < other.m_capacity; ++i) {
            newArray[i] = deepCopyList(other.m_array[i]);
        }

        m_array = newArray;
        m_capacity = other.m_capacity;
        m_size = other.m_size;

        return *this;
    }

    // Helper for find() and exists()
    // Find node associated with key: O(n) where n is # of nodes at
    // the hash index
    // Best case: O(1) if key is the first node at the hash index
    m_Node *_find(K key) {
        int index = hash(key);

        m_Node *curr = m_array[index];
        while (curr != nullptr) {
            if (curr->key == key) {
                return curr;
            }
            curr = curr->next;
        }

        return nullptr;
    }
    
    // Check if key exists: See _find()
    bool exists(K key) {
        return _find(key) != nullptr;
    }

    // Find and return value: see _find()
    V *find(K key) {
        m_Node *node = _find(key);
        return node != nullptr ? &node->value : nullptr;
    }

    // Insert unique key: exists has O(n) where n is # of nodes at the hash index
    // but insertion itself is amortized O(1), rehashing is O(n)
    void insert(K key, V value) {
        if (exists(key)) {
            return;
        }

        if ((float)m_size / m_capacity >= 0.75) {
            rehash();
        }
        
        int index = hash(key);
        m_Node *newNode = new m_Node(key, value);
        newNode->next = m_array[index];
        m_array[index] = newNode;
        ++m_size;
    }

    // Erase node associated with key: O(n) where n is # of nodes
    // Best case: O(1) if key is first at hash index
    void erase(K key) {
        int index = hash(key);

        m_Node *curr = m_array[index];

        // Do nothing if list at index is empty
        if (curr == nullptr) {
            return;
        }

        while (curr != nullptr) {
            // If the first node is the node to be erased
            if (curr->key == key) {
                m_array[index] = curr->next;
                delete curr;
                --m_size;
                return;
            }
            // Next node has the key, rearrange next pointers
            // and free the node to be erased
            else if (curr->next != nullptr && curr->next->key == key) {
                m_Node *delNode = curr->next;
                curr->next = curr->next->next;
                delete delNode;
                --m_size;
                return;
            }
            curr = curr->next;
        }
    }

    // Size: O(1), manually tracked
    int size() {
        return m_size;
    }

    // Rehash when high load factor: O(n + m) where n is total capacity
    // and m is total # of nodes
    void rehash() {
        int oldCapacity = m_capacity;
        m_Node **oldArray = m_array;

        m_capacity *= 2;
        m_array = new m_Node*[m_capacity];

        for (int i = 0; i < m_capacity; ++i) {
            m_array[i] = nullptr;
        }

        m_size = 0;
        for (int i = 0; i < oldCapacity; ++i) {
            m_Node *curr = oldArray[i];
            while (curr != nullptr) {
                insert(curr->key, curr->value);

                m_Node *delNode = curr;
                curr = curr->next;
                delete delNode;
            }
        }

        delete[] oldArray;
    }
};