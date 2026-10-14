//
// Created by Ben Babicka on 11/09/2026.
//

#ifndef ALGORITHMS_LINKEDLISTITERATOR_H
#define ALGORITHMS_LINKEDLISTITERATOR_H

#include <iostream>
#include <memory>
#include <ostream>
#include <stdexcept>
#include <utility>


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

    DoublyLinkedList(const DoublyLinkedList &other) {
        try {
            for (node current = other.head; current; current = current->next) {
                append(current->data);
            }
        } catch (...) {
            clear();
            throw;
        }
    }

    DoublyLinkedList(DoublyLinkedList &&other) noexcept : head(std::move(other.head)),
                                                          tail(std::move(other.tail)),
                                                          length(other.length) {
        other.length = 0;
    }

    DoublyLinkedList &operator=(DoublyLinkedList other) noexcept {
        swap(other);
        return *this;
    }

    ~DoublyLinkedList() {
        clear();
    }

    void swap(DoublyLinkedList &other) noexcept {
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

    void insertAt(T aData, const int aIndex) {
        if (aIndex < 0 || aIndex > length)
            throw std::out_of_range("Index out of range");

        if (aIndex == 0) {
            prepend(aData);
            return;
        }
        if (aIndex == length) {
            append(aData);
            return;
        }

        node newNode = Node::makeNode(std::move(aData));
        node currentNode = getAt(aIndex);
        node previousNode = currentNode->previous.lock();

        newNode->next = currentNode;
        newNode->previous = previousNode;
        currentNode->previous = newNode;
        previousNode->next = newNode;
        length++;
    }

    T remove(T aItem) {
        for (node current = head; current; current = current->next) {
            if (current->data == aItem) {
                return removeNode(current);
            }
        }
        throw std::out_of_range("Item not found");
    }

    T removeAt(const int aIndex) {
        if (aIndex < 0 || aIndex >= length)
            throw std::out_of_range("Index out of range");

        return removeNode(getAt(aIndex));
    }

    void append(const T &aData) {
        node newNode = Node::makeNode(aData);

        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            newNode->previous = tail;
            tail->next = newNode;
            tail = newNode;
        }
        length++;
    }

    void prepend(const T &aData) {
        node newNode = Node::makeNode(aData);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->previous = newNode;
            head = newNode;
        }
        length++;
    }

    const T &get(const int aIndex) const {
        if (aIndex < 0 || aIndex >= length)
            throw std::out_of_range("Index out of range");

        return getAt(aIndex)->data;
    }

    bool contains(const T &aData) const {
        for (node current = head; current; current = current->next) {
            if (current->data == aData) {
                return true;
            }
        }
        return false;
    }

    void print(const bool printData = false) const {
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

        std::cout << "  (" << head->data << ")";
        if (printData) {
            std::cout << std::endl << "     {" << std::endl;
            std::cout << "      Index: " << 0 << std::endl;
            std::cout << "      Data: " << head->data << std::endl;
            std::cout << "      This: " << head << std::endl;
            std::cout << "      Prev: " << head->previous.lock() << std::endl;
            std::cout << "      Next: " << head->next << std::endl;
            std::cout << "      }";
        }

        int i = 1;
        for (node current = head->next; current; current = current->next) {
            std::cout << "," << std::endl << "  (" << current->data << ")";
            if (printData) {
                std::cout << std::endl << "     {" << std::endl;
                std::cout << "      Index: " << i++ << std::endl;
                std::cout << "      Data: " << current->data << std::endl;
                std::cout << "      This: " << current << std::endl;
                std::cout << "      Prev: " << current->previous.lock() << std::endl;
                std::cout << "      Next: " << current->next << std::endl;
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
       T data = std::move(currentNode->data);

        if (currentNode == head) {
            head = currentNode->next;
        }
        if (currentNode == tail) {
            tail = currentNode->previous.lock();
        }

        currentNode->isolate();
        length--;

        return data;
    }
};


#endif //ALGORITHMS_LINKEDLISTITERATOR_H
