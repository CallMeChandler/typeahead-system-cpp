#pragma once

#include <string>
#include <vector>
#include "models/Suggestion.hpp"

class TrieNode{
public:
    TrieNode* children[26];

    bool isEnd;
    int frequency;

    std::vector<Suggestion> topSuggestions;

    TrieNode();
};