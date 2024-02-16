#include <iostream>
#include <dataStructures/LinkedList.h>

int main(int, char**){
    std::cout << "Hello, from Algorithms!\n";
    LinkedList<int> list;

    for(int i{}; i<10; i++){
        list.push_back(i);
    }

    // std::cout << list.toString() << std::endl;
}
