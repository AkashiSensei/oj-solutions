/*
 * Problem Link: https://leetcode.cn/problems/implement-trie-prefix-tree/
 * Problem Name: 208. Implement Trie (Prefix Tree)
 * Difficulty: Medium
 * Problem Tags: design, trie, string
 *
 * Submission Record:
 * Approach: Pointer-based trie with 26 child slots and word-end flags
 * Language: C++
 * Status: Accepted
 * Submitted At: N/A
 * Runtime: 31 ms (beats 49.84%)
 * Memory: 49.45 MB (beats 66.78%)
 * Submission Link: N/A
 * Recorded On: 2026-10-25
 * Record Source: User-provided accepted-submission screenshot
 *
 * Problem Description:
 * Implement a Trie that stores strings and supports full-word and prefix queries.
 *
 * Interface:
 * Trie(): Initialize an empty trie.
 * void insert(string word): Insert word into the trie.
 * bool search(string word): Return true if the complete word was inserted.
 * bool startsWith(string prefix): Return true if some inserted word starts
 * with prefix.
 *
 * Constraints:
 * 1. 1 <= word.length, prefix.length <= 2000
 * 2. Words and prefixes contain only lowercase English letters.
 * 3. At most 30000 calls in total are made to insert, search, and startsWith.
 *
 * Example:
 * Operations:
 * ["Trie","insert","search","search","startsWith","insert","search"]
 * Arguments:
 * [[],["apple"],["apple"],["app"],["app"],["app"],["app"]]
 * Output:
 * [null,null,true,false,true,null,true]
 *
 * Explanation:
 * Insert "apple". Searching for "apple" succeeds, but searching for the
 * complete word "app" fails. The prefix "app" exists. After inserting
 * "app", searching for that complete word succeeds too.
 *
 * Note:
 * The local main() runs the official operation sequence directly.
 * null represents the constructor or an insert() call with no return value.
 * Each Trie object allocates its own root. Child pointers and word-end flags
 * are initialized by DicNode's default member initializers.
 * This version has no destructor; allocated nodes are not explicitly released.
 *
 * Approach:
 * Each node represents one prefix and stores 26 child pointers indexed by
 * character minus 'a'. Insert follows the word's path, creating missing nodes,
 * and marks the final node as a complete word. Existing prefixes are shared.
 * Search follows the same path and requires the final word-end flag to be true.
 * startsWith only requires the complete prefix path to exist, regardless of
 * whether its final node marks a complete word. Missing edges return false.
 * Duplicate insertions reuse existing nodes and leave the word-end flag true.
 *
 * Complexity:
 * Let L be the operation's input string length and P the allocated trie node
 * count, including the root. Construction takes O(1) time for a fixed alphabet.
 * Insert, search, and startsWith each take O(L) worst-case time. Each new node
 * initializes 26 pointers, a constant amount of work for lowercase English.
 * Persistent trie storage is O(26*P) = O(P). If S is the total character count
 * across inserted words, P <= S + 1 because shared prefixes reuse nodes.
 * Insert allocates at most L additional nodes; query traversal uses O(1)
 * workspace. The public methods take string arguments by value, so an lvalue
 * call also copies O(L) characters and uses O(L) temporary argument storage.
 * Including an argument copy, peak storage is O(P + L). No recursion is used.
 */

#include <cstdio>
#include <string>

using namespace std;

struct DicNode {
    // One slot per lowercase letter; all initially nullptr.
    DicNode* next[26] = {};
    bool valid = false;  // True only when a complete inserted word ends here.
};

class Trie {
private:
    DicNode* dicRoot;
public:
    Trie() {
        // The root represents the empty prefix.
        dicRoot = new DicNode();
    }

    void insert(string word) {
        // Reuse existing prefixes and allocate only missing path nodes.
        DicNode* node = dicRoot;
        for (char ch: word) {
            if (node->next[ch - 'a'] == nullptr)
                node->next[ch - 'a'] = new DicNode();

            node = node->next[ch - 'a'];
        }
        node->valid = true;  // A path can exist without previously being a full word.
    }

    bool search(string word) {
        DicNode* node = dicRoot;
        for (char ch: word) {
            if (node->next[ch - 'a'] == nullptr)
                return false;

            node = node->next[ch - 'a'];
        }

        // Full-word lookup must distinguish an inserted word from a prefix.
        return node->valid;
    }

    bool startsWith(string prefix) {
        DicNode* node = dicRoot;
        for (char ch: prefix) {
            if (node->next[ch - 'a'] == nullptr)
                return false;

            node = node->next[ch - 'a'];
        }

        // Prefix lookup succeeds as soon as every character has a matching edge.
        return true;
    }
};

int main() {
    // Expected output: [null,null,true,false,true,null,true]
    Trie trie;
    printf("Example: [null");

    trie.insert("apple");
    printf(",null");

    printf(",%s", trie.search("apple") ? "true" : "false");
    printf(",%s", trie.search("app") ? "true" : "false");
    printf(",%s", trie.startsWith("app") ? "true" : "false");

    trie.insert("app");
    printf(",null");

    printf(",%s", trie.search("app") ? "true" : "false");
    printf("]\n");

    return 0;
}
