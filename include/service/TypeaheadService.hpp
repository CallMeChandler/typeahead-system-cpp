#pragma once

#include <shared_mutex>
#include <vector>

#include "trie/Trie.hpp"
#include "repository/WordRepository.hpp"
#include "repository/AnalyticsRepository.hpp"

class TypeaheadService {
private:
    Trie trie;
    WordRepository words;
    AnalyticsRepository analytics;

    mutable std::shared_mutex mutex;

    void persistWord(const std::string& word);
    
public:
    TypeaheadService();

    std::vector<Suggestion> search(const std::string& prefix);

    void addWord(const std::string& word);

    void recordSelection(
        const std::string& query,
        const std::string& word
    );
};