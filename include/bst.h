// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <utility>
#include <string>
#include <algorithm>
#include <vector>

template <typename T>
class BST {
 private:
    struct Node {
        T val;
        int ocCount;
        Node* left;
        Node* right;
        explicit Node(const T& t) : val(t), ocCount(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* add(Node* n, const T& t) {
        if (!n) {
            return new Node(t);
        }

        if (t == n->val) {
            n->ocCount++;
            return n;
        }

        if (t < n->val) {
            n->left = add(n->left, t);
        } else {
            n->right = add(n->right, t);
        }

        return n;
    }

    int depthTree(Node* n) const {
        if (!n) return -1;
        int lDepth = depthTree(n->left);
        int rDepth = depthTree(n->right);
        return 1 + (lDepth > rDepth ? lDepth : rDepth);
    }

    void clear(Node* n) {
        if (!n) return;
        clear(n->left);
        clear(n->right);
        delete n;
    }

    void ord(Node* n, std::vector<std::pair<T, int>>& res) const {
        if (!n) return;
        ord(n->left, res);
        res.push_back({n->val, n->ocCount});
        ord(n->right, res);
    }

 public:
    BST() : root(nullptr) {}
    ~BST() { clear(root); }

    void insert(const T& value) {
        root = add(root, value);
    }

    int search(const T& value) const {
        Node* node = root;
        while (node) {
            if (value == node->val) {
                return node->ocCount;
            }
            if (value < node->val) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return 0;
    }

    int depth() const {
        return depthTree(root);
    }

    std::vector<std::pair<T, int>> toVector() const {
      std::vector<std::pair<T, int>> res;
      ord(root, res);
      return res;
    }
};
#endif  // INCLUDE_BST_H_
