#ifndef CACHE_LEVEL_H
#define CACHE_LEVEL_H

#include <unordered_map>
#include <list>
#include <string>

using namespace std;

class CacheLevel {
public:
    int size;
    string evictionPolicy;
    unordered_map<string, string> cache;
    list<string> accessOrder; 
    unordered_map<string, int> accessFreq;

    CacheLevel(int size, string evictionPolicy);
    string get(string key);
    void put(string key, string value);
    void evict();

private:
    string getLFUKey();
};

#endif
