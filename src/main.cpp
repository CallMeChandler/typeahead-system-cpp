#include <iostream>

#include "crow.h"
#include "trie/Trie.hpp"
#include "repository/WordRepository.hpp"


int main(){
    crow::SimpleApp app;

    Trie trie;

    WordRepository repository("../data/words.json");

    auto words = repository.loadAll();

    for (const auto& word : words) {
        trie.insert(word.word, word.frequency);
    }

    CROW_ROUTE(app, "/health")
    ([]{
        return crow::response(
            200,
            R"({"status":"ok"})"
        );
    });

    CROW_ROUTE(app, "/search")
    ([&trie](const crow::request& req){
        const auto& queryParams = req.url_params;
        
        const char* query = queryParams.get("q");

        if (query==nullptr||query[0]=='\0'){
            return crow::response(
                400,
                R"({"error":"missing query parameter"})"
            );
        }

        auto suggestions = trie.startsWith(query);

        crow::json::wvalue response;

        size_t index = 0;

        for (const auto& suggestion : suggestions) {
            crow::json::wvalue item;

            item["word"] = suggestion.word;
            item["frequency"] = suggestion.frequency;

            response["suggestions"][index++] = std::move(item);
        }

        return crow::response(response);
    });

    CROW_ROUTE(app, "/words").methods("POST"_method)
    ([&trie, &repository](const crow::request& req) {

        auto body = crow::json::load(req.body);

        if (!body) {
            return crow::response(400, R"({"error":"invalid json"})");
        }

        std::string word = body["word"].s();

        if (word.empty()) {
            return crow::response(400, R"({"error":"word required"})");
        }

        trie.insert(word);

        int frequency = trie.getFrequency(word);

        auto words = repository.loadAll();

        bool found = false;

        for (auto& item : words) {
            if (item.word == word) {
                item.frequency = frequency;
                found = true;
                break;
            }
        }

        if (!found) {
            words.push_back({word, frequency});
        }

        repository.saveAll(words);

        crow::json::wvalue response;
        response["message"] = "word inserted";
        response["frequency"] = frequency;

        return crow::response(201, response);
    });

    app.port(18080).multithreaded().run();

    return 0;
}