// Copyright 2021 NNTU-CS
#include "bst.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>

bool isWordChar(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

char toLowerChar(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return ch + ('a' - 'A');
    }
    return ch;
}

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return;
    }
    std::string word;
    char ch;
    while (file.get(ch)) {
        if (isWordChar(ch)) {
            word += toLowerChar(ch);
        } else {
            if (!word.empty()) {
                tree.insert(word);
            }
            word.clear();
        }
    }
    if (!word.empty()) {
        tree.insert(word);
    }
    file.close();
}

void sortNodesByFrequency(BST<std::string>::Node** nodes, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (nodes[j]->count < nodes[j + 1]->count) {
                std::swap(nodes[j], nodes[j + 1]);
            }
        }
    }
}

void printFreq(BST<std::string>& tree) {
    int size = 0;
    auto nodes = tree.getNodes(size);
    if (size == 0) {
        std::cout << "Tree is empty" << std::endl;
        return;
    }
    sortNodesByFrequency(nodes, size);
    std::ofstream outFile("result/freq.txt");
    if (!outFile) {
        std::cerr << "Error: Cannot create result/freq.txt" << std::endl;
    }
    std::cout << "\n=== Word Frequency Analysis ===" << std::endl;
    std::cout << "Total unique words: " << size << std::endl;
    std::cout << "Tree depth: " << tree.depth() << std::endl;
    std::cout << "\nTop 20 most frequent words:" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    int displayLimit = std::min(20, size);
    for (int i = 0; i < size; i++) {
        std::string line = nodes[i]->key + ": " + std::to_string(nodes[i]->count);
        if (i < displayLimit) {
            std::cout << line << std::endl;
        }
        if (outFile) {
            outFile << line << std::endl;
        }
    }
    if (outFile) {
        std::cout << "\nFull results saved to result/freq.txt" << std::endl;
        outFile.close();
    }
    delete[] nodes;
}
