#include "repository/WordRepository.hpp"

#include <fstream>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

WordRepository::WordRepository(const std::string& filePath)
    : filePath(filePath) {
}

std::vector<Suggestion> WordRepository::loadAll(){
    std::vector<Suggestion> words;

    std::ifstream file(filePath);

    if (!file.is_open()){
        return words;
    }

    json data;
    file >> data;

    for (const auto& item:data){
        Suggestion suggestion;

        suggestion.word=item["word"];
        suggestion.frequency=item["frequency"];

        words.push_back(suggestion);
    }

    return words;
}

void WordRepository::saveAll(const std::vector<Suggestion>& words){
    json data = json::array();

    for (const auto& suggestion : words){
        json item;

        item["word"]=suggestion.word;
        item["frequency"]=suggestion.frequency;

        data.push_back(item);
    }

    std::ofstream file(filePath);

    file << data.dump(4);
}