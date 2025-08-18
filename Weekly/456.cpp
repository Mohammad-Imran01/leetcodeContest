#include "../tinyCodes.h"

class Solution
{
    // Q1. Partition String
    // Medium 4 pt. Given a string s, partition it into unique segments:
    // - Start at index 0, extend segment until it hasn't been seen before
    // - Once unique, mark it seen, push into result, and start new segment
    // - Return the list of segments
public:
    V1<string> partitionString(string s)
    {
        unordered_set<string> seenSoFar;
        V1<string> res;
        string curr;
        for (int i = 0; i < s.length(); ++i)
        {
            curr += s[i];
            if (seenSoFar.count(curr))
                continue;
            seenSoFar.insert(curr);
            res.push_back(curr);
            curr.clear();
        }
        return res;
    }

    // Q2. Longest Common Prefix Between Adjacent Strings After Removals
    // Medium 4 pt.
    // - For each index i, remove words[i]
    // - Compute longest common prefix among adjacent pairs
    // - Return array answer where answer[i] is max LCP length
private:
    int getPrefix(const string &a, const string &b)
    {
        int res = 0;
        for (int i = 0; i < a.size() && i < b.size(); ++i)
        {
            if (a[i] != b[i])
                break;
            ++res;
        }
        return res;
    }

public:
    vector<int> longestCommonPrefix(V1<string> &words)
    {
        int n = words.size();
        if (n == 1)
            return {0};

        vector<int> temp(n - 1);
        for (int i = 1; i < n; ++i)
            temp[i - 1] = getPrefix(words[i], words[i - 1]);

        vector<int> left(n - 1), right(n - 1);
        left[0] = temp[0], right[n - 2] = temp[n - 2];

        for (int i = 1; i < n - 1; ++i)
        {
            int l = i, r = n - 2 - i;
            left[l] = max(left[l - 1], temp[l]);
            right[r] = max(right[r + 1], temp[r]);
        }

        vector<int> res(n, 0);
        for (int i = 0; i < n; ++i)
        {
            int maxi = 0;

            // Case 1: max from pairs not involving i
            if (i > 1)
                maxi = max(maxi, left[i - 2]);
            if (i < n - 2)
                maxi = max(maxi, right[i + 1]);

            // Case 2: new pair formed after removal
            if (i > 0 && i < n - 1)
            {
                maxi = max(maxi, getPrefix(words[i - 1], words[i + 1]));
            }

            res[i] = maxi;
        }
        return res;
    }

    // Q3. Partition Array to Minimize XOR
    // Medium 5 pt.
    // - Partition nums into k non-empty subarrays
    // - Compute XOR of each subarray
    // - Minimize the maximum XOR across all subarrays
public:
    int minXor(vector<int> &nums, int k)
    {
        int n = nums.size();
        vector<int> px(n + 1, 0);
        for (int i = 0; i < n; i++)
            px[i + 1] = px[i] ^ nums[i];

        auto can = [&](int limit)
        {
            vector<int> dp(n + 1, 1e9);
            dp[0] = 0;
            for (int i = 1; i <= n; i++)
            {
                for (int j = 0; j < i; j++)
                {
                    int xr = px[i] ^ px[j];
                    if (xr <= limit)
                    {
                        dp[i] = min(dp[i], dp[j] + 1);
                    }
                }
            }
            return dp[n] <= k;
        };

        int lo = 0, hi = (1 << 30) - 1, ans = hi;
        while (lo <= hi)
        {
            int mid = lo + (hi - lo) / 2;
            if (can(mid))
            {
                ans = mid;
                hi = mid - 1;
            }
            else
            {
                lo = mid + 1;
            }
        }
        return ans;
    }
};