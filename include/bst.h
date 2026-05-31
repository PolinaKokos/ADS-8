// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>

template <typename T>
class BST {
 public:
    struct Node {
        T key;
        int count;
        Node* left;
        Node* right;
        explicit Node(const T& val) : key(val), count(1), left(nullptr), right(nullptr) {}
    };

 private:
    Node* root;

    Node* insert(Node* node, const T& value) {
        if (node == nullptr) {
            return new Node(value);
        }
        if (value < node->key) {
            node->left = insert(node->left, value);
        } else if (value > node->key) {
            node->right = insert(node->right, value);
        } else {
            node->count++;
        }
        return node;
    }

    int depth(Node* node) const {
        if (node == nullptr) return 0;
        return 1 + std::max(depth(node->left), depth(node->right));
    }

    Node* search(Node* node, const T& value) const {
        if (node == nullptr || node->key == value) {
            return node;
        }
        if (value < node->key) {
            return search(node->left, value);
        }
        return search(node->right, value);
    }

    void clear(Node* node) {
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    void collectNodes(Node* node, Node* nodes[], int& index) {
        if (node == nullptr) return;
        collectNodes(node->left, nodes, index);
        nodes[index++] = node;
        collectNodes(node->right, nodes, index);
    }

    int getSize(Node* node) const {
        if (node == nullptr) return 0;
        return 1 + getSize(node->left) + getSize(node->right);
    }

 public:
    BST() : root(nullptr) {}

    ~BST() {
        clear(root);
    }

    void insert(const T& value) {
        root = insert(root, value);
    }

    int depth() const {
        return depth(root);
    }

    bool search(const T& value) const {
        return search(root, value) != nullptr;
    }

    int getCount(const T& value) const {
        Node* node = search(root, value);
        return node ? node->count : 0;
    }

    Node** getNodes(int& size) {
        if (root == nullptr) {
            size = 0;
            return nullptr;
        }
        size = getSize(root);
        Node** nodes = new Node*[size];
        int index = 0;
        collectNodes(root, nodes, index);
        return nodes;
    }

    int getSize() const {
        return getSize(root);
    }
};

#endif  // INCLUDE_BST_H_
