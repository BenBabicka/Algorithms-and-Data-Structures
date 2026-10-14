#include <filesystem>
#include <iostream>

#include "MinHeap.h"


int main() {

    ArrayList<int> list{1, 2, 3, 4, 5};

    list.print();
    list.pop();
    list.pop();
    list.print();
    list.push(10);
    list.push(20);
    list.print();

    MinHeap heap;

    heap.insert(5);
    heap.insert(2);
    heap.insert(1);
    heap.insert(20);
    heap.insert(10);
    std::cout << heap.remove() << std::endl;
    std::cout << heap.remove() << std::endl;
    std::cout << heap.remove() << std::endl;
    std::cout << heap.remove() << std::endl;
    std::cout << heap.remove() << std::endl;
}
