#include "middleware/RateLimiter.hpp"

bool RateLimiter::allowRequest(const std::string& clientId)
{
    std::lock_guard<std::mutex> lock(mutex);

    auto now = std::chrono::steady_clock::now();

    auto& bucket = buckets[clientId];

    if (bucket.lastRefill.time_since_epoch().count()==0){
        bucket.tokens=MAX_TOKENS;
        bucket.lastRefill=now;
    }
    
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(
        now - bucket.lastRefill
    ).count();

    if (elapsed > 0) {

        int refill = elapsed * REFILL_RATE;

        bucket.tokens = std::min(
            MAX_TOKENS,
            bucket.tokens + refill
        );

        bucket.lastRefill = now;
    }

    if (bucket.tokens == 0) {
        return false;
    }

    bucket.tokens--;

    return true;
}