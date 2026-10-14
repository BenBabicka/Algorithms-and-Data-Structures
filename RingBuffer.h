//
// Created by Ben Babicka on 18/09/2026.
//

#ifndef ALGORITHMS_RINGBUFFER_H
#define ALGORITHMS_RINGBUFFER_H
#include <cassert>
#include <initializer_list>
#include <iostream>
#include <utility>

template<typename T>
class RingBuffer {
public:
    RingBuffer() noexcept : elements(nullptr), length(0), capacity(0), tail(0), head(0) {
    };

    RingBuffer(std::initializer_list<T> aInit) : elements(nullptr), length(0), capacity(0), tail(0), head(0) {
        if (aInit.size() == 0) return;

        capacity = static_cast<int>(aInit.size());
        elements = new T[capacity];

        for (const T &val: aInit) {
            elements[length++] = val;
        }
        tail = capacity - 1;
        head = 0;
    }

    ~RingBuffer() {
        delete[] elements;
    }

    RingBuffer(const RingBuffer &other) : elements(nullptr), length(other.length), capacity(other.capacity),
                                          tail(other.tail), head(other.head) {
        if (capacity > 0) {
            elements = new T[capacity];
            for (int i = 0; i < capacity; i++) {
                elements[i] = other.elements[i];
            }
        }
    }

    RingBuffer(RingBuffer &&other) noexcept : elements(other.elements), length(other.length), capacity(other.capacity),
                                             tail(other.tail), head(other.head) {
        other.elements = nullptr;
        other.length = 0;
        other.capacity = 0;
        other.tail = 0;
        other.head = 0;
    }

    RingBuffer &operator=(RingBuffer other) noexcept {
        swap(other);
        return *this;
    }

    void swap(RingBuffer &other) noexcept {
        std::swap(elements, other.elements);
        std::swap(length, other.length);
        std::swap(capacity, other.capacity);
        std::swap(head, other.head);
        std::swap(tail, other.tail);
    }

    int getLength() const noexcept {
        return length;
    }

    int getCapacity() const noexcept {
        return capacity;
    }

    void push(T val) noexcept {
        ensureCapacity();
        elements[head] = std::move(val);
        head = next(head);
        length++;
    }

    T pop() noexcept {
        assert(length > 0);
        head = prev(head);
        T val = std::move(elements[head]);
        elements[head] = T{};
        length--;
        adjustCapacity();
        return val;
    }

    void unshift(T val) noexcept {
        ensureCapacity();
        elements[tail] = std::move(val);
        tail = prev(tail);
        length++;
    }

    T shift() noexcept {
        assert(length > 0);
        tail = next(tail);
        T val = std::move(elements[tail]);
        elements[tail] = T{};
        length--;
        adjustCapacity();
        return val;
    }

    T getHead() const noexcept {
        assert(length > 0);
        return elements[prev(head)];
    }

    T getTail() const noexcept {
        assert(length > 0);
        return elements[next(tail)];
    }

    void print() const noexcept {
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
        elements = nullptr;
        capacity = 0;
        length = 0;
        head = 0;
        tail = 0;
    }

    T operator[](int i) const {
        assert(i >= 0 && i < length);
        return elements[(tail + 1 + i) % capacity];
    }

    T &operator[](int i) {
        assert(i >= 0 && i < length);
        return elements[(tail + 1 + i) % capacity];
    }

private:
    T *elements;
    int length;
    int capacity;
    int tail;
    int head;

    int next(int i) const noexcept {
        return i + 1 == capacity ? 0 : i + 1;
    }

    int prev(int i) const noexcept {
        return i == 0 ? capacity - 1 : i - 1;
    }

    void resize(int newCapacity) {
        T *newElements = new T[newCapacity];
        int index = next(tail);
        for (int i = 0; i < length; i++) {
            newElements[i] = std::move(elements[index]);
            index = next(index);
        }
        delete[] elements;
        elements = newElements;
        capacity = newCapacity;
        tail = capacity - 1;
        head = length == capacity ? 0 : length;
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
};
#endif //ALGORITHMS_RINGBUFFER_H
