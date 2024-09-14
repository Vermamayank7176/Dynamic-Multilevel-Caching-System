#ifndef MULTILEVELCACHE_H
#define MULTILEVELCACHE_H

#include "CacheLevel.h"
#include <vector>

using namespace std;

class MultilevelCache {
public:
    void addCacheLevel(int size, const string& evictionPolicy);
    void removeCacheLevel(int level);
    string get(const string& key);
    void put(const string& key, const string& value);
    void displayCache();

private:
    vector<CacheLevel> levels;
};

#endif // MULTILEVELCACHE_H
