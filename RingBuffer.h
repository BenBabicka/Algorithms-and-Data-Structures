//
// Created by Ben Babicka on 18/09/2026.
//

#ifndef ALGORITHMS_RINGBUFFER_H
#define ALGORITHMS_RINGBUFFER_H
#include <cassert>
#include <initializer_list>
#include <iostream>

template<typename T>
class RingBuffer {
public:
    RingBuffer() noexcept : elements(nullptr), length(0), capacity(0), tail(0), head(0) {
    };

    RingBuffer(std::initializer_list<T> aInit) noexcept : elements(new T[aInit.size()]), length(aInit.size()),
                                                          capacity(aInit.size()), head(aInit.size() - 1),
                                                          tail(aInit.size() - 1) {
        int i = 0;
        for (const T &val: aInit) {
            elements[i++] = val;
        }
    }

    int getLength() noexcept {
        return length;
    }

    int getCapacity() noexcept {
        return capacity;
    }

    void push(T val) noexcept {
        ensureCapacity();
        elements[head] = val;
        adjustHead();

        length++;
        head++;
    }

    T pop() noexcept {
        assert(length > 0);
        length--;
        head--;
        adjustHead();
        T val = std::move(elements[head]);
        elements[head] = T{};
        adjustCapacity();
        return val;
    }

    void unshift(T val) noexcept {
        ensureCapacity();
        elements[tail] = val;
        adjustTail();
        tail--;
        length++;
    }

    T shift() noexcept {
        assert(length > 0);
        length--;
        tail++;
        adjustTail();
        T val = std::move(elements[tail]);
        elements[tail] = T{};
        adjustCapacity();
        return val;
    }

    T getHead() noexcept {
        assert(length > 0);
        return elements[head - 1];
    }

    T getTail() noexcept {
        assert(length > 0);
        return elements[tail];
    }

    void print() noexcept {
        std::cout << "Length: " << length << std::endl;
        std::cout << "Capacity: " << capacity << std::endl;
        std::cout << "Head: " << head << std::endl;
        std::cout << "Tail: " << tail << std::endl;
        std::cout << "Elements: [ ";

        if (length > 0) {
            int index = tail + 1;
            if (index == capacity) {
                index = 0;
            }

            std::cout << elements[index];

            index++;
            if (index == capacity) {
                index = 0;
            }

            for (int i = 0; i < length - 1; i++) {
                std::cout << ", " << elements[index];
                index++;
                if (index == capacity) {
                    index = 0;
                }
            }
        }
        std::cout << " ]" << std::endl;
    }

    bool full() const noexcept {
        return length == capacity;
    }

    bool empty() const noexcept {
        return length == 0;
    }

    void clear() noexcept {
        delete[] elements;
        elements = new T[capacity];
        capacity = 0;
        length = 0;
        head = 0;
        tail = 0;
    }

    T operator[] (int i) const {
        int index = (tail + 1) + i;
        if (index >= capacity) index = capacity - index;
        return elements[index];
    }

    T& operator[] (int i) {
        int index = (tail + 1) + i;
        if (index >= capacity) index = capacity - index;
        return elements[i];
    }



private:
    T *elements;
    int length;
    int capacity;
    int tail;
    int head;

    void resize(int newCapacity) {
        T *newElements = new T[newCapacity];
        int index = tail + 1;
        if (index == capacity) {
            index = 0;
        }
        for (int i = 0; i < length; i++) {
            newElements[i] = elements[index];
            index++;
            if (index == capacity) {
                index = 0;
            }
        }
        delete[] elements;
        elements = newElements;
        capacity = newCapacity;
        tail = capacity - 1;
        head = length;
    }

    void ensureCapacity() {
        if (capacity == 0)
            resize(1);
        if (length == capacity) {
            resize(capacity * 2);
        }
    }

    void adjustCapacity() {
        if (length * 4 <= capacity) {
            if (capacity / 2 == 0)
                resize(1);
            else
                resize(capacity / 2);
        }
    }

    void adjustHead() {
        if (head >= capacity)
            head = 0;

        if (head < 0)
            head = capacity - 1;

        if (length == capacity) {
            resize(capacity * 2);
        }
    }

    void adjustTail() {
        if (tail >= capacity)
            tail = 0;

        if (tail < 0)
            tail = capacity - 1;

        if (length == capacity) {
            resize(capacity * 2);
        }
    }
};
#endif //ALGORITHMS_RINGBUFFER_H
