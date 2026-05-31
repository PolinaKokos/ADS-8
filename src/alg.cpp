// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "File ERR" << std::endl;
        return;
    }

    std::string cword;
    char cch;

    while (file.get(cch)) {
        if (std::isalpha(cch)) {
            cword += std::tolower(cch);
        } else if (!cword.empty()) {
            tree.insert(cword);
            cword.clear();
        }
    }

    if (!cword.empty()) {
        tree.insert(cword);
    }

    file.close();
}

void printFreq(BST<std::string>& tree) {
  auto wordsVec = tree.toVector();
  std::sort(wordsVec.begin(), wordsVec.end(),
            [](const auto& a, const auto& b) {
              return a.second > b.second;
            });
  std::ofstream out("result/freq.txt");
  for (const auto& pair : wordsVec) {
    std::cout << pair.first << " - " << pair.second << std::endl;
    out << pair.first << " - " << pair.second << std::endl;
  }
}
