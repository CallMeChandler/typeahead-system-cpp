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

    for(int i=0;i<5;i++) trie.insert("car");
    for(int i=0;i<3;i++) trie.insert("camera");
    for(int i=0;i<2;i++) trie.insert("cat");
    trie.insert("camp");

    auto suggestions = trie.startsWith("ca");

    for (const auto& s : suggestions) {
        std::cout << s.word << " : " << s.frequency << '\n';
    }
}