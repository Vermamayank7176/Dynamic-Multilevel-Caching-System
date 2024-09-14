#include "MultilevelCache.h"
#include "CacheLevel.h"
#include <iostream>

using namespace std;

int main() {
    MultilevelCache cache;
    
    // Test Case 1: Basic Insertion and Retrieval
    cout << "Test Case 1: Basic Insertion and Retrieval\n";
    cache.put("A", "1");
    cout << "Get A: " << cache.get("A") << "\n"; // Expected Output: 1

    // Test Case 2: Cache Miss
    cout << "Test Case 2: Cache Miss\n";
    cout << "Get B: " << cache.get("B") << "\n"; // Expected Output: null

    // Test Case 3: Eviction in L1 Cache
    cout << "Test Case 3: Eviction in L1 Cache\n";
    cache.addCacheLevel(3, "LRU");
    cache.put("A", "1");
    cache.put("B", "2");
    cache.put("C", "3");
    cache.put("D", "4"); // Should evict the least recently used item (A) in L1 if size of L1 is 3
    cout << "Get A: " << cache.get("A") << "\n"; // Expected Output: null
    cout << "Get B: " << cache.get("B") << "\n"; // Expected Output: 2

    // Test Case 4: Data Promotion from L2 to L1
    cout << "Test Case 4: Data Promotion from L2 to L1\n";
    cache.put("A", "1");
    cache.put("B", "2");
    cache.put("C", "3");
    cout << "Get A: " << cache.get("A") << "\n"; // Expected Output: 1

    // Test Case 5: Adding New Cache Level
    cout << "Test Case 5: Adding New Cache Level\n";
    cache.addCacheLevel(2, "LRU"); // Add L2 cache with size 2 and LRU policy
    cache.put("X", "10");
    cache.put("Y", "20");
    cache.put("Z", "30"); // Should evict the least recently used item in L2 if size of L2 is 2
    cout << "Get X: " << cache.get("X") << "\n"; // Expected Output: 10
    cout << "Get Y: " << cache.get("Y") << "\n"; // Expected Output: 20
    cout << "Get Z: " << cache.get("Z") << "\n"; // Expected Output: 30

    // Test Case 6: Removing a Cache Level
    cout << "Test Case 6: Removing a Cache Level\n";
    cache.removeCacheLevel(1); // Remove L1 cache
    cache.put("A", "1");
    cout << "Get A: " << cache.get("A") << "\n"; // Expected Output: null (L1 was removed)

    // Test Case 7: Verify Cache Contents After Removal
    cout << "Test Case 7: Verify Cache Contents After Removal\n";
    cache.displayCache(); // Expected Output: Only lower levels should be displayed

    // Test Case 8: Insert and Retrieve with LFU Policy
    cout << "Test Case 8: Insert and Retrieve with LFU Policy\n";
    cache.addCacheLevel(3, "LFU"); // Add L1 cache with size 3 and LFU policy
    cache.put("A", "1");
    cache.put("B", "2");
    cache.put("C", "3");
    cache.get("A");
    cache.put("D", "4"); // Should evict the least frequently used item in L1 if size of L1 is 3
    cout << "Get B: " << cache.get("B") << "\n"; // Expected Output: null (B should be evicted if it was the least frequently used)

    // Test Case 9: Dynamic Addition and Removal
    cout << "Test Case 9: Dynamic Addition and Removal\n";
    cache.addCacheLevel(2, "LRU"); // Add L1 cache with size 2 and LRU policy
    cache.put("A", "1");
    cache.put("B", "2");
    cache.addCacheLevel(3, "LFU"); // Add L2 cache with size 3 and LFU policy
    cache.put("C", "3");
    cout << "Get A: " << cache.get("A") << "\n";
    cache.removeCacheLevel(2); // Remove L2 cache
    cache.displayCache(); // Expected Output: Only L1 should be displayed

    // Test Case 10: Concurrency (Bonus)
    cout << "Test Case 10: Concurrency (Bonus)\n";
    // Assuming thread-safe implementation for concurrency
    cache.put("X", "10"); // Thread 1
    cout << "Get X: " << cache.get("X") << "\n"; // Thread 2: Expected Output: 10
    cache.put("Y", "20"); // Thread 1
    cout << "Get Y: " << cache.get("Y") << "\n"; // Thread 2: Expected Output: 20

    return 0;
}
