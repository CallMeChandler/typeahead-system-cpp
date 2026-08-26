#pragma once

#include <string>
#include <unordered_map>
#include <mutex>
#include <chrono>

struct ClientBucket {
    int tokens;
    std::chrono::steady_clock::time_point lastRefill;
};

class RateLimiter {
private:
    std::unordered_map<std::string, ClientBucket> buckets;
    
    std::mutex mutex;

    const int MAX_TOKENS = 20;
    const int REFILL_RATE = 5;
public:
    bool allowRequest(const std::string& clientId);
};