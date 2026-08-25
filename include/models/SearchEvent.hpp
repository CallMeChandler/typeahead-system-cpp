#pragma once

#include <string>

struct SearchEvent {
    std::string query;
    std::string selectedWord;
    long timestamp;
};