//
// Created by Ben Babicka on 7/10/2026.
//

#ifndef ALGORITHMS_MINHEAP_H
#define ALGORITHMS_MINHEAP_H
#include <cmath>

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

    int remove() noexcept {
        if (length == 0) return -1;
        const int out = data[0];
        length--;

        if (length == 0) {
            data = {};
            return out;
        }
        data[0] = data[length];

        heapifyDown(0);
        return out;
    }

private:
    int length;
    ArrayList<int> data;

    int parent(const int i) noexcept {
        return std::floor((i - 1) / 2);
    }

    int leftChild(const int i) noexcept {
        return parent(i * 2) + 1;
    }

    int rightChild(const int i) noexcept {
        return parent(i * 2) + 2;
    }

    void heapifyUp(const int i) noexcept {
        if (i == 0) return;
        const int p = parent(i);
        const int parentV = data[i];
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
        if (i >= length || lIndex >= length) return;

        const int lV = data[lIndex];
        const int rV = data[rIndex];
        const int v = data[i];

        if (lV > rV && v > rV) {
            data[i] = rV;
            data[rIndex] = v;
            heapifyDown(rIndex);
        } else if (rV > lV && v > lV) {
            data[i] = lV;
            data[lIndex] = v;
            heapifyDown(lIndex);
        }
    }
};
#endif //ALGORITHMS_MINHEAP_H
