#include <filesystem>
#include <iostream>

#include "MinHeap.h"

int main() {

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

    return 0;
}
