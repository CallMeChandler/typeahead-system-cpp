#include "trie/Trie.hpp"

Trie::Trie() {
    root = new TrieNode();
}

void Trie::insert(const std::string& word) {
    TrieNode* current = root;

    for (char ch : word) {
        int index = ch - 'a';

        if (current->children[index] == nullptr) {
            current->children[index] = new TrieNode();
        }

        current = current->children[index];
    }

    current->isEnd = true;
}

bool Trie::search(const std::string& word) {
    TrieNode* current = root;

    for (char ch : word) {
        int index = ch - 'a';

        if (current->children[index] == nullptr) {
            return false;
        }

        current = current->children[index];
    }

    return current->isEnd;
}

std::vector<std::string> Trie::startsWith(const std::string& prefix){
    TrieNode* current = root;
    std::vector<std::string> results;

    for (char ch:prefix){
        int index = ch-'a';

        if (current->children[index]==nullptr){
            return results;
        }

        current = current->children[index];
    }

    collectWords(current, prefix, results);

    return results;
}

void Trie::collectWords(
    TrieNode* node,
    std::string currentWord,
    std::vector<std::string>& results
) {
    if (node->isEnd){
        results.push_back(currentWord);
    }

    for (int i = 0; i < 26; i++){
        if (node->children[i]!=nullptr){
            char nextChar = 'a'+i;

            collectWords(
                node->children[i],
                currentWord+nextChar,
                results
            );  
        }
    }
}