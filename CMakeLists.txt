cmake_minimum_required(VERSION 3.20)

project(TypeaheadSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    crow
    GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
    GIT_TAG v1.3.3
)

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.12.0
)

FetchContent_MakeAvailable(crow json)

add_executable(typeahead
    src/main.cpp
    src/trie/TrieNode.cpp
    src/trie/Trie.cpp
    src/repository/WordRepository.cpp
    src/repository/AnalyticsRepository.cpp
    src/service/TypeaheadService.cpp
    src/middleware/RateLimiter.cpp
    src/metrics/Metrics.cpp
)

target_link_libraries(typeahead
    PRIVATE
    Crow::Crow
    nlohmann_json::nlohmann_json
)

target_include_directories(typeahead
    PRIVATE
    include
)