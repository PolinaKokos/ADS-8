// Copyright 2021 NNTU-CS
#include "../include/bst.h"
#include <iostream>
#include <chrono>
void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);
int main() {
    std::cout << "=== Word Frequency Analysis of 'War and Peace' ===" << std::endl;
    std::cout << "Loading and analyzing the text file..." << std::endl;
    BST<std::string> tree;
    auto start = std::chrono::high_resolution_clock::now();
    makeTree(tree, "src/war_peace.txt");
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Tree built successfully!" << std::endl;
    std::cout << "Time taken: " << duration.count() << " ms" << std::endl;
    std::cout << "Total unique words: " << tree.getSize() << std::endl;
    std::cout << "Tree depth: " << tree.depth() << std::endl;
    printFreq(tree);
    std::cout << "\n=== Search Examples ===" << std::endl;
    std::string testWords[] = {"war", "peace", "and", "the", "to", "of"};
    for (const auto& word : testWords) {
        int count = tree.getCount(word);
        std::cout << "Word '" << word << "' found " << count << " times" << std::endl;
    }
    return 0;
}
