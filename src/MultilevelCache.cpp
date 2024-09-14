#include<iostream>
#include "MultilevelCache.h"
using namespace std;
void MultilevelCache::addCacheLevel(int size, const string& evictionPolicy) {
    CacheLevel newLevel(size, evictionPolicy);
    levels.push_back(newLevel);
}

void MultilevelCache::removeCacheLevel(int level) {
    if (level >= 0 && level < levels.size()) {
        levels.erase(levels.begin() + level);
    }
}

string MultilevelCache::get(const string& key) {
    for (int i = 0; i < levels.size(); i++) {
        string value = levels[i].get(key);
        if (!value.empty()) {
            // Promote data to higher cache levels
            for (int j = i - 1; j >= 0; j--) {
                levels[j].put(key, value);
            }
            return value;
        }
    }
    // If not found, simulate fetching from memory
    string value = "FetchedFromMemory";
    put(key, value);
    return value;
}

void MultilevelCache::put(const string& key, const string& value) {
    if (!levels.empty()) {
        levels[0].put(key, value);
    }
}

void MultilevelCache::displayCache() {
    for (int i = 0; i < levels.size(); i++) {
        cout << "Cache Level " << i + 1 << ": ";
        for (const auto& [key, value] : levels[i].cache) {
            cout << "[" << key << ": " << value << "] ";
        }
        cout << endl;
    }
}
