/*
 * Problem Link: https://leetcode.cn/problems/lru-cache/
 * Problem Name: 146. LRU Cache
 * Difficulty: Medium
 * Problem Tags: design, hash table, linked list, doubly-linked list
 *
 * Submission Record:
 * Approach: Direct-address table + array-backed doubly-linked list
 * Language: C++
 * Status: Accepted
 * Submitted At: N/A
 * Runtime: 7 ms (beats 97.05%)
 * Memory: 48.34 MB (beats 47.97%)
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
 * The local main() uses the official operation sequence, with the first
 * stored value changed from 1 to 0; its first successful get() returns 0.
 * null represents a constructor or put() call with no return value.
 *
 * Approach:
 * Use the bounded key directly as an index into table, which stores the
 * value, validity flag, and linked-list slot. No hashing is needed.
 * Store list nodes in entries; pi and ni are predecessor/successor slot
 * indices. first is most recently used; last is least recently used.
 * The index 0xffff denotes no neighbor. Hits move their slot to first.
 * Insertions allocate the next unused slot until capacity is reached;
 * thereafter, invalidate the old key and reuse the least-recent slot.
 * Both arrays belong to each cache object and are zero-initialized, so
 * different instances do not share validity flags or list state.
 *
 * Complexity:
 * Let U = 10001 be the direct-address table length and C = 3001 be the
 * reserved list-slot count. Construction takes O(U + C) time to initialize
 * the arrays. get(), put(), and moving a node each take O(1) worst-case
 * time: they access only a constant number of slots and links.
 * Each object reserves O(U + C) storage regardless of the chosen capacity;
 * at most capacity slots contain active list nodes. For q operations,
 * total time including construction is O(U + C + q).
 */

#include <cstdio>
#include <cstdint>

using namespace std;

struct Data {
    int value;
    uint16_t ei;
    bool v;
};

struct Entry {
    uint16_t key;
    uint16_t pi;
    uint16_t ni;
};

class LRUCache {
private:
    int capacity;
    uint16_t size;
    uint16_t last;
    uint16_t first;

    // O(U + C) reserved storage and zero-initialization per cache object.
    Data table[10001]{};  // Direct key lookup; v == false means absent.
    Entry entries[3001]{};  // Linked-list connections use array indices.


    // O(1): detach one slot and reconnect it at the most-recent end.
    void moveToFirst(uint16_t idx) {
        if (idx == first) return;
        if (first == last) return;
        if (idx == last) last = entries[idx].pi;
        if (entries[idx].pi != 0xffff) entries[entries[idx].pi].ni = entries[idx].ni;
        if (entries[idx].ni != 0xffff) entries[entries[idx].ni].pi = entries[idx].pi;

        entries[idx].pi = 0xffff;
        entries[idx].ni = first;

        entries[first].pi = idx;
        first = idx;
    };


public:
    LRUCache(int capacity) {
        this->capacity = capacity;
        size = 0;
        first = 0xffff;
        last = 0xffff;
    }

    // O(1): direct lookup and, on a hit, refresh recency.
    int get(int key) {
        if (table[key].v) {
            moveToFirst(table[key].ei);
            return table[key].value;
        } 
        return -1;
    }

    // O(1): update, allocate a free slot, or reuse the least-recent slot.
    void put(int key, int value) {
        if (table[key].v) {
            moveToFirst(table[key].ei);
            table[key].value = value;
            return;
        }
            

        if (size < capacity) {
            table[key] = {value, size, true};

            entries[size] = {(uint16_t) key, 0xffff, first};
            if (first != 0xffff) entries[first].pi = size;
            else last = 0;
            first = size;

            size++;
            
            return;
        }

        // O(1) eviction: invalidate the old key and recycle its list slot.
        uint16_t plast = last;
        table[entries[last].key].v = false;

        moveToFirst(last);
        
        table[key] = {value, first, true};
        entries[first].key = key;

        return;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main() {
    // Expected: [null,null,null,0,null,-1,null,-1,3,4]
    LRUCache cache(2);
    printf("[null");

    cache.put(1, 0);
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
