/*
 * Problem Link: https://leetcode.cn/problems/lru-cache/
 * Problem Name: 146. LRU Cache
 * Difficulty: Medium
 * Problem Tags: design, hash table, linked list, doubly-linked list
 *
 * Submission Record:
 * Approach: Unordered map + STL list of keys
 * Language: C++
 * Status: Accepted
 * Submitted At: N/A
 * Runtime: 19 ms (beats 65.71%)
 * Memory: 46.97 MB (beats 74.77%)
 * Submission Link:
 * N/A
 * Recorded On: 2026-10-12
 * Record Source: User-provided accepted-submission screenshot
 *
 * Problem Description:
 * Implement a cache with a fixed positive capacity and a least recently
 * used (LRU) eviction policy.
 *
 * Interface:
 * LRUCache(capacity): Initialize an empty cache with the given capacity.
 * get(key): Return the stored value, or -1 if the key is absent.
 * put(key, value): Update an existing key or insert a new key-value pair.
 * If an insertion exceeds capacity, evict the least recently used key.
 * Successful reads, updates, and insertions refresh the usage order.
 * Both get() and put() must run in O(1) average time.
 *
 * Constraints:
 * 1. 1 <= capacity <= 3000
 * 2. 0 <= key <= 10000
 * 3. 0 <= value <= 100000
 * 4. At most 200000 calls are made to get() and put().
 *
 * Example:
 * Operations:
 * ["LRUCache","put","put","get","put","get","put","get","get","get"]
 * Arguments:
 * [[2],[1,1],[2,2],[1],[3,3],[2],[4,4],[1],[3],[4]]
 * Output:
 * [null,null,null,1,null,-1,null,-1,3,4]
 *
 * Note:
 * The local main() runs the official example directly.
 * null represents a constructor or put() call with no return value.
 *
 * Approach:
 * Store keys in an STL list, most recently used at the front and least
 * recently used at the back. The unordered map stores each key's value
 * and an iterator to its list node.
 * Successful reads and updates move the existing node to the front with
 * splice(), which preserves the stored iterator. New keys get a front
 * node. When full, erase the back key from the map, remove its list node,
 * and insert the new key. size grows only until capacity is reached;
 * replacements do not change the number of cached entries.
 *
 * Complexity:
 * Let c be capacity and k <= c be the number of cached entries.
 * Constructing empty containers takes O(1) time. Single-node list insert,
 * removal, and splice take O(1) time. Hash-table lookup, insertion, and
 * erasure take average O(1) time; insertion may trigger rehashing.
 * Thus get() and put() take average/amortized O(1) time, with O(k)
 * worst-case time for a single operation. The map and list store at most
 * c entries each, using O(c) auxiliary space including hash buckets.
 */

#include <cstdio>
#include <list>
#include <unordered_map>
#include <utility>

using namespace std;

struct Data {
    int value;
    list<int>::iterator lit;  // Position of this key in the recency list.
};

class LRUCache {
private:
    int capacity;
    int size;
    // O(c) dynamic storage across the map and list; each instance owns both.
    unordered_map<int, Data> table;
    list<int> entries;  // Front: most recent; back: least recent.

public:
    // O(1): the map and list are default-constructed empty.
    LRUCache(int capacity) {
        this->capacity = capacity;
        size = 0;
    }

    int get(int key) {
        // Average O(1) lookup; a miss does not insert a map entry.
        auto it = table.find(key);
        if (it == table.end()) return -1;

        // O(1) move; the iterator stored in the map remains valid.
        entries.splice(entries.begin(), entries, it->second.lit);
        return it->second.value;
    }

    // Average/amortized O(1); worst-case O(k) for hash-table operations.
    void put(int key, int value) {
        auto it = table.find(key);

        if (it != table.end()) {
            it->second.value = value;
            entries.splice(entries.begin(), entries, it->second.lit);
            return;
        }

        // O(1) list insertion plus average/amortized O(1) map insertion.
        if (size < capacity) {
            entries.push_front(key);
            table[key] = {value, entries.begin()};
            size++;
            return;
        }

        // Average O(1) map erasure and O(1) list removal; keep both in sync.
        table.erase(entries.back());
        entries.pop_back();
        entries.push_front(key);
        table[key] = {value, entries.begin()};
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main() {
    // Expected: [null,null,null,1,null,-1,null,-1,3,4]
    LRUCache cache(2);
    printf("[null");

    cache.put(1, 1);
    printf(",null");
    cache.put(2, 2);
    printf(",null");
    printf(",%d", cache.get(1));

    cache.put(3, 3);
    printf(",null");
    printf(",%d", cache.get(2));

    cache.put(4, 4);
    printf(",null");
    printf(",%d", cache.get(1));
    printf(",%d", cache.get(3));
    printf(",%d]\n", cache.get(4));

    return 0;
}
