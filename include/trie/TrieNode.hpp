#pragma once

class TrieNode{
public:
    TrieNode* children[26];
    bool isEnd;
    int frequency;

    TrieNode();
};