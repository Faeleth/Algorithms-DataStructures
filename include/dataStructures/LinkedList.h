#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

template<typename T>
class LinkedList {
    using print_data = std::string(*)(const T&);

    struct Node {
        T data;
        Node* next;
        Node* prev;
        explicit Node(const T& _data): data(_data), next(nullptr), prev(nullptr){}
    };

    Node* head;
    Node* tail;
    int size;

    bool pop();
    static std::string def_to_cout_func(const T & rhs) { return std::to_string(rhs); }

    public:
        LinkedList();
        ~LinkedList();
        void push_back(const T& _data);
        void push_front(const T& _data);
        void pop_back();
        void pop_front();
        void insert(int index, const T& _data);
        void erase(int index);
        T& operator[](int index);
        int getSize() { return size; };
        void clear();
        std::string to_string(print_data func = def_to_cout_func) const;
};

template<typename T> 
LinkedList<T>::LinkedList(): head(nullptr), tail(nullptr), size(0) {}

template<typename T>
LinkedList<T>::~LinkedList(){
    clear();
}

template<typename T>
void LinkedList<T>::push_back(const T& _data){
    Node* newNode = new Node(_data);
    
    if(size == 0){
        head = tail = newNode;
        size++;
        return;
    } 

    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;

    size++;
}

template<typename T>
void LinkedList<T>::push_front(const T& _data){
    Node* newNode = new Node(_data);
    
    if(size == 0){
        head = tail = newNode;
        return;
    } 

    head->prev = newNode;
    newNode->next = head;
    head = newNode;

    size++;
}

template<typename T>
bool LinkedList<T>::pop(){
    if(size == 0) { return true; }

    if(size == 1) {
        delete head;
        head = tail = nullptr;
        size--;
        return true;
    }

    return false;
}

template<typename T>
void LinkedList<T>::pop_back(){

    if(pop()) { return; }

    Node* voyager = tail;
    tail = tail->prev;
    tail->next = nullptr;
    delete voyager;

    size--;
}

template<typename T>
void LinkedList<T>::pop_front(){
    
    if(pop()) { return; }

    Node* voyager = head;
    head = head->next;
    head->prev = nullptr;
    delete voyager;

    size--;
}

template<typename T>
void LinkedList<T>::insert(int index, const T& _data){
    if(index < 0 || index > size) { throw std::out_of_range("Index out of range"); }

    if(index == 0) { push_front(_data); return; }
    if(index == size) { push_back(_data); return; }

    Node* newNode = new Node(_data);
    Node* voyager = head;
    while(index--){
        voyager = voyager->next;
    }

    newNode->next = voyager;
    newNode->prev = voyager->prev;
    voyager->prev->next = newNode;
    voyager->prev = newNode;

    size++;
}

template<typename T>
void LinkedList<T>::erase(int index){
    if(index < 0 || index >= size) { throw std::out_of_range("Index out of range"); }

    if(index == 0) { pop_front(); return; }
    if(index == size-1) { pop_back(); return; }

    Node* voyager = head;
    while(index--){
        voyager = voyager->next;
    }

    voyager->prev->next = voyager->next;
    voyager->next->prev = voyager->prev;
    delete voyager;

    size--;
}

template<typename T>
T& LinkedList<T>::operator[](int index){
    if(index < 0 || index >= size) { throw std::out_of_range("Index out of range"); }

    Node* voyager = head;
    while(index--){
        voyager = voyager->next;
    }
    
    return voyager->data;
}

template<typename T>
void LinkedList<T>::clear(){
    Node* voyager = head;
    while(voyager){
        Node* temp = voyager;
        voyager = voyager->next;
        delete temp;
    }
    head = tail = nullptr;
    size = 0;
}

template<typename T>
std::string LinkedList<T>::to_string(print_data func) const {
    std::string result;
    Node* voyager = head;
    while(voyager){
        result += std::to_string(voyager->data) + " ";
        voyager = voyager->next;
    }
    return result;
}

#endif // LINKED_LIST_H_