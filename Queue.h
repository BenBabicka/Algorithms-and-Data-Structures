//
// Created by Ben Babicka on 14/09/2026.
//

#ifndef ALGORITHMS_QUEUE_H
#define ALGORITHMS_QUEUE_H
#include <iostream>
#include <ostream>
#include "Node.h"

template<typename T>
class Queue {
    using node = Node<T>::node;

public:
    Queue() noexcept = default;

    Queue(const Queue &aQueue) {
        for (node current = aQueue.head; current; current = current->next) {
            enqueue(current->data);
        }
    };

    Queue(Queue &&aQueue) noexcept : head(aQueue.head),
                                     tail(aQueue.tail),
                                     length(aQueue.length) {
        aQueue.head = aQueue.tail = nullptr;
        aQueue.length = 0;
    };

    Queue &operator=(Queue aQueue) noexcept {
        swap(aQueue);
        return *this;
    };

    ~Queue() noexcept {
        clear();
    };

    void swap(Queue &other) noexcept {
        std::swap(head, other.head);
        std::swap(tail, other.tail);
        std::swap(length, other.length);
    }

    void clear() noexcept {
        tail = nullptr;
        node current = std::move(head);
        while (current) {
            node following = std::move(current->next);
            current = std::move(following);
        }
        length = 0;
    }

    int getLength() const noexcept {
        return length;
    }

    T deque() {
        if (length == 0)
            throw std::logic_error("Queue is empty");
        length = std::max(0, length - 1);
        const node tempNode = head;

        if (length == 0) {
            head = nullptr;
            return tempNode->data;
        }

        head = head->next;

        return tempNode->data;
    }

    T peek() const {
        if (head == nullptr)
            throw std::logic_error("Queue is empty");

        return head->data;
    }

    void enqueue(const T &aData) noexcept {
        using nodeType = Node<T>;
        node newNode = nodeType::makeNode(aData);

        length++;

        if (length == 1) {
            tail = head = newNode;
            return;
        }

        tail->next = newNode;
        tail = newNode;
    }

    void print(bool printData = false) noexcept {
        std::cout << "=======================" << std::endl << "QUEUE" << std::endl << "=======================" <<
                std::endl;
        if (head == nullptr) {
            std::cout << "Empty Queue" << std::endl;
            return;
        }
        std::cout << "{" << std::endl;
        std::cout << "head: " << head->data << std::endl;
        std::cout << "tail: " << tail->data << std::endl;
        std::cout << "length: " << length << std::endl;
        node tempNode = head;
        std::cout << "  (" << tempNode->data << ")";
        if (printData) {
            std::cout << std::endl << "     {" << std::endl;
            std::cout << "      Index: " << 0 << std::endl;
            std::cout << "      Data: " << tempNode->data << std::endl;
            std::cout << "      This: " << tempNode << std::endl;
            std::cout << "      Next: " << tempNode->next << std::endl;
            std::cout << "      }";
        }
        for (int i = 1; i < length; i++) {
            tempNode = tempNode->next;
            std::cout << "," << std::endl << "  (" << tempNode->data << ")";
            if (printData) {
                std::cout << std::endl << "     {" << std::endl;
                std::cout << "      Index: " << i << std::endl;
                std::cout << "      Data: " << tempNode->data << std::endl;
                std::cout << "      This: " << tempNode << std::endl;
                std::cout << "      Next: " << tempNode->next << std::endl;
                std::cout << "      }";
            }
        }
        std::cout << std::endl << "}" << std::endl;
    }

    bool empty() const noexcept {
        return length == 0;
    }

private:
    node head;
    node tail;
    int length = 0;
};


#endif //ALGORITHMS_QUEUE_H
