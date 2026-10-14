//
// Created by Ben Babicka on 7/10/2026.
//

#ifndef ALGORITHMS_MINHEAP_H
#define ALGORITHMS_MINHEAP_H

#include "ArrayList.h"

class MinHeap {
public:
    MinHeap() noexcept : length(0), data({}) {
    };

    int getLength() const noexcept {
        return length;
    }

    void insert(int value) noexcept {
        data.push(value);
        heapifyUp(length);
        length++;
    }

    int remove() {
        if (length == 0) throw std::out_of_range("MinHeap is empty");
        const int out = data[0];
        length--;

        data[0] = data[length];
        data.pop();
        if (length == 0) return out;

        heapifyDown(0);
        return out;
    }

private:
    int length;
    ArrayList<int> data;

    int parent(const int i) noexcept {
        return (i - 1) / 2;
    }

    int leftChild(const int i) noexcept {
        return i * 2 + 1;
    }

    int rightChild(const int i) noexcept {
        return i * 2 + 2;
    }

    void heapifyUp(const int i) noexcept {
        if (i == 0) return;
        const int p = parent(i);
        const int parentV = data[p];
        const int v = data[i];

        if (parentV > v) {
            data[i] = parentV;
            data[p] = v;
            heapifyUp(p);
        }
    }

    void heapifyDown(const int i) noexcept {
        const int lIndex = leftChild(i);
        const int rIndex = rightChild(i);
        if (lIndex >= length) return;

        int smallest = lIndex;
        if (rIndex < length && data[rIndex] < data[lIndex]) smallest = rIndex;

        if (data[smallest] < data[i]) {
            const int temp = data[i];
            data[i] = data[smallest];
            data[smallest] = temp;
            heapifyDown(smallest);
        }
    }
};
#endif //ALGORITHMS_MINHEAP_H
