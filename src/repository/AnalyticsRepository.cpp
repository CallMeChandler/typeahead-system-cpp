#include "repository/AnalyticsRepository.hpp"

#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

AnalyticsRepository::AnalyticsRepository(const std::string& path)
    : filePath(path) {}

void AnalyticsRepository::logEvent(const SearchEvent& event) {
    json data = json::array();

    std::ifstream input(filePath);

    if (input.is_open() && input.peek()!=std::ifstream::traits_type::eof()){
        input >> data;
    }

    json item;

    item["query"] = event.query;
    item["selectedWord"] = event.selectedWord;
    item["timestamp"] = event.timestamp;

    data.push_back(item);

    std::ofstream output(filePath);

    output << data.dump(4);
}