//
// Created by Ben Babicka on 11/09/2026.
//

#ifndef ALGORITHMS_LINKEDLISTITERATOR_H
#define ALGORITHMS_LINKEDLISTITERATOR_H

#include <cassert>
#include <iostream>
#include <ostream>

#include <memory>

template<typename T>
class DoublyLinkedList {
    struct Node {
        using node = std::shared_ptr<Node>;
        using node_w = std::weak_ptr<Node>;

        T data;
        node next;
        node_w previous;

        Node(const T aData) noexcept : data(std::move(aData)) {
        }

        void link(node aPrevious, node aNext) noexcept {
            next = std::move(aNext);
            previous = std::move(aPrevious);
        }

        void isolate() noexcept {
            // Check if current node has a next node
            // If it does set the next node's previous to this current node's previous
            if (next)
                next->previous = previous;
            // Check if current node has a previous node
            // if it does sent the previous node next to this current node's next
            node iNode = previous.lock();
            if (iNode)
                iNode->next = next;

            //Clear the previous nodes
            previous.reset();
            next.reset();
        }

        template<typename... Args>
        static node makeNode(Args &&... args) {
            return std::make_shared<Node>(std::forward<Args>(args)...);
        }
    };

public:
    using node = std::shared_ptr<Node>;

    DoublyLinkedList() noexcept = default;

    int getLength() const noexcept {
        return length;
    }

    void insertAt(T aData, const int aIndex) {
        assert(aIndex >= 0 && aIndex <= length);

        if (aIndex == 0) {
            prepend(aData);
            return;
        }
        if (aIndex == length) {
            append(aData);
            return;
        }

        length++;

        node newNode = Node::makeNode(aData);
        node currentNode = getAt(aIndex);

        newNode->next = currentNode;
        newNode->previous = currentNode->previous.lock();
        currentNode->previous = newNode;
        if (newNode->previous.lock() != nullptr) {
            newNode->previous.lock()->next = newNode;
        }
    }

    T remove(T aItem) {
        node currentNode = head;
        for (int i = 0; i < length; i++) {
            if (currentNode->data == aItem) {
                break;
            }
            currentNode = currentNode->next;
        }
        return removeNode(currentNode);
    }

    T removeAt(const int aIndex) {
       return removeNode(getAt(aIndex));
    }

    void append(const T &aData) {
        node newNode = Node::makeNode(aData);
        length++;
        if (tail == nullptr) {
            head = tail = newNode;
            return;
        }
        newNode->previous = tail;
        tail->next = newNode;
        tail = newNode;
    }

    void prepend(const T &aData) {
        node newNode = Node::makeNode(aData);
        length++;
        if (head == nullptr) {
            head = tail = newNode;
            return;
        }
        newNode->next = head;
        head->previous = newNode;
        head = newNode;
    }

    node get(const int aIndex) const {
        assert(aIndex >= 0 && aIndex < length);
        node currentNode = getAt(aIndex);
        if (!currentNode) {
            return nullptr;
        }
        return currentNode->data;
    }

    void print(const bool printData = false) {
        std::cout << "=======================" << std::endl << "Linked List" << std::endl << "======================="
                << std::endl;
        if (head == nullptr) {
            std::cout << "Empty Linked List" << std::endl;
            return;
        }
        std::cout << "{" << std::endl;
        std::cout << "head: " << head->data << std::endl;
        std::cout << "tail: " << tail->data << std::endl;
        std::cout << "length: " << length << std::endl;

        node tempNode = getAt(0);
        std::cout << "  (" << tempNode->data << ")";
        if (printData) {
            std::cout << std::endl << "     {" << std::endl;
            std::cout << "      Index: " << 0 << std::endl;
            std::cout << "      Data: " << tempNode->data << std::endl;
            std::cout << "      This: " << tempNode << std::endl;
            std::cout << "      Prev: " << tempNode->previous.lock() << std::endl;
            std::cout << "      Next: " << tempNode->next << std::endl;
            std::cout << "      }";
        }

        for (int i = 1; i < length; i++) {
            tempNode = getAt(i);
            std::cout << "," << std::endl << "  (" << tempNode->data << ")";
            if (printData) {
                std::cout << std::endl << "     {" << std::endl;
                std::cout << "      Index: " << i << std::endl;
                std::cout << "      Data: " << tempNode->data << std::endl;
                std::cout << "      This: " << tempNode << std::endl;
                std::cout << "      Prev: " << tempNode->previous.lock() << std::endl;
                std::cout << "      Next: " << tempNode->next << std::endl;
                std::cout << "      }";
            }
        }
        std::cout << std::endl << "}" << std::endl;
    }

private:
    node head;
    node tail;
    int length = 0;

    node getAt(int aIndex) const {
        node current = head;
        for (int i = 0; current && i < aIndex; i++) {
            current = current->next;
        }
        return current;
    }

    T removeNode(node currentNode) {
        if (!currentNode) {
            return nullptr;
        }
        const T data = currentNode->data;

        length--;
        if (length == 0) {
            head = tail = nullptr;
            return currentNode->data;
        }
        if (currentNode == head) {
            head = currentNode->next;
        }
        if (currentNode == tail) {
            tail = currentNode->previous.lock();
        }
        currentNode->isolate();
        currentNode = nullptr;

        return data;
    }
};


#endif //ALGORITHMS_LINKEDLISTITERATOR_H
