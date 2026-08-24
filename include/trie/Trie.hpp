#pragma once

#include <string>
#include <vector>
#include "trie/TrieNode.hpp"
#include "models/Suggestion.hpp"

class Trie {
private:
    TrieNode* root;

    void collectWords(
        TrieNode* node,
        std::string currentWord,
        std::vector<Suggestion>& results
    );

public:
    Trie();

    void insert(const std::string& word);
    bool search(const std::string& word);
    
    std::vector<Suggestion> startsWith(const std::string& prefix);
};