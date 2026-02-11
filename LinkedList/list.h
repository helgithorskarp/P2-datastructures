

/// has a sentinel Node at front
template <typename T>
struct DLL
{
    struct Node
    {
        Node *prev;
        Node *next;
        T val;
    };

    Node *sentinel;
    int m_size;

    // O(1)
    DLL()
    {
        sentinel = new Node;
        sentinel->next = sentinel;
        sentinel->prev = sentinel;

        m_size = 0;
    }

    /// O(n) where n is the size of other linked list. Has to loop trough other linked list and create a copy of it.
    DLL(const DLL &other)
    {
        sentinel = get_copy_list(other.sentinel);

        m_size = other.m_size;
    }

    // O(1)
    Node *sentinel_end_node()
    {
        return sentinel;
    }

    /// O(1)
    Node *begin_node()
    {
        return sentinel->next;
    }

    /// O(n) has to create a new list by deepcopying the other one, that is looping trough the entire other list
    Node *get_copy_list(const Node *sentinel)
    {
        Node *new_sentinel = new Node;
        new_sentinel->next = new_sentinel;
        new_sentinel->prev = new_sentinel;

        Node *cursor_other = sentinel->next; // One step ahead of new list
        Node *tail = new_sentinel;           // starts at sentinel the new list

        while (cursor_other != sentinel)
        { // stop when we loop back
            Node *new_node = new Node;
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

    /// O(1)
    Node *front()
    {
        return sentinel->next;
    }

    /// O(1)
    Node *back()
    {
        return sentinel->prev;
    }

    /// O(1), just hast to move a few pointers around the cursor
    Node *insert(Node *cursor, T value)
    {
        Node *new_node = new Node;
        new_node->val = value;

        new_node->next = cursor;
        new_node->prev = cursor->prev;

        cursor->prev->next = new_node;
        cursor->prev = new_node;

        m_size++;
        return new_node;
    }

    /// O(1) just has to move a few pointers around the cursor
    Node *erase(Node *cursor)
    {
        cursor->prev->next = cursor->next;
        cursor->next->prev = cursor->prev;

        Node *after_pointer = cursor->next;

        delete cursor;

        m_size--;
        return after_pointer;
    }

    /// O(1)
    Node *predecessor(Node *cursor)
    {
        return cursor->prev;
    }

    /// O(1)
    Node *successor(Node *cursor)
    {
        return cursor->next;
    }

    /// O(1)
    int size() const
    {
        return m_size;
    }


    /// helper funciton loops trough the list and deletes all notes, O(n)
    void deleteDLLmemory(Node *sentinel)
    {
        Node *curr = sentinel->next;

        while (curr != sentinel)
        {
            Node *next = curr->next;
            delete curr;
            curr = next;
        }

        delete sentinel;
    }

    /// O(n) calls the helper function time complexity explained above
    ~DLL()
    {
        deleteDLLmemory(sentinel);
    }

    /// time complexity is O(n + m) where n is the size of current list and m is the size of other list
    /// we first have to delete our list O(n) operations, then we have to do a deep copy of other list O(m) operation
    ///total O(n + m)
    /// (Self-assignment: O(1))
    DLL &operator=(const DLL &other)
    {
        if (this == &other)
            return *this;

        deleteDLLmemory(sentinel);

        sentinel = get_copy_list(other.sentinel);
        m_size = other.m_size;

        return *this;
    }
};