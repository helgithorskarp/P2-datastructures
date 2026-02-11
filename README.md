# How to compile and run
Each data structure is located in its own folder (e.g. Heap/) in that folder you will find a the header file of the data structure + the templete to test it. In order to compile simply run 
> make 

in the root directory, this will automatically trigger compilation of all of the templete files in the respective folders. Then to run the templete files you navigate to the folder of the data structure you want to run and write
> ./nameOfDataStructure

Additionally we templeted all data structures so in order to use them you have to choose a type of storage






# Data structures Implemented
You can see more information in the respective header files about time complexity above the function names. With a justification why if it is not obvious. 

### Dynamically sized array


Implements a contiguous, indexable array that grows automatically when full.

- **Initial capacity:** 16
- **When array grows:** when `size == capacity`, allocate a new array of size `capacity * 2` and copy elements over.
- **When array shrinks:** does not shrink.
- **Kattis Submittion:** Submittion on kattis https://ru.kattis.com/courses/T-403-FORC/FORC2026/assignments/aaohpd/submissions/19116347
- **Assumptions:** We assume that the type used has a default constructor.




### Linked list
Sumbmittion on kattis
https://ru.kattis.com/courses/T-403-FORC/FORC2026/assignments/aaohpd/submissions/19117255

We implemented a doubly linked list using a single sentinel node at the front, forming a circular structure.
### Dequeue




### Heap
Submittion on kattis
https://ru.kattis.com/courses/T-403-FORC/FORC2026/assignments/aaohpd/submissions/19117852

Implemented a heap using an array implementation. That is internally the first item in the array is always empty and for index i, parent of i is i//2, children are i*2 and i*2 + 1.

In this implementation we use the dynamically sized array introduced before to store the data
- **Assumptions**: Samea assumptions as in the dynimcally sized array because we use that in out implementation here. Additionally we assume that the type pased in can be compared (<, >, <=, >=)
- **Type**: We implimented a min heap
- **Indexing**: Index 0 stores a dummy element to simplify parent/child


### Hash table

### Self Balancing Tree (Treap)
Submittion on kattis
https://ru.kattis.com/courses/T-403-FORC/FORC2026/assignments/aaohpd/submissions/19139178

In this solution we use a Treap for the self balancing tree. That each each item in the tree is stored in a node that has a priority and a key. Tree is structured like a normal binary search tree but at the same time as a heap trough the priority. Random priority is generated with std::rand() via rand_int(). the heap is structured as a MAX heap

Each node stores additionally left_size and right_size which represent the size of their left and right subtrees

Insertion and deletion strategy high level: Insert into the binary search tree normally, give the node a random priority. Rotate parents on way up/down with right and left rotations to ensure that the heap structure is preservered.



- **Assumptions**: The key supports basic comparisons. Key and value have default constructors

