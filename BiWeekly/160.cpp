#include "tinyCodes.h"

/*
Q1. Hexadecimal and Hexatrigesimal Conversion (Easy - 3 pt)

Given an integer n:

- Compute n² and n³.
- Convert n² to hexadecimal (base-16, digits 0-9, A-F).
- Convert n³ to hexatrigesimal (base-36, digits 0-9, A-Z).
- Concatenate the two results and return as a string.

Examples:

1. n = 13
   n² = 169 → hex = "A9"
   n³ = 2197 → base36 = "1P1"
   Result = "A91P1"

2. n = 36
   n² = 1296 → hex = "510"
   n³ = 46656 → base36 = "1000"
   Result = "5101000"

Constraints:
1 <= n <= 1000
*/

/*
Q2: Minimum Alternating Path Cost in Grid (Medium)

Given:
- Integers m, n: grid dimensions (rows x columns)
- waitCost[i][j]: cost to wait on cell (i, j)
- Entrance cost for cell (i, j): (i+1) * (j+1)

Rules:
1. Start at cell (0,0), paying its entrance cost.
2. Moves alternate each second:
   - Odd seconds: move right or down to an adjacent cell, paying its entrance cost.
   - Even seconds: must wait in place for exactly 1 second, paying waitCost[i][j].
3. Goal: reach bottom-right cell (m-1, n-1) with minimum total cost.

Example 1:
Input: m = 1, n = 2, waitCost = [[1,2]]
Output: 3
Explanation:
- Start at (0,0), pay entrance cost = 1
- Move right to (0,1) on second 1, pay entrance cost = 2
- Total cost = 1 + 2 = 3

Example 2:
Input: m = 2, n = 2, waitCost = [[3,5],[2,4]]
Output: 9
Explanation:
- Optimal path minimizes alternating move/wait costs.

Constraints:
- Always move within the grid
- Must follow alternating pattern: move → wait → move → wait → ...
- Return minimum total cost to reach (m-1, n-1)
*/

class Solution160
{
    char func(long long num)
    {
        if (num < 10)
            return '0' + num;
        return 'A' + (num - 10);
    }

    string getHex(long long num, int mod = 16)
    {
        string res;

        while (num)
        {
            res = func(num % mod) + res;
            num /= mod;
        }

        return res;
    }

public:
    string concatHex36(int n)
    {
        long long n2 = 1LL * n * n;
        long long n3 = 1LL * n * n * n;

        return getHex(n2) + getHex(n3, 36);
    }
};