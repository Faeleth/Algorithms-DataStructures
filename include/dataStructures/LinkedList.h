#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

template<typename T>
class LinkedList {
    
    struct Node {
        T data;
        Node* next;
        Node* prev;
        explicit Node(const T& _data): data(_data), next(nullptr), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;

    bool pop();

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
        bool empty();
        void clear();
};

template<typename T> 
LinkedList<T>::LinkedList(): head(nullptr), tail(nullptr), size(0) {}

template<typename T>
LinkedList<T>::~LinkedList(){
    // clear();
}

template<typename T>
void LinkedList<T>::push_back(const T& _data){
    Node* newNode = new Node(_data);
    
    if(size == 0){
        head = tail = newNode;
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

}

template<typename T>
void LinkedList<T>::erase(int index){

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
bool LinkedList<T>::empty(){

}

template<typename T>
void LinkedList<T>::clear(){

}

#endif // LINKED_LIST_H_