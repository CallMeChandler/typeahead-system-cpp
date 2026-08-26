#pragma once

#include <shared_mutex>
#include <vector>

#include "trie/Trie.hpp"
#include "repository/WordRepository.hpp"
#include "repository/AnalyticsRepository.hpp"
#include "middleware/RateLimiter.hpp"
#include "metrics/Metrics.hpp"

class TypeaheadService {
private:
    Trie trie;
    WordRepository words;
    AnalyticsRepository analytics;
    RateLimiter limiter;
    Metrics metrics;

    mutable std::shared_mutex mutex;

    void persistWord(const std::string& word);
    
public:
    TypeaheadService();

    std::vector<Suggestion> search(const std::string& prefix);

    void addWord(const std::string& word);

    bool canSearch(const std::string& clientId);

    void recordSelection(
        const std::string& query,
        const std::string& word
    );

    Metrics& getMetrics();
};