#include "metrics/Metrics.hpp"

void Metrics::recordSearch()
{
    totalSearches.fetch_add(1);
}

void Metrics::recordInsertion()
{
    totalInsertions.fetch_add(1);
}

void Metrics::recordSelection()
{
    totalSelections.fetch_add(1);
}

void Metrics::setUniqueWords(std::size_t count)
{
    uniqueWords.store(count);
}

std::size_t Metrics::getTotalSearches() const
{
    return totalSearches.load();
}

std::size_t Metrics::getTotalInsertions() const
{
    return totalInsertions.load();
}

std::size_t Metrics::getTotalSelections() const
{
    return totalSelections.load();
}

std::size_t Metrics::getUniqueWords() const
{
    return uniqueWords.load();
}