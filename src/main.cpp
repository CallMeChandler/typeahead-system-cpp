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
    trie.insert("apple");

    std::cout << trie.search("cat") << '\n';
    std::cout << trie.search("car") << '\n';
    std::cout << trie.search("cap") << '\n';
    std::cout << trie.search("apple") << '\n';

    return 0;
}