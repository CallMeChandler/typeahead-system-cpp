#pragma once

#include <string>
#include "trie/TrieNode.hpp"

class Trie {
private:
    TrieNode* root;

public:
    Trie();

    void insert(const std::string& word);
    bool search(const std::string& word);
};