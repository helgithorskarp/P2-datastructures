#include <cstdlib> // rand, srand
#include <ctime>   // time


template <typename T_k, typename T_v>
struct Treap
{
    struct Node {
        Node *left;
        Node *right;
        int left_size;
        int right_size;
        int priority;
        T_k key;
        T_v value;

        Node(
            int left_size = 0,
            int right_size = 0,
            T_k key = T_k(),
            T_v value = T_v()
        )
            : left(nullptr),
            right(nullptr),
            left_size(left_size),
            right_size(right_size),
            priority(0),
            key(key),
            value(value)
        {}
    };

    Node * root;

    Treap() {
        root = nullptr;
    }

    Treap(const Treap& other) {
        /// approach, inorder recursion of existing other, and construct the new tree as we go along
        if (other.root != nullptr) {
            root = new Node(other.root->left_size, other.root->right_size, other.root->key, other.root->value);
            root->priority = other.root->priority;
            preorderInitializer(other.root, root);
        }
        else root = nullptr;/// other root is nullptr, do nothing
    }



    Node * preorderInitializer(Node * other_node, Node * curr_node) {
   
        if (other_node->left != nullptr) {
            Node * new_left = new Node(other_node->left->left_size, other_node->left->right_size, other_node->left->key, other_node->left->value);
            new_left->priority = other_node->left->priority;
            curr_node->left = preorderInitializer(other_node->left, new_left);
        }
        if (other_node->right != nullptr) {
            Node * new_right = new Node(other_node->right->left_size, other_node->right->right_size, other_node->right->key, other_node->right->value);
            new_right->priority = other_node->right->priority;
            curr_node->right = preorderInitializer(other_node->right, new_right);
        }
        return curr_node;
    }



    int rand_int() {
        return std::rand();
    }


    Node* rotate_right(Node* parent) {
        Node* left_child = parent->left;
        Node* left_right_child = left_child->right;

        left_child->right = parent;
        parent->left = left_right_child;

        // update sizes: update the node that moved down first (parent)
        parent->left_size  = size(parent->left);
        parent->right_size = size(parent->right);

        // then update the node that moved up left_child)
        left_child->left_size  = size(left_child->left);
        left_child->right_size = size(left_child->right);

        return left_child;
    }

    
    Node *rotate_left(Node * parent) {
        Node * right_child = parent->right;
        Node * right_left_child = right_child->left;

        right_child->left = parent;
        parent->right = right_left_child;

        /// these function calls update the sizes depending on their new child
        parent->right_size = size(parent->right);
        parent->left_size = size(parent->left);

        right_child->right_size = size(right_child->right);
        right_child->left_size = size(right_child->left);
        return right_child; /// new root of subtree
    }

        Node * Find(T_k k) {
        return Find(k, root);
    }

    Node * Find(T_k k, Node * node) {
        if (node == nullptr) {
            return nullptr;
        }

        if (k < node->key) {
            return Find(k, node->left);
        } else if (k > node->key) {
            return Find(k, node->right);
        } else {
            return node;
        }
    }



    Node* insert(T_k k, T_v v) {
        if (root == nullptr) {
            root = new Node(0, 0, k, v);
            root->priority = rand_int();
            return root;
        }

        ///if exists return that node
        Node * look_up = Find(k);
        if (look_up != nullptr) {
            return look_up;
        }
        /// doesnt exist create a new node and insert
        Node * new_node = new Node(0, 0, k, v);
        new_node->priority = rand_int();


        root = insert(new_node, root);
        return new_node;
    }

    


 Node* insert(Node* new_node, Node* cur) {
    if (cur == nullptr) return new_node;

    if (new_node->key < cur->key) {
        cur->left = insert(new_node, cur->left);

        if (cur->left && cur->priority < cur->left->priority) {
            cur = rotate_right(cur);
        }
    } else {
        cur->right = insert(new_node, cur->right);

        if (cur->right && cur->priority < cur->right->priority) {
            cur = rotate_left(cur);
        }
    }

    // update sizes for BOTH branches
    cur->left_size  = size(cur->left);
    cur->right_size = size(cur->right);

    return cur;
}



    Node * lower_bound(T_k k) {
        /// returns node with smallest key creater than given key
        /// strategy: Loop and try to find the exact key if not found return up a best-canidate key
        return bound(k, root);
    }

    Node * upper_bound(T_k k) {
        /// return the node with smalelst key that is strictly greater than the key passed in
        return bound(k, root, true);
    }

    bool is_valid(T_k cand_key, T_k key, bool upper_bound) {
    ///helper function to determine if a key is valid, depeding on if upper bound is true or we are doing lower bound
    return upper_bound ? (cand_key > key) : (cand_key >= key);
}


    Node * bound(T_k key, Node * cur, bool upper_bound = false) {
        if (cur == nullptr) {
            return nullptr; // best candidate is nullPtr
        }

        Node * best_candidate = nullptr;
        Node * possible_candidate = nullptr;

        if (key < cur->key) {
            ///cur is a candidate
            if (is_valid(cur->key, key, upper_bound)) best_candidate = cur;
            possible_candidate = bound(key, cur->left, upper_bound);

            if (possible_candidate != nullptr) {
                /// if possible candidate is smaller than best candidate and larger than key
                if (possible_candidate->key < cur->key &&
                    is_valid(possible_candidate->key, key, upper_bound)) {
                    best_candidate = possible_candidate;
                }
            }
        }
        else if (key > cur->key) {
            /// cur->KEY IS NOT A CANDIDATE because its smaller than the key
            possible_candidate = bound(key, cur->right, upper_bound);
            if (possible_candidate != nullptr &&
                is_valid(possible_candidate->key, key, upper_bound))
                best_candidate = possible_candidate;
        } else {
            /// only if upper bound is not true can we concider it a candidate
            if (!upper_bound) {
                best_candidate = cur;
            } else {
                // upper_bound: need strictly greater, so look in the right subtree
                best_candidate = bound(key, cur->right, upper_bound);
            }
        }
        return best_candidate;
    }


    int size() {
        if (root == nullptr) return 0;
        return 1 + root->left_size + root->right_size;
    }

    /// this gets the size of the sub tree from node n
    int size(Node* n) {
        return n ? (1 + n->left_size + n->right_size) : 0;
    }


    Node * back() {
        if (root == nullptr) return nullptr;
        return get_extreme(true, root);
    }

    Node * front() {
        if (root == nullptr) return nullptr;
        return get_extreme(false, root);
    }

    /// both front and back call this function
    /// function goes all the way to left/right depending on flag
   Node* get_extreme(bool getMax, Node *cur) {
        Node * extreme_node = getMax ? cur->right : cur->left;
        if (extreme_node == nullptr) {
            return cur;
        }
        else {
            return get_extreme(getMax, extreme_node);
        }
   }


   Node *k_th_element(int k) {
    /// returns the kth element from left to right
    /// strategy: each item stores how many items are in their left sub tree
    /// and right subtree, so in current itteration in recursive call:
        /// if k > left subtree, go right and subtract the size of left subtree + 1
        /// if k < left subtree, go left, dont subtract anything
        /// if k == left sub tree + 1 then we have found our node

    if (k < 0|| k >= size()) return nullptr;

    return k_th_element(k, root);
   }

   Node *k_th_element(int k, Node * cur) { // 0 based indexing
    if (k == cur->left_size) return cur;
    if (k < cur->left_size) return k_th_element(k, cur->left);
    else return k_th_element(k - (cur->left_size + 1), cur->right);
    }

   int rank(Node *node) {
        /// return how many elements smaller are than Node passed in
        /// strategy: at each recursive itteration we keep a count argument initially set to zero
            /// if node is smaller than current key, go to left
            /// if node is greater than current key, go to right adding the size of left subtree to count
            /// if node is found return the count + size of left subtree
        return rank(0, root, node);
   }

    int rank(int count, Node *curr, Node *node) {
        if (curr == nullptr) return -1; /// -1 representing that the rank num was not found

        if (node->key < curr->key) {
            return rank(count, curr->left, node);
        } 
        else if (node->key > curr->key) {
            return rank(count + 1 + curr->left_size, curr->right, node);
        } 
        else {
            return count + curr->left_size;
        }
    }

    Node* predecessor(Node* node) {
        if (node == nullptr) return nullptr;       
        

        int r = rank(node);                       
        if (r == 0) return nullptr;   /// no item is before the given node         

        return k_th_element(r - 1);
    }

    Node* Successor(Node* node) {
        if (node == nullptr) return nullptr;  

        /// im pretty sure that these two functions are literally supposed to do the same thing :)
        return upper_bound(node->key);
    }


    void erase(Node * node){
        ///Remove the node passed in,
        ///Strategy: Set the node we are removing prioriy to a very low valye, (lower than randnumber generator allows)
            /// Repeat:
            /// Pick which child is larger, if left child is larger do a right roation, if right child is smaller do a left roation,
            /// recursive down like this until the node we are trying to remove only has 1 or 0 childs
                /// if node has 1 child simple swap that child with the parent and remove the parent
                /// if node has 0 childs then simply make the parent point at nothing (nullptr)
        
        if (node == nullptr) return;

        node->priority = -999; /// randomint function is strictly positive, so -999 will always swim all the way down

        root = remove(root, node);
        delete node; /// remove helper function does not Delete the value from memory just removes it from tree
        return;
    }

    Node * remove(Node * cur,  Node *node) {
        if (cur == nullptr) return nullptr;


        if (node->key < cur->key) {
            cur->left = remove(cur->left, node);
        } else if (node->key > cur->key) {
            cur->right = remove(cur->right, node);
        } else { /// here we have located at the node we want to remove, that is cur == node
            if (cur->left != nullptr && cur->right != nullptr) {/// both childs are present
                if (cur->left->priority >= cur->right->priority) {
                    cur = rotate_right(cur);
                    cur->right = remove(cur->right, node);
                }
                else {
                    cur = rotate_left(cur);
                    cur->left = remove(cur->left, node);
                }
            } 
            else if (cur->left == nullptr) cur = cur->right; /// these two cases handle both when node has 0 childs and 1 child, if 1 child return that child, if 0 childs return nullptr
            else if (cur->right == nullptr) cur =  cur->left;
        }


        /// update sizes
        if (cur != nullptr) {
        cur->left_size = size(cur->left);
        cur->right_size = size(cur->right);}

        return cur;
    }

    Treap& operator=(const Treap& other) {
        if (this == &other) return *this;

        postorderDeconstructor(root);

        root = nullptr;
        if (other.root != nullptr) {
            root = new Node(other.root->left_size, other.root->right_size, other.root->key, other.root->value);
            root->priority = other.root->priority;
            preorderInitializer(other.root, root);
        }

        return *this;
    }

    ~Treap(){
        /// strategy: in order recursion loop, visit both sub trees and only then we can free the current node;
        postorderDeconstructor(root);
    }

    void postorderDeconstructor(Node * node) {
        if (node == nullptr) return;

        postorderDeconstructor(node->left);
        postorderDeconstructor(node->right);

        delete node;
        return;
    }


    
};
