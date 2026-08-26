#include "crow.h"

#include "service/TypeaheadService.hpp"

#include <fstream>
#include <sstream>

std::string readFile(const std::string& path) {
    std::ifstream file(path);

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

int main() {

    crow::SimpleApp app;

    TypeaheadService service;

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

    CROW_ROUTE(app, "/health")([] {
        return crow::response(200, R"({"status":"ok"})");
    });

    CROW_ROUTE(app, "/search")
    ([&service](const crow::request& req) {

        std::string client = req.remote_ip_address;

        if (!service.canSearch(client)) {

            return crow::response(
                429,
                R"({"error":"rate limit exceeded"})"
            );
        }

        const char* query = req.url_params.get("q");

        if (query == nullptr || query[0] == '\0') {
            return crow::response(
                400,
                R"({"error":"missing query parameter"})"
            );
        }

        auto suggestions = service.search(query);

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
    ([&service](const crow::request& req) {

        auto body = crow::json::load(req.body);

        if (!body) {
            return crow::response(
                400,
                R"({"error":"invalid json"})"
            );
        }

        std::string word = body["word"].s();

        if (word.empty()) {
            return crow::response(
                400,
                R"({"error":"word required"})"
            );
        }

        service.addWord(word);

        crow::json::wvalue response;
        response["message"] = "word inserted";

        return crow::response(201, response);
    });

    CROW_ROUTE(app, "/select").methods("POST"_method)
    ([&service](const crow::request& req) {

        auto body = crow::json::load(req.body);

        if (!body) {
            return crow::response(
                400,
                R"({"error":"invalid json"})"
            );
        }

        std::string query = body["query"].s();
        std::string word = body["word"].s();

        if (query.empty() || word.empty()) {
            return crow::response(
                400,
                R"({"error":"query and word required"})"
            );
        }

        service.recordSelection(query, word);

        crow::json::wvalue response;
        response["message"] = "selection recorded";

        return crow::response(200, response);
    });

    app.port(18080).multithreaded().run();

    return 0;
}