#pragma once

#include <string>
#include "models/SearchEvent.hpp"

class AnalyticsRepository {
private:
    std::string filePath;

public:
    explicit AnalyticsRepository(const std::string& path);

    void logEvent(const SearchEvent& event);
};