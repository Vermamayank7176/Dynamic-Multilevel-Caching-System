#include "CacheLevel.h"
#include <climits>

CacheLevel::CacheLevel(int size, string evictionPolicy)
    : size(size), evictionPolicy(evictionPolicy) {}

string CacheLevel::get(string key) {
    if (cache.find(key) != cache.end()) {
        if (evictionPolicy == "LRU") {
            accessOrder.remove(key);
            accessOrder.push_front(key);
        } else if (evictionPolicy == "LFU") {
            accessFreq[key]++;
        }
        return cache[key];
    }
    return "";
}

void CacheLevel::put(string key, string value) {
    if (cache.size() >= size) {
        evict();
    }
    cache[key] = value;
    if (evictionPolicy == "LRU") {
        accessOrder.push_front(key);
    } else if (evictionPolicy == "LFU") {
        accessFreq[key] = 1;
    }
}

void CacheLevel::evict() {
    if (evictionPolicy == "LRU") {
        string keyToEvict = accessOrder.back();
        accessOrder.pop_back();
        cache.erase(keyToEvict);
    } else if (evictionPolicy == "LFU") {
        string keyToEvict = getLFUKey();
        accessFreq.erase(keyToEvict);
        cache.erase(keyToEvict);
    }
}

string CacheLevel::getLFUKey() {
    string lfuKey;
    int minFreq = INT_MAX;
    for (auto &[key, freq] : accessFreq) {
        if (freq < minFreq) {
            minFreq = freq;
            lfuKey = key;
        }
    }
    return lfuKey;
}
