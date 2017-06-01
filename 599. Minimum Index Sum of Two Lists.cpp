/*
Suppose Andy and Doris want to choose a restaurant for dinner, and they both have a list of favorite restaurants represented by strings.

You need to help them find out their common interest with the least list index sum. If there is a choice tie between answers, output all of them with no order requirement. You could assume there always exists an answer.

Example 1:
Input:
["Shogun", "Tapioca Express", "Burger King", "KFC"]
["Piatti", "The Grill at Torrey Pines", "Hungry Hunter Steakhouse", "Shogun"]
Output: ["Shogun"]
Explanation: The only restaurant they both like is "Shogun".
Example 2:
Input:
["Shogun", "Tapioca Express", "Burger King", "KFC"]
["KFC", "Shogun", "Burger King"]
Output: ["Shogun"]
Explanation: The restaurant they both like and have the least index sum is "Shogun" with index sum 1 (0+1).
Note:
The length of both lists will be in the range of [1, 1000].
The length of strings in both lists will be in the range of [1, 30].
The index is starting from 0 to the list length minus 1.
No duplicates in both lists.
*/

// Straightforward solution. Time: O(m+n), Space: O(m+n).
class Solution {
public:
    vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
        vector<string> res;
        int minSum = INT_MAX;
        unordered_map<string, vector<int>> ht; // string -> vector of indices
        for (int i = 0; i < list1.size(); i++) ht[list1[i]].push_back(i);
        for (int j = 0; j < list2.size(); j++) ht[list2[j]].push_back(j);
        
        for (auto p : ht) {
            if (p.second.size() != 2) continue;
            if (p.second[0] + p.second[1] < minSum) {
                res.clear();
                res.push_back(p.first);
                minSum = p.second[0] + p.second[1];
            } else if (p.second[0] + p.second[1] == minSum) {
                res.push_back(p.first);
            }
        }
        
        return res;
    }
};

// We can actually improve the space complexity to O(min(m, n)) by only traversing each list once.
class Solution {
public:
    vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
        vector<string> res;
        int minSum = INT_MAX;
        unordered_map<string, int> ht; // string -> index
        for (int i = 0; i < list1.size(); i++) ht[list1[i]] = i;
        
        for (int j = 0; j < list2.size(); j++) {
            string str = list2[j];
            if (ht.find(str) == ht.end()) continue;
            if (j + ht[str] < minSum) {
                minSum = j + ht[str];
                res.clear();
                res.push_back(str);
            } else if (j + ht[str] == minSum) {
                res.push_back(str);
            }
        }

        return res;
    }
};
