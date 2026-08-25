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
    void insert(const std::string& word, int frequency);

    bool search(const std::string& word);
    int getFrequency(const std::string& word);
    
    std::vector<Suggestion> startsWith(const std::string& prefix);
};