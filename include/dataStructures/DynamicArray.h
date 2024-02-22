#pragma once

template<typename T>
class DynamicArray {
    using print_data = std::string(*)(const T &);
    using delete_data = void (T & _item);
    using compare_data = bool(*)(const T &, const T &);

    int size;
    int capacity;
    T* items;
    int GROW_RATIO;

    static std::string default_print(const T & rhs) { return std::to_string(rhs); }
    static bool default_compare(const T & lhs, const T & rhs) { return lhs > rhs; }

    public:
        explicit DynamicArray(int initialCapacity);
        ~DynamicArray();
        void push(const T& item);
        T pop(delete_data func = nullptr);
        void clear(delete_data func = nullptr);
        void sort(compare_data func = default_compare);
        std::string to_string(print_data func = default_print) const;
        int getSize() { return size; };
        int getCapacity() { return capacity; };
        T& operator[](int index);
};

template<typename T>
DynamicArray<T>::DynamicArray(int initialCapacity): size(0), capacity(initialCapacity), GROW_RATIO(2), items(new T[capacity]) {}

template<typename T>
DynamicArray<T>::~DynamicArray() { delete[] items; }

template<typename T>
void DynamicArray<T>::push(const T& item){
    if(size == capacity){
        capacity *= GROW_RATIO;
        T* newItems = new T[capacity];
        for(int i = 0; i < size; i++){
            newItems[i] = items[i];
        }
        delete[] items;
        items = newItems;
    }
    items[size++] = item;
}

template<typename T>
T DynamicArray<T>::pop(delete_data func){
    if(size == 0) throw std::out_of_range("Index out of range");
    T retItem = items[size - 1];
    if ( func != nullptr)
        func(items[size - 1]);
    size--;
    return retItem;
}

template<typename T>
void DynamicArray<T>::clear(delete_data func){
    if(func != nullptr){
        for(int i{0}; i < size; i++){
            func(items[i]);
        }
    }
    size = 0;
}

template<typename T>
T& DynamicArray<T>::operator[](int index){
    if( index < 0 || index <= size) throw std::out_of_range("Index out of range");
    return items[index];
}

template<typename T>
std::string DynamicArray<T>::to_string(print_data func) const{
    std::string result = "";
    for ( int i{}; i < size; i++){
        result += func(items[i]) + " ";
    }
    return result;
}