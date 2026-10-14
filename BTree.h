//
// Created by Ben Babicka on 17/09/2026.
//

#ifndef ALGORITHMS_TREE_H
#define ALGORITHMS_TREE_H
#include <format>
#include <memory>
#include <queue>
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

    BTree() noexcept {
    }

    BTree(const T aData) noexcept {
        node n = Node::makeNode(aData);
        n->height = 0;
        root = n;
    }

    void insert(const T aData) {
        if (root == nullptr) {
            root = Node::makeNode(aData);
            root->height = 0;
            return;
        }
        insertInOrder(root, aData);
    }

    T remove(const T aData) {
        node foundNode = breadth_first_search(aData);
        if (foundNode == nullptr) {
            return T{};
        }
        const T data = foundNode->data;
        bool isLeft = foundNode->parent->left == foundNode;
        if (foundNode->left == nullptr && foundNode->right == nullptr) {
            if (isLeft) {
                foundNode->parent->left = nullptr;
            } else {
                foundNode->parent->right = nullptr;
            }
            std::cout << isLeft << std::endl;
            foundNode->isolate();
        }
        if (foundNode->left == nullptr || foundNode->right == nullptr) {
            node child = foundNode->left ? foundNode->left : foundNode->right;
            node leftChild = foundNode->left ? foundNode->left : nullptr;
            node rightChild = foundNode->right ? foundNode->right : nullptr;
            while (leftChild || rightChild) {
                if (leftChild) {
                    leftChild->height = leftChild->height - 1;
                    leftChild = leftChild->left;
                }
                if (rightChild) {
                    rightChild->height = rightChild->height - 1;
                    rightChild = rightChild->right;
                }
            }
            if (isLeft) {
                foundNode->parent->left = child;
            } else {
                foundNode->parent->right = child;
            }
        } else {
            // Check which side goes the deepest
            int side = 0;

            node leftNode = foundNode->left;
            node rightNode = foundNode->right;
            node deepestNode;

            while (leftNode || rightNode) {
                if (rightNode) {
                    side--;
                    deepestNode = rightNode;
                    rightNode = rightNode->left;
                }
                if (leftNode) {
                    side++;
                    deepestNode = leftNode;
                    leftNode = leftNode->right;
                }
            }
            std::cout << aData << std::endl;
            std::cout << side << std::endl;
            std::cout << deepestNode->data << std::endl;
            // Side >= 0 is left side
            // Side < 0 is right side
            if (side >= 0) {
                if (deepestNode->left) {
                    deepestNode->parent->right = deepestNode->left;
                    deepestNode->right->parent = deepestNode->parent;
                } else {
                    deepestNode->parent->right = nullptr;
                }
            } else {
                if (deepestNode->right) {
                    deepestNode->parent->left = deepestNode->right;
                    deepestNode->left->parent = deepestNode->parent;
                } else {
                    deepestNode->parent->left = nullptr;
                }
            }
            deepestNode->height = foundNode->height;
            deepestNode->parent = foundNode->parent;
            deepestNode->right = foundNode->right;
            deepestNode->left = foundNode->left;
            if (leftNode) deepestNode->parent->left = deepestNode;
            else deepestNode->parent->right = deepestNode;
        }
        foundNode->isolate();
        foundNode = nullptr;
        return data;
    }

    node breadth_first_search(T needle) {
        Queue<node> q;
        q.enqueue(root);
        while (!q.empty()) {
            const node current = q.deque();
            if (!current)
                continue;
            if (current->data == needle) {
                return current;
            }
            q.enqueue(current->left);
            q.enqueue(current->right);
        }
        return nullptr;
    }

    std::vector<node> pre_order_traversal() {
        return pre_order_walk(root, std::vector<node>());
    }

    std::vector<node> post_order_walk() {
        return post_order_walk(root, std::vector<node>());
    }

    std::vector<node> in_order_walk() {
        return in_order_walk(root, std::vector<node>());
    }

    bool operator==(const BTree &aOther) {
        compare(root, aOther.root);
    }

    node getRoot() {
        assert(root != nullptr);
        return root;
    }

    void print() {
        //if (mode == 0) {
        //    std::vector<node> path = pre_order_walk(root, std::vector<node>());
        //}
        //else if (mode == 1) {
        std::cout << "========================" << std::endl;
        std::cout << "BTree" << std::endl;
        std::vector<node> path = in_order_walk(root, std::vector<node>());
        std::cout << "========================" << std::endl;

        //}
        //else {
        //    std::vector<node> path = post_order_walk(root, std::vector<node>());
        //}
    }

private:
    node root;

    std::vector<node> pre_order_walk(node current, std::vector<node> path) {
        if (current == nullptr) {
            return path;
        }
        std::cout << "Level: " << current->height << ", Value: " << current->data << std::endl;
        path.push_back(current);
        pre_order_walk(current->left, path);
        pre_order_walk(current->right, path);
        return path;
    }

    std::vector<node> in_order_walk(node current, std::vector<node> path) {
        if (current == nullptr) {
            return path;
        }

        in_order_walk(current->left, path);
        std::cout << "Level: " << current->height << ", Value: " << current->data << std::endl;
        path.push_back(current);
        in_order_walk(current->right, path);

        return path;
    }

    std::vector<node> post_order_walk(node current, std::vector<node> path) {
        if (current == nullptr) {
            return path;
        }

        post_order_walk(current->left, path);
        post_order_walk(current->right, path);
        std::cout << "Level: " << current->height << ", Value: " << current->data << std::endl;
        path.push_back(current);

        return path;
    }

    void insertInOrder(node n, T aData, node parent = nullptr) {
        if (n == nullptr) {
            node newNode = Node::makeNode(aData);
            newNode->parent = parent;
            if (parent && parent->data < aData) {
                parent->right = newNode;
                newNode->parent = parent;
                newNode->height = parent->height + 1;
                return;
            } else if (parent && parent->data >= aData) {
                parent->left = newNode;
                newNode->height = parent->height + 1;
                newNode->parent = parent;
                return;
            }
        }
        if (n->data < aData)
            insertInOrder(n->right, aData, n);
        else if (n->data >= aData)
            insertInOrder(n->left, aData, n);
    }

    bool compare(node &a, node &b) {
        if (a == nullptr && b == nullptr)
            return true;

        if (a == nullptr || b == nullptr)
            return false;

        if (a->data != b->data)
            return false;

        return compare(a->left, b->left) && compare(a->right, b->right);
    }
};
#endif //ALGORITHMS_TREE_H
