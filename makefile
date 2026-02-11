CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++98

all:
	$(CXX) $(CXXFLAGS) Dequeue/dequeue_template.cpp -o Dequeue/Dequeue
	$(CXX) $(CXXFLAGS) DynamicArray/template.cpp -o DynamicArray/DynamicArray
	$(CXX) $(CXXFLAGS) Heap/heaptemp.cpp -o Heap/Heap
	$(CXX) $(CXXFLAGS) LinkedList/kattis_dll_template.cpp -o LinkedList/LinkedList
	$(CXX) $(CXXFLAGS) Treap/bst_template.cpp -o Treap/Treap

clean:
	rm -f Dequeue/Dequeue
	rm -f DynamicArray/DynamicArray
	rm -f Heap/Heap
	rm -f LinkedList/LinkedList
	rm -f Treap/Treap
