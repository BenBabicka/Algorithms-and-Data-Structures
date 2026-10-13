//
// Created by Ben Babicka on 14/09/2026.
//

#ifndef ALGORITHMS_NODE_H
#define ALGORITHMS_NODE_H
#include <memory>

template<typename T>
struct Node {
    using node = std::shared_ptr<Node>;
    T data;
    node next;

    Node(const T &aData) noexcept : data(std::move(aData)) {
    }

    Node(T &&aData) noexcept : data(std::move(aData)) {
    }

    template<typename... Args>
    static node makeNode(Args &&... args) {
        return std::make_shared<Node>(std::forward<Args>(args)...);
    }
};
#endif //ALGORITHMS_NODE_H
