/*
 * https://codeforces.com/problemset/problem/30/A
 *
 * Problem: Accounting (Codeforces Beta Round 30 - Problem A)
 * Difficulty: 1400 (Codeforces Rating)
 * Tags: Brute Force, Mathematics
 * 
 * Problem Description:
 * King Copa needs to demonstrate the financial stability of his kingdom by finding an integer growth coefficient X.
 * The kingdom's income follows the formula: A * (X^n) = B, where:
 * - A is the income in the 0-th year (can be negative, indicating a loss)
 * - B is the income in the n-th year (can also be negative)
 * - X is the annual growth coefficient (must be an integer; can be zero or negative)
 * The goal is to find such an integer X. If no integer X exists (or X would be fractional), output "No solution".
 * If multiple valid X exist, any one of them can be output.
 * 
 * Input Specification:
 * The input consists of three integers A, B, n, where:
 * - |A| ≤ 1000 (absolute value of A is at most 1000)
 * - |B| ≤ 1000 (absolute value of B is at most 1000)
 * - 1 ≤ n ≤ 10 (n is a positive integer between 1 and 10 inclusive)
 * 
 * Output Specification:
 * - If an integer X satisfying A * (X^n) = B exists, output X.
 * - If no such integer X exists, output "No solution".
 * 
 * Special Cases to Note:
 * 1. When A = 0:
 *    - If B = 0: Any integer X is valid (e.g., the third sample input outputs 5).
 *    - If B ≠ 0: No solution exists (since 0 * X^n = 0 ≠ B).
 * 2. When A ≠ 0:
 *    - X must be an integer such that X^n = B / A (B must be divisible by A first; otherwise, no solution).
 *    - The parity of n affects X's sign:
 *      - For even n: X^n is non-negative, so A and B must have the same sign (or both zero).
 *      - For odd n: X^n has the same sign as X, so the sign of X is determined by B/A.
 * 
 * Solution Approach:
 * 1. Handle the special case where A = 0 first (check B and output any X if B=0, else "No solution").
 * 2. For A ≠ 0:
 *    a. Check if B is divisible by A. If not, output "No solution".
 *    b. Compute target = B / A (we need X^n = target).
 *    c. Brute-force possible X values (since |target| ≤ 1000 and n ≤ 10, X ranges from -1000 to 1000 is sufficient).
 *    d. For each X, compute X^n (avoid overflow by checking intermediate values if needed) and verify if it equals target.
 *    e. If a valid X is found, output it; if none are found after checking all possibilities, output "No solution".
 * 
 * Example Inputs & Outputs:
 * 1. Input: 2 18 2 → Output: 3 (since 2 * 3² = 2*9=18)
 * 2. Input: -1 8 3 → Output: -2 (since -1 * (-2)³ = -1*(-8)=8)
 * 3. Input: 0 0 10 → Output: 5 (any integer is valid; 5 is a sample choice)
 * 4. Input: 1 16 5 → Output: No solution (no integer X satisfies X⁵=16)
 */



#include <stdio.h>
#include <math.h>

// long long int pow(long long int x, int n) {
//     long long int result = 1;
//     for (int i = 0; i < n; i++) {
//         result *= x;
//     }
//     return result;
// }

int main() {
	long long int a, b, n;
	scanf("%lld%lld%lld", &a, &b, &n);

	if (a == b) {
		printf("1\n");
		return 0;
	}

    if (a == 0) {
        printf("No solution\n");
        return 0;
    }

    if (b == 0) {
        printf("0\n");
        return 0;
   }

    if (b % a != 0) {
        printf("No solution\n");
        return 0;
    }

    long long int x, k;
    k = b / a;
    int minus = k < 0;

    if (minus) {
        k = -k;
    }
    
    if (minus && n % 2 == 0){
        printf("No solution\n");
        return 0;
    }

    double f = pow((double)k, 1.0 / (double) n) + 1e-5;

    if (f - (long long int)f > 2e-5)
        printf("No solution\n");
    else 
        printf("%lld\n", minus ? -(long long int)f : (long long int)f);

    return 0;
}




