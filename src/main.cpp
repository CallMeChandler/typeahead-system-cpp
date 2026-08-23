// #include "crow.h"

// int main(){
//     crow::SimpleApp app;

//     CROW_ROUTE(app, "/health")
//     ([] {
//         return crow::response{
//             200,
//             R"({"status":"ok"})"
//         };
//     });

//     app.port(18080).multithreaded().run();

//     return 0;
// }

#include <iostream>
#include "trie/Trie.hpp"

int main() {
    Trie trie;

    trie.insert("cat");
    trie.insert("car");
    trie.insert("camera");
    trie.insert("camp");
    trie.insert("apple");

    auto words = trie.startsWith("ca");

    for (const auto& word : words) {
        std::cout << word << '\n';
    }

    return 0;
}