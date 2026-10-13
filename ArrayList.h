//
// Created by Ben Babicka on 14/09/2026.
//

#ifndef ALGORITHMS_ARRAYLIST_H
#define ALGORITHMS_ARRAYLIST_H
#include <array>
#include <cassert>

template<typename T>
class ArrayList {
public:
    ArrayList() noexcept : elements(new T[0]), length(0), capacity(0) {
    };

    ArrayList(std::initializer_list<T> aInit) : length(aInit.size()),
                                                capacity(aInit.size()),
                                                elements(new T[aInit.size()]) {
        int i = 0;
        for (const T &val: aInit) {
            elements[i++] = val;
        }
    };

    T operator[](int i) const {
        assert(i >= 0 && i < length);
        return elements[i];
    }

    T &operator[](int i) {
        assert(i >= 0 && i < length);
        return elements[i];
    }

    void operator=(std::initializer_list<T> value) {
        delete[] elements;

        elements = new T[value.size()];
        capacity = std::max(1, static_cast<int>(value.size()));
        length = value.size();

        int i = 0;
        for (const T &val: value) {
            elements[i++] = val;
        }
    }

    int getLength() const {
        return length;
    }

    int getCapacity() const {
        return capacity;
    }

    void push(T item) {
        ensureCapacity();
        elements[length] = item;
        length++;
    }

    T pop() {
        if (length == 0)
            throw std::out_of_range("ArrayList is empty");
        length--;
        const T val = elements[length];
        adjustCapacity();
        return val;
    }

    void unshift(T item) {
        ensureCapacity();
        for (int i = length; i > 0; i--) {
            elements[i] = elements[i - 1];
        }

        elements[0] = item;
        length++;
    }

    T shift() {
        if (length == 0)
            throw std::out_of_range("ArrayList is empty");

        const T val = elements[0];
        for (int i = 0; i < length - 1; i++) {
            elements[i] = elements[i + 1];
        }
        length--;
        adjustCapacity();
        return val;
    }

    void print() {
        std::cout << "Capacity: " << getCapacity() << std::endl;
        std::cout << "Length: " << getLength() << std::endl;
        if (length == 0) {
            std::cout << "[]" << std::endl;
            return;
        }
        std::cout << "[";
        std::cout << elements[0];
        for (int i = 1; i < getLength(); i++) {
            std::cout << ", " << elements[i];
        }
        std::cout << "]" << std::endl;
    }

private:
    T *elements;
    int length;
    int capacity;

    void resize(int newCapacity) {
        T *newElements = new T[newCapacity];
        for (int i = 0; i < length; i++) {
            newElements[i] = elements[i];
        }
        delete[] elements;
        elements = newElements;
        capacity = newCapacity;
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
#endif //ALGORITHMS_ARRAYLIST_H
