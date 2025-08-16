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