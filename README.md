# How to Compile and Run
Each data structure is located in its own folder (e.g., Heap/). In that folder you will find the header file of the data structure and a test program. In order to compile, simply run:

> make

in the root directory. This will automatically trigger compilation of all test programs in the respective folders. To run a test program, navigate to the folder of the data structure you want to run and execute:

> ./nameOfDataStructure

Additionally, all data structures are templated, so in order to use them you must choose a type.

# Data Structures Implemented
You can see more information in the respective header files about time complexity above the function names, with a justification if it is not obvious.

### Dynamically Sized Array

Implements a contiguous, indexable array that grows automatically when full.

- **Initial capacity:** 16
- **When array grows:** When `size == capacity`, allocate a new array of size `capacity * 2` and copy elements over.
- **When array shrinks:** Does not shrink.
- **Kattis Submission:** https://ru.kattis.com/courses/T-403-FORC/FORC2026/assignments/aaohpd/submissions/19116347
- **Assumptions:** We assume that the type used has a default constructor.

### Linked List

We implemented a circular doubly linked list with a single sentinel node at the front.  
The sentinel is always present and simplifies edge cases (empty list, insert/erase at ends).

- Cursor-based operations: insert, erase, predecessor, and successor take a pointer to a Node that is already in the list.
- Initial state: the list contains only the sentinel node (`sentinel->next == sentinel` and `sentinel->prev == sentinel`).
- **Kattis Submission:** https://ru.kattis.com/courses/T-403-FORC/FORC2026/assignments/aaohpd/submissions/19117255

### Dequeue

Implemented a dequeue using a circular buffer implementation.

In this implementation, we use a dynamically allocated array to store the elements and modular arithmetic to access them.

- **Initial capacity:** 8
- **When dequeue grows:** When `size == capacity`, allocate a new array of size `capacity * 2` and copy elements over.
- **Assumptions:** We assume that the type used has a default constructor. 
- **Kattis Submission:** https://ru.kattis.com/courses/T-403-FORC/FORC2026/assignments/aaohpd/submissions/19165302

### Heap

Implemented a heap using an array implementation. For index `i`, the parent of `i` is `i / 2`, and the children are `i * 2` and `i * 2 + 1`.

In this implementation, we use the dynamically sized array introduced earlier to store the data.

Index 0 stores a dummy element to simplify parent/child calculations.

- **Assumptions:** Same assumptions as in the dynamically sized array, because we use it in our implementation here. Additionally, we assume that the type passed in can be compared (`<`, `>`, `<=`, `>=`).
- **Type:** We implemented a min heap.
- **Kattis Submission:** https://ru.kattis.com/courses/T-403-FORC/FORC2026/assignments/aaohpd/submissions/19117852

### Hash Table

Not implemented.

### Self Balancing Tree (Treap)

In this solution, we use a Treap for the self-balancing tree. Each item in the tree is stored in a node that has a priority and a key. The tree is structured like a normal binary search tree, but at the same time as a heap through the priority. A random priority is generated with `std::rand()` via `rand_int()`. The heap is structured as a max heap.

Each node additionally stores `left_size` and `right_size`, which represent the sizes of their left and right subtrees.

Insertion and deletion strategy: insert into the binary search tree normally, give the node a random priority, then rotate parents on the way up/down with right and left rotations to ensure that the heap structure is preserved.

As mentioned above, the time complexities are commented in `treap.h`. Even though a Treap is self-balancing, it has a bad worst-case time complexity due to the random factor.

- **Assumptions:** The key supports basic comparisons. Key and value have default constructors.
- **Kattis Submission:** https://ru.kattis.com/courses/T-403-FORC/FORC2026/assignments/aaohpd/submissions/19139178
