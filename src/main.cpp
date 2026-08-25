#include <iostream>

#include "crow.h"
#include "trie/Trie.hpp"
#include "repository/WordRepository.hpp"
#include "repository/AnalyticsRepository.hpp"
#include "models/SearchEvent.hpp"

#include <ctime>
#include <fstream>
#include <sstream>

std::string readFile(const std::string& path) {
    std::ifstream file(path);

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}


int main(){
    crow::SimpleApp app;

    Trie trie;

    WordRepository repository("../data/words.json");
    AnalyticsRepository analytics("../data/search_logs.json");

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

    CROW_ROUTE(app, "/select").methods("POST"_method)
    ([&trie, &repository, &analytics](const crow::request& req){
        auto body = crow::json::load(req.body);

        if (!body){
            return crow::response(
                400,
                R"({"error":"invalid json"})"
            );
        }

        std::string query = body["query"].s();
        std::string word = body["word"].s();
        
        if (query.empty() || word.empty()){
            return crow::response(
                400,
                R"({"error":"query and word required"})"
            );
        }

        trie.insert(word);

        int frequency = trie.getFrequency(word);

        auto words = repository.loadAll();

        bool found = false;

        for (auto& item:words){
            if (item.word==word){
                item.frequency=frequency;
                found=true;
                break;
            }
        }

        if (!found){
            words.push_back({word, frequency});
        }

        repository.saveAll(words);

        SearchEvent event{
            query,
            word,
            std::time(nullptr)
        };

        analytics.logEvent(event);

        crow::json::wvalue res;
        res["message"] = "selection recorded";
        res["frequency"] = frequency;

        return crow::response(200, res);
    });

    CROW_ROUTE(app, "/")([] {
        auto html = readFile("../frontend/index.html");

        crow::response res(html);
        res.set_header("Content-Type", "text/html");

        return res;
    });

    CROW_ROUTE(app, "/app.js")([] {
        auto js = readFile("../frontend/app.js");

        crow::response res(js);
        res.set_header("Content-Type", "application/javascript");

        return res;
    });

    app.port(18080).multithreaded().run();

    return 0;
}