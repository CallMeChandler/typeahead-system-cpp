#pragma once

#include <string>
#include <vector>

#include "models/Suggestion.hpp"

class WordRepository{
private:
    std::string filePath;

public:
    explicit WordRepository(const std::string& filePath);

    std::vector<Suggestion> loadAll();
    void saveAll(const std::vector<Suggestion>& words);
};