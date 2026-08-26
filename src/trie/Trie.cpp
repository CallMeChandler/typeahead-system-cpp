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

        updateTopSuggestions(
            current,
            word,
            current->frequency+1
        );
    }

    current->isEnd=true;
    current->frequency=frequency;
}

void Trie::updateTopSuggestions(
    TrieNode* node,
    const std::string& word,
    int frequency
)
{
    bool found = false;

    for (auto& item:node->topSuggestions){
        if (item.word==word){
            item.frequency=frequency;
            found=true;
            break;
        }
    }

    if (!found){
        node->topSuggestions.push_back({word, frequency});
    }

    std::sort(
        node->topSuggestions.begin(),
        node->topSuggestions.end(),
        [](const Suggestion& a, const Suggestion& b){
            return a.frequency<b.frequency;
        }
    );

    if (node->topSuggestions.size()>5){
        node->topSuggestions.resize(5);
    }
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

std::vector<Suggestion>
Trie::startsWith(const std::string& prefix)
{
    TrieNode* current = root;

    for (char ch : prefix) {

        int index = ch - 'a';

        if (current->children[index] == nullptr)
            return {};

        current = current->children[index];
    }

    return current->topSuggestions;
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