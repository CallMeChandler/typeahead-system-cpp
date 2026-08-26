#pragma once

#include <atomic>
#include <cstddef>

class Metrics {
private:
    std::atomic<std::size_t> totalSearches{0};
    std::atomic<std::size_t> totalInsertions{0};
    std::atomic<std::size_t> totalSelections{0};

    std::atomic<std::size_t> uniqueWords{0};

public:
    void recordSearch();
    void recordInsertion();
    void recordSelection();

    void setUniqueWords(std::size_t count);

    std::size_t getTotalSearches() const;
    std::size_t getTotalInsertions() const;
    std::size_t getTotalSelections() const;
    std::size_t getUniqueWords() const;
};