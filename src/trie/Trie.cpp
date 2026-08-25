#include "trie/Trie.hpp"

#include <algorithm>

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
    current->frequency++;
}

void Trie::insert(const std::string& word, int frequency){
    TrieNode* current = root;

    for (char ch:word){
        int index = ch-'a';

        if (current->children[index]==nullptr){
            current->children[index] = new TrieNode();
        }

        current = current->children[index];
    }

    current->isEnd=true;
    current->frequency=frequency;
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

std::vector<Suggestion> Trie::startsWith(const std::string& prefix) {
    TrieNode* current = root;
    std::vector<Suggestion> results;

    for (char ch : prefix) {
        int index = ch - 'a';

        if (current->children[index] == nullptr)
            return results;

        current = current->children[index];
    }

    collectWords(current, prefix, results);

    std::sort(results.begin(), results.end(),
        [](const Suggestion& a, const Suggestion& b) {
            return a.frequency > b.frequency;
        });

    if (results.size() > 5)
        results.resize(5);

    return results;
}

void Trie::collectWords(
    TrieNode* node,
    std::string currentWord,
    std::vector<Suggestion>& results
) {
    if (node->isEnd) {
        results.push_back({currentWord, node->frequency});
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

int Trie::getFrequency(const std::string& word){
    TrieNode* current = root;

    for (char ch:word){
        int index=ch-'a';

        if (current->children[index]==nullptr) return 0;

        current=current->children[index];
    }

    if (!current->isEnd){
        return 0;
    }

    return current->frequency;
}