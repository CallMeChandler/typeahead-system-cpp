#pragma once

#include <string>
#include <vector>
#include "trie/TrieNode.hpp"

class Trie {
private:
    TrieNode* root;

    void collectWords(
        TrieNode* node,
        std::string currentWord,
        std::vector<std::string>& results
    );

public:
    Trie();

    void insert(const std::string& word);
    bool search(const std::string& word);
    
    std::vector<std::string> startsWith(const std::string& prefix);
};