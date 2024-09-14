#include "MultilevelCache.h"
#include <iostream>

using namespace std;

int main() {
    MultilevelCache cacheSystem;

    // Add L1 and L2 cache levels
    cacheSystem.addCacheLevel(3, "LRU");
    cacheSystem.addCacheLevel(2, "LFU");

    // Insert and access data
    cacheSystem.put("A", "1");
    cacheSystem.put("B", "2");
    cacheSystem.put("C", "3");
    cout << "Get A: " << cacheSystem.get("A") << endl; // L1 hit
    cacheSystem.put("D", "4"); // LRU eviction on L1
    cacheSystem.get("C"); // Fetches from L2 and promotes to L1

    // Display cache contents
    cacheSystem.displayCache();

    return 0;
}
