#include <filesystem>
#include <iostream>

#include "BTree.h"
#include "DoublyLinkedList.h"
#include "MinHeap.h"
#include "RingBuffer.h"
#include "search.h"
#include "sort.h"

int main() {

    ArrayList<int> list{1, 2, 3, 4, 5};
    list.print();
    list.pop();
    list.pop();
    list.print();
    list.push(10);
    list.push(20);
    list.print();

    RingBuffer<int> ring{1,2,3,5};
    ring.print();
    ring.shift();
    ring.push(6);
    ring.print();

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

    DoublyLinkedList<int> dList;
    dList.append(1);
    dList.print();
    dList.append(2);
    dList.append(3);
    dList.prepend(4);
    dList.prepend(5);
    dList.print();
    std::cout << dList.remove(1) << std::endl;
    std::cout << dList.remove(2) << std::endl;
    //std::cout << dList.remove(1) << std::endl; //Throws error
    std::cout << "Contains 1: " << dList.contains(1) << std::endl;
    std::cout << "Contains 4: " << dList.contains(4) << std::endl;
    std::cout << dList.removeAt(1) << std::endl;
    std::cout << dList.get(1) << std::endl;
    dList.print();

    BTree<int> bTree;
    bTree.insert(100);
    std::srand(time(0));
    for (int i = 0; i < 200; i++) {
        bTree.insert(rand() % 200);
    }

    bTree.print();

    std::vector<int> arr;
    for (int i = 0; i < 200; i++) {
        arr.push_back(rand() % 100);
    }
    std::cout << "Quicksort - Unsorted array: [" << arr[0];
    for (std::size_t i = 1; i < arr.size(); i++) {
        std::cout << ", " << arr[i];
    }
    std::cout << "]" << std::endl;
    sort::quick_sort(arr, arr.size());
    std::cout << "Quicksort - Sorted array: [" << arr[0];
    for (std::size_t i = 1; i < arr.size(); i++) {
        std::cout << ", " << arr[i];
    }
    std::cout << "]" << std::endl;

    arr.clear();
    arr.push_back(57);
    for (int i = 0; i < 200; i++) {
        arr.push_back(rand() % 100);
    }
    std::cout << "Bubble sort - Unsorted array: [" << arr[0];
    for (std::size_t i = 1; i < arr.size(); i++) {
        std::cout << ", " << arr[i];
    }
    std::cout << "]" << std::endl;
    sort::bubble_sort(arr, arr.size());
    std::cout << "Bubble sort - Sorted array: [" << arr[0];
    for (std::size_t i = 1; i < arr.size(); i++) {
        std::cout << ", " << arr[i];
    }
    std::cout << "]" << std::endl;

    search::linear_search(arr, arr.size(), 57);
    search::linear_search(arr, arr.size(), 101);
    search::binary_search(arr, arr.size(), 57);
    search::binary_search(arr, arr.size(), 101);
    search::jump_search(arr, arr.size(), 57);
    search::jump_search(arr, arr.size(), 101);
}
