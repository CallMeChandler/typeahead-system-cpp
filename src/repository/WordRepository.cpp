#include "repository/WordRepository.hpp"

#include <fstream>
#include <stdexcept>

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

    if (file.peek()==std::ifstream::traits_type::eof()){
        return words;
    }

    json data;
    
    try{
        file >> data;
    }
    catch (const json::parse_error& e){
        throw std::runtime_error(
                "Invalid JSON in words file: " + std::string(e.what())
            );
    }

    if (!data.is_array()) {
        throw std::runtime_error(
            "Invalid words file: expected a JSON array"
        );
    }
    

    for (const auto& item : data) {

        if (!item.contains("word") ||
            !item.contains("frequency")) {
            throw std::runtime_error(
                "Invalid words file: missing word or frequency"
            );
        }

        Suggestion suggestion;

        suggestion.word = item["word"];
        suggestion.frequency = item["frequency"];

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