#include "service/TypeaheadService.hpp"

#include <ctime>
#include <mutex>

TypeaheadService::TypeaheadService()
    : words("../data/words.json"),
      analytics("../data/search_logs.json")
{
    auto stored = words.loadAll();

    for (const auto& item : stored) {
        trie.insert(item.word, item.frequency);
    }

    metrics.setUniqueWords(stored.size());
}

std::vector<Suggestion>
TypeaheadService::search(const std::string& prefix)
{
    std::shared_lock lock(mutex);

    metrics.recordSearch();

    return trie.startsWith(prefix);
}

Metrics& TypeaheadService::getMetrics()
{
    return metrics;
}

void TypeaheadService::addWord(const std::string& word)
{
    std::unique_lock lock(mutex);

    trie.insert(word);

    persistWord(word);

    metrics.recordInsertion();
}

void TypeaheadService::persistWord(const std::string& word)
{
    int frequency = trie.getFrequency(word);

    auto all = words.loadAll();

    bool found = false;

    for (auto& item : all) {
        if (item.word == word) {
            item.frequency = frequency;
            found = true;
            break;
        }
    }

    if (!found) {
        all.push_back({word, frequency});
    }

    words.saveAll(all);

    metrics.setUniqueWords(all.size());
}

bool TypeaheadService::canSearch(const std::string& clientId)
{
    return limiter.allowRequest(clientId);
}

void TypeaheadService::recordSelection(
    const std::string& query,
    const std::string& word)
{
    std::unique_lock lock(mutex);

    trie.insert(word);

    persistWord(word);

    SearchEvent event{
        query,
        word,
        std::time(nullptr)
    };

    analytics.logEvent(event);

    metrics.recordSelection();
}