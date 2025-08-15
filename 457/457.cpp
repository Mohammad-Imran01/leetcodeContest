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
};