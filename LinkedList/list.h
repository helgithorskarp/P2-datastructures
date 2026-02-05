



/// has a sentinel Node at front
template <typename T>
    struct DLL {
        struct Node {
        Node * prev;
        Node * next;
        T val;
    };

    Node * sentinel;
    int m_size;

    DLL() {
        sentinel = new Node;
        sentinel->next = sentinel;
        sentinel->prev = sentinel;

        m_size = 0;
    }


    
DLL(const DLL& other) {
    sentinel = get_copy_list(other.sentinel);

    m_size = other.m_size;
}

Node* sentinel_end_node() {
    return sentinel;
}

Node* begin_node() {
    return sentinel->next;
}



Node* get_copy_list(const Node* sentinel) {
    Node* new_sentinel = new Node;
    new_sentinel->next = new_sentinel;
    new_sentinel->prev = new_sentinel;

    Node* cursor_other = sentinel->next;     // One step ahead of new list
    Node* tail = new_sentinel;               // starts at sentinel the new list

    while (cursor_other != sentinel) {       // stop when we loop back 
        Node* new_node = new Node;
        new_node->val = cursor_other->val;

        // append to end of new list
        tail->next = new_node;
        new_node->prev = tail;

        // keep cycle closed to the NEW sentinel
        new_node->next = new_sentinel;
        new_sentinel->prev = new_node;

        tail = new_node;
        cursor_other = cursor_other->next;
    }

    return new_sentinel;
}



    Node* front() {
        return sentinel->next;
    }

    Node* back() {
        return sentinel->prev;
    }

    Node* insert(Node* cursor, T value) {
        Node* new_node = new Node;
        new_node->val = value;

        new_node->next = cursor;
        new_node->prev = cursor->prev;

        cursor->prev->next = new_node;
        cursor->prev = new_node;

        m_size++;
        return new_node;
    }


    Node* erase(Node* cursor) {
        cursor->prev->next = cursor->next;
        cursor->next->prev = cursor->prev;

        Node * after_pointer = cursor->next;

        delete cursor;

        m_size--;
        return after_pointer;
    }

    Node* predecessor(Node * cursor) {
        return cursor->prev;
    }

    Node* successor(Node * cursor) {
        return cursor->next;
    }

    int size() const {
        return m_size;
    }


    void deleteDLLmemory(Node* sentinel) {
        Node* curr = sentinel->next;

        while (curr != sentinel) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }

        delete sentinel;
    }


    ~DLL() {
        deleteDLLmemory(sentinel);
    }


    DLL& operator=(const DLL& other) {
        if (this == &other)
            return *this;

        deleteDLLmemory(sentinel);

        sentinel = get_copy_list(other.sentinel);
        m_size = other.m_size;

        return *this;
    }




};