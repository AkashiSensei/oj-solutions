/*
 * Problem Link: https://leetcode.cn/problems/basic-calculator-ii/
 * Problem Name: 227. Basic Calculator II
 * Difficulty: Medium
 * Problem Tags: math, string, stack
 *
 * Submission Record:
 * Approach: sscanf tokenization with a completed-term sum and current term
 * Language: C++
 * Status: Accepted
 * Submitted At: N/A
 * Runtime: 351 ms (beats 5.22%)
 * Memory: 11.91 MB (beats 96.39%)
 * Submission Link: N/A
 * Recorded On: 2026-10-26
 * Record Source: User-provided accepted-submission screenshot
 *
 * Problem Description:
 * Given a string s representing a valid arithmetic expression, evaluate it
 * and return its integer result. The expression contains nonnegative integer
 * operands, the operators '+', '-', '*', '/', and spaces, but no parentheses.
 * Apply the usual arithmetic precedence and left associativity.
 * Integer division truncates toward zero.
 * Do not use a built-in function that evaluates strings as mathematical
 * expressions, such as eval().
 *
 * Constraints:
 * 1. 1 <= s.length <= 300000
 * 2. s consists of integers, '+', '-', '*', '/', and spaces.
 * 3. s is a valid expression.
 * 4. Integer operands are in [0, 2147483647].
 * 5. All intermediate results and the answer fit in a signed 32-bit integer.
 *
 * Example 1:
 * Input: s = "3+2*2"
 * Output: 7
 *
 * Example 2:
 * Input: s = " 3/2 "
 * Output: 1
 *
 * Example 3:
 * Input: s = " 3+5 / 2 "
 * Output: 5
 *
 * Note:
 * This is a supplemental expression-evaluation problem outside the Hot100 list.
 * The local main() runs all three official examples directly, preserving spaces.
 * sscanf reads from s.c_str() without modifying the string. %n records the
 * characters consumed by the current call, including skipped spaces; pos
 * advances the next call to the unconsumed suffix.
 * The parser relies on valid input: one initial operand followed by complete
 * operator/operand pairs. The bitwise-complement loop condition assumes the
 * usual EOF value of -1 and stops at input exhaustion.
 *
 * Approach:
 * Read the first operand into tmp. Keep saved as the sum of completed additive
 * terms and tmp as the current signed term, which may still receive multiplication
 * or division. On '+' or '-', add tmp to saved and start the next signed term.
 * On '*' or '/', update tmp immediately. This preserves precedence and the
 * left-to-right evaluation order of consecutive multiplication/division.
 * C++ integer division truncates toward zero, including for a negative tmp.
 * At input exhaustion, return saved + tmp. No number or operator stack is stored.
 *
 * Complexity:
 * Let n be s.length(). Token processing and arithmetic require O(n) work if
 * parsing consumes only the characters of each token. However, repeated sscanf
 * calls on shrinking suffixes can rescan their full remaining lengths: glibc's
 * string-stream initialization calls strlen for every sscanf call. With O(n)
 * short tokens, the total scanned suffix lengths can be O(n^2).
 * Thus this implementation has O(n^2) worst-case time on glibc-style scanners;
 * scanner behavior is implementation-dependent, and a linear parser avoids
 * this extra work. Reference: glibc libio/strfile.h and libio/strops.c.
 * The evaluator uses O(1) auxiliary state and no recursive stack. Its string
 * parameter is passed by value, so an lvalue call also takes O(n) time and
 * O(n) storage for the argument copy. Including that copy, peak space is O(n);
 * s.c_str() itself does not allocate another string.
 */

#include <cstdio>
#include <string>

using namespace std;

class Solution {
public:
    int calculate(string s) {
        // Borrow the null-terminated character buffer; do not modify s while using it.
        const char* text = s.c_str();
        int pos = 0;
        // saved contains completed terms; tmp retains the active signed term.
        int saved = 0, tmp, input, cnt;
        char ch;

        // Parse the initial operand; %n reports consumption but is not an assignment count.
        sscanf(text, " %d%n", &tmp, &cnt);
        pos += cnt;

        // Parse each remaining operator/operand pair; repeated suffix scans can be costly.
        while (~sscanf(text + pos, " %c %d%n", &ch, &input, &cnt)) {
            pos += cnt;
            if (ch == '+' || ch == '-') {
                // Finish the preceding term before beginning a new additive term.
                saved += tmp;
                if (ch == '+') tmp = input;
                else tmp = -input;
            }else {
                // Multiplication and division belong to the current term.
                if (ch == '*') tmp *= input;
                else tmp /= input;
            }

        }

        return saved + tmp;  // Include the final term, which has no following operator.
    }
};

int main() {
    Solution sol;
    string inputs[] = {
        "3+2*2",
        " 3/2 ",
        " 3+5 / 2 "
    };

    // Expected outputs: 7, 1, 5.
    for (int i = 0; i < 3; i++) {
        printf("Example %d: %d\n", i + 1, sol.calculate(inputs[i]));
    }

    return 0;
}
