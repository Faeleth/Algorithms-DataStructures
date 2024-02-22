#pragma once

template <typename T>
class BinarySearchTree{

    struct Node{
        T data;
        Node * parent;
        Node * left;
        Node * right;
        explicit Node(const T & _data): data(_data), parent(nullptr), left(nullptr), right(nullptr) {};
    };

    using compare_data = bool(*)(const T&, const T&);
    using remove_data = void(*)(const T&);
    using do_traverse = void(const T&);

    enum class TraversalOrder{
        PRE_ORDER,
        IN_ORDER,
        POST_ORDER
    };

    Node * root;
    int size;

    static bool default_compare(const T & lhs, const T & rhs) { return lhs < rhs; }

    void traverse(Node * _node, do_traverse do_traverse_func, TraversalOrder _order);
    void update_parent(Node * del_node, Node * child_node, compare_data compare = default_compare);
    void erase_node(Node * node, remove_data remove = nullptr);
    int calc_height(Node * node);

    public:
        BinarySearchTree();
        BinarySearchTree(const T & _root_data);
        ~BinarySearchTree();
        void insert(const T & _data, compare_data compare = default_compare);
        void remove(const T & _data, compare_data compare = default_compare, remove_data = nullptr);
        Node * search(const T & _data, compare_data compare = default_compare);
        void pre_order(do_traverse func) { traverse(root, func, TraversalOrder::PRE_ORDER); };
        void in_order(do_traverse func) { traverse(root, func, TraversalOrder::IN_ORDER); };
        void post_order(do_traverse func) { traverse(root, func, TraversalOrder::POST_ORDER); };
        void clear(remove_data func = nullptr);
        int bst_height() { return root == nullptr ? 0 : calc_height(root); };
        int get_size();    
};

template <typename T>
BinarySearchTree<T>::BinarySearchTree(): root(nullptr), size(0) {}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(const T & _root_data): root(new Node(_root_data)), size(1) {}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree(){
    clear();
}

template <typename T>
void BinarySearchTree<T>::clear(remove_data remove){
    erase_node(root, remove);
    root = nullptr;
    size = 0;
}

template <typename T>
void BinarySearchTree<T>::erase_node(BinarySearchTree::Node * node, remove_data remove){
    if (node == nullptr)
        return;

    erase_node(node->left, remove);
    erase_node(node->right, remove);
    
    if (remove != nullptr)
        remove(node->data);
        
    node->left = node->right = node->parent = nullptr;
    delete node;
    node = nullptr;
}

template <typename T>
void BinarySearchTree<T>::traverse(Node * _node, do_traverse do_traverse_func, TraversalOrder _order){
    if (_node == nullptr) return;
    if (_order == TraversalOrder::PRE_ORDER) do_traverse_func(_node->data);
    traverse(_node->left, do_traverse_func, _order);
    if (_order == TraversalOrder::IN_ORDER) do_traverse_func(_node->data);
    traverse(_node->right, do_traverse_func, _order);
    if (_order == TraversalOrder::POST_ORDER) do_traverse_func(_node->data);

}

template <typename T>
void BinarySearchTree<T>::insert(const T & _data, compare_data func){
    Node * newNode = new Node(_data);
    Node * current = root;
    Node * parent = nullptr;

    while(current != nullptr){
        parent = current;
        // ignore duplicates
        if(_data == current->data){
            return;
        }
        if(func(_data, current->data)){
            current = current->left;
        } else {
            current = current->right;
        }
    }

    newNode->parent = parent;
    if(parent == nullptr){
        root = newNode;
    } else if(func(_data, parent->data)){
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
    size++;
}

template <typename T>
void BinarySearchTree<T>::update_parent(Node * target_node, Node * child_node, compare_data compare){
    if (root == target_node) {
        root = child_node;
        child_node->parent = nullptr;
        return;
    }
    
    Node * parent = target_node->parent;

    if (child_node != nullptr)
        child_node->parent = parent;
    if (compare(target_node->data, parent->data)){
        parent->left = child_node;
    } else {
        parent->right = child_node;
    }
}

template <typename T>
void BinarySearchTree<T>::remove(const T & _data, compare_data compare_func, remove_data remove_func){
    Node * node = search(_data, compare_func);
    if(node == nullptr) return;
 
    if(node->left == nullptr && node->right == nullptr){
        update_parent(node, nullptr, compare_func);
    }
    else if(node->left == nullptr){ // # 2
        update_parent(node, node->right, compare_func);
    }
    else if(node->right == nullptr){ // # 2
        update_parent(node, node->left, compare_func);
    }
    else {
        Node * successor = node->right;
        while ( successor->left != nullptr )
            successor = successor->left;
        
        update_parent(successor, nullptr, compare_func);
        update_parent(node, successor, compare_func);
        
        successor->left = node->left;
        successor->right = node->right;

        node->left->parent = successor;
    }

    if( remove_func != nullptr ) 
        remove_func(node->data);
    delete node;
    node = nullptr;
    --size;
}

template <typename T>
typename BinarySearchTree<T>::Node * BinarySearchTree<T>::search(const T & _data, compare_data func){
    Node * current = root;
    while(current != nullptr){
        if(_data == current->data){
            return current;
        }
        if(func(_data, current->data)){
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return nullptr;
}

template <typename T>
int BinarySearchTree<T>::calc_height(Node * node){
    if(node == nullptr) return 0;

    int left_node = calc_height(node->left);
    int right_node = calc_height(node->right);
    return std::max(left_node, right_node) + 1;
}