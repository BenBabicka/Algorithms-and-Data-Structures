//
// Created by Ben Babicka on 17/09/2026.
//

#ifndef ALGORITHMS_TREE_H
#define ALGORITHMS_TREE_H
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>


#include "Queue.h"

template<typename T>
class BTree {
    struct Node {
        using node = std::shared_ptr<Node>;
        using node_w = std::weak_ptr<Node>;
        T data;

        node left;
        node right;

        node_w parent;
        int height = 0;

        explicit Node(T aData) : data(std::move(aData)) {
        }

        template<typename... Args>
        static node makeNode(Args &&... args) {
            return std::make_shared<Node>(std::forward<Args>(args)...);
        }
    };

public:
    using node = std::shared_ptr<Node>;

    BTree() noexcept = default;

    BTree(const T aData) {
        root = Node::makeNode(aData);
    }

    BTree(const BTree &aOther) {
        if (aOther.root == nullptr)
            return;

        root = cloneNode(aOther.root, nullptr);
        std::vector<std::pair<node, node> > pending{{aOther.root, root}};
        while (!pending.empty()) {
            auto [source, copy] = pending.back();
            pending.pop_back();
            if (source->left) {
                copy->left = cloneNode(source->left, copy);
                pending.emplace_back(source->left, copy->left);
            }
            if (source->right) {
                copy->right = cloneNode(source->right, copy);
                pending.emplace_back(source->right, copy->right);
            }
        }
    }

    BTree(BTree &&aOther) noexcept : root(std::move(aOther.root)) {
    }

    BTree &operator=(BTree aOther) noexcept {
        swap(aOther);
        return *this;
    }

    ~BTree() {
        clear();
    }

    void swap(BTree &aOther) noexcept {
        std::swap(root, aOther.root);
    }

    void clear() noexcept {
        node current = std::move(root);
        while (current) {
            if (current->left) {
                node leftChild = std::move(current->left);
                current->left = std::move(leftChild->right);
                leftChild->right = std::move(current);
                current = std::move(leftChild);
            } else {
                node following = std::move(current->right);
                current = std::move(following);
            }
        }
    }

    void insert(const T aData) {
        node newNode = Node::makeNode(aData);
        if (root == nullptr) {
            root = newNode;
            return;
        }

        node current = root;
        while (true) {
            node &side = current->data < aData ? current->right : current->left;
            if (side == nullptr) {
                side = newNode;
                break;
            }
            current = side;
        }
        newNode->parent = current;
        newNode->height = current->height + 1;
    }

    T remove(const T aData) {
        node target = find(aData);
        if (target == nullptr)
            throw std::out_of_range("Item not found");

        T removed = target->data;
        if (target->left && target->right) {
            node successor = target->right;
            while (successor->left) {
                successor = successor->left;
            }
            target->data = successor->data;
            target = successor;
        }

        node child = target->left ? target->left : target->right;
        node parentNode = target->parent.lock();

        if (child) {
            child->parent = parentNode;
            shiftHeights(child, -1);
        }

        if (parentNode == nullptr) {
            root = child;
        } else if (parentNode->left == target) {
            parentNode->left = child;
        } else {
            parentNode->right = child;
        }
        return removed;
    }

    bool contains(const T &aData) const {
        return find(aData) != nullptr;
    }

    node breadth_first_search(T needle) const{
        Queue<node> q;
        if (root)
            q.enqueue(root);
        while (!q.empty()) {
            const node current = q.deque();

            if (current->data == needle) {
                return current;
            }

            if (current->left)
                q.enqueue(current->left);
            if (current->right)
                q.enqueue(current->right);
        }
        return nullptr;
    }

    // Depth first searches
    // N, L, R
    std::vector<node> pre_order_traversal() const {
        std::vector<node> path;
        pre_order_walk(root, path);
        return path;
    }

    // L, R, N
    std::vector<node> post_order_traversal() const {
        std::vector<node> path;
        post_order_walk(root, path);
        return path;
    }

    // L, N, R
    std::vector<node> in_order_traversal() const {
        std::vector<node> path;
        in_order_walk(root, path);
        return path;
    }

    bool operator==(const BTree &aOther) const {
        std::vector<std::pair<const Node *, const Node *> > pending;
        pending.emplace_back(root.get(), aOther.root.get());
        while (!pending.empty()) {
            const auto [a, b] = pending.back();
            pending.pop_back();

            if (a == nullptr && b == nullptr)
                continue;
            if (a == nullptr || b == nullptr)
                return false;
            if (a->data != b->data)
                return false;
            pending.emplace_back(a->left.get(), b->left.get());
            pending.emplace_back(a->right.get(), b->right.get());
        }
        return true;
    }

    node getRoot() const{
        if (root == nullptr)
            throw std::out_of_range("Root is null");
        return root;
    }

    void print() const {
        std::cout << "========================" << std::endl;
        std::cout << "BTree" << std::endl;
        for (const node &current: in_order_traversal()) {
            std::cout << "Level: " << current->height << ", Value: " << current->data << std::endl;
        }
        std::cout << "========================" << std::endl;
    }

private:
    node root;

    node find(const T &aData) const {
        node current = root;
        while (current) {
            if (aData < current->data) {
                current = current->left;
            } else if (current->data < aData) {
                current = current->right;
            } else {
                return current;
            }
        }
        return nullptr;
    }

    static node cloneNode(const node &aSource, const node &aParent) {
        node newNode = Node::makeNode(aSource->data);
        newNode->parent = aParent;
        newNode->height = aSource->height;
        return newNode;
    }

    static void pre_order_walk(const node &current, std::vector<node> &path) {
        if (current == nullptr)
            return;

        path.push_back(current);
        pre_order_walk(current->left, path);
        pre_order_walk(current->right, path);
    }

    static void in_order_walk(const node &current, std::vector<node> &path) {
        if (current == nullptr)
            return;

        in_order_walk(current->left, path);
        path.push_back(current);
        in_order_walk(current->right, path);
    }

    static void post_order_walk(const node &current, std::vector<node> &path) {
        if (current == nullptr)
            return;

        post_order_walk(current->left, path);
        post_order_walk(current->right, path);
        path.push_back(current);
    }

    static void shiftHeights(const node &aSubTree, const int aDelta) {
        std::vector<Node *> pending;
        pending.push_back(aSubTree.get());
        while (!pending.empty()) {
            Node *current = pending.back();
            pending.pop_back();
            current->height += aDelta;
            if (current->left)
                pending.push_back(current->left.get());
            if (current->right)
                pending.push_back(current->right.get());
        }
    }
};
#endif //ALGORITHMS_TREE_H
