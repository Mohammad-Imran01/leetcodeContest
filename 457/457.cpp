#include "tinyCodes.h"
using namespace std;

/*
Q1. Coupon Code Validator (Easy - 3 pt)

Given:
    - code[i]: coupon identifier
    - businessLine[i]: category
    - isActive[i]: boolean

Valid coupon if:
    1. code[i] non-empty, only a-z, A-Z, 0-9, '_'
    2. businessLine[i] in {"electronics", "grocery", "pharmacy", "restaurant"}
    3. isActive[i] == true

Return:
    All valid codes, sorted by:
       1) businessLine in order: electronics, grocery, pharmacy, restaurant
       2) code lexicographically within each category

Example:
    code = ["SAVE20", "", "PHARMA5", "SAVE@20"]
    businessLine = ["restaurant", "grocery", "pharmacy", "restaurant"]
    isActive = [true, true, true, true]
    → Output: ["PHARMA5", "SAVE20"]

Constraints:
    1 <= n <= 100
*/

/*
Q2. Power Grid Maintenance

We have c power stations (1..c) connected by bidirectional cables (connections[]).
Connected stations form a "power grid". Initially, all stations are online.

Queries:
[1, x] → Maintenance check:
          - If x is online, return x.
          - If x is offline, return the smallest online station in x's grid, or -1 if none.
[2, x] → Take station x offline (remains part of grid structure).

Goal: Process all queries in order and output answers for type [1, x].

Constraints:
1 ≤ c ≤ 1e5, 0 ≤ connections ≤ 1e5, queries ≤ 2e5
*/

class Solution457
{
    const string t1 = "electronics";
    const string t2 = "grocery";
    const string t3 = "pharmacy";
    const string t4 = "restaurant";

    bool isValidChar(char c)
    {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' ||
               (c >= '0' && c <= '9');
    }
    bool isValCode(const string &str)
    {
        if (str.empty())
            return false;
        for (const char &c : str)
            if (!isValidChar(c))
                return false;
        return true;
    }
    bool isValBus(const string &type)
    {
        return type == t1 || type == t2 || type == t3 || type == t4;
    }

    int getCategoryIndex(const string &type)
    {
        if (type == t1)
            return 0;
        if (type == t2)
            return 1;
        if (type == t3)
            return 2;
        if (type == t4)
            return 3;
        return 4; // Unknown category
    }

    struct Disjoint
    {
        V1<int> par, weight, active;
        Disjoint(int n)
        {
            par.resize(n + 1),
                weight.assign(n + 1, 1),
                active.assign(n + 1, true);
            for (int i = 1; i <= n; ++i)
                par[i] = i;
        }
        void join(int x, int y)
        {
            x = getPar(x);
            y = getPar(y);
            if (weight[x] > weight[y])
            {
                par[y] = x;
            }
            else if (weight[x] < weight[y])
            {
                par[x] = y;
            }
            else
            {
                par[y] = x;
                ++weight[x];
            }
        }
        int getPar(int node)
        {
            if (par[node] == node)
                return node;
            return par[node] = getPar(par[node]);
        }
        void disable(int node)
        {
            active[node] = false;
        }
        int getActive(int node)
        {
            if (active[node])
                return node;
            int res = -1;
            node = getPar(node);
            for (int i = 1; i < weight.size(); ++i)
                if (active[i] && getPar(i) == node)
                {
                    res = i;
                    break;
                }
            return res;
        }
    };

public:
    V1<string> validateCoupons(const V1<string> &coupons, const V1<string> &companies, const V1<bool> &isActive)
    {
        if (coupons.size() != companies.size() || companies.size() != isActive.size())
            return {};
        const int len = coupons.size();

        unordered_map<string, vector<string>> validCoupons;
        for (int i = 0; i < len; ++i)
        {
            if (isValCode(coupons[i]) && isValBus(companies[i]) && isActive[i])
            {
                validCoupons[companies[i]].push_back(coupons[i]);
            }
        }
        V1<pair<string, V1<string>>> sortedCoupons(validCoupons.begin(), validCoupons.end());
        sort(sortedCoupons.begin(), sortedCoupons.end());

        V1<string> result;
        for (auto &sortedList : sortedCoupons)
        {
            sort(sortedList.second.begin(), sortedList.second.end());
            result.insert(result.end(), sortedList.second.begin(), sortedList.second.end());
        }

        return result;
    }

public:
    V1<int> processQueries(int c, vector<V1<int>> &conn, vector<V1<int>> &queries)
    {
        Disjoint ds(c);
        for (const auto &p : conn)
            ds.join(p[0], p[1]);
        V1<int> res;

        for (const auto &q : queries)
        {
            bool check = q[0] == 1;
            if (check)
            {
                res.push_back(ds.getActive(q[1]));
            }
            else
            {
                ds.disable(q[1]);
            }
        }

        return res;
    }
};
