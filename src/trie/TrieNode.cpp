#include "trie/TrieNode.hpp"

TrieNode::TrieNode() {
    for (int i = 0; i < 26; i++) {
        children[i] = nullptr;
    }

    isEnd = false;
}