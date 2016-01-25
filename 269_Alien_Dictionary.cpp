/*
 There is a new alien language which uses the latin alphabet. However, the order among letters are unknown to you. You receive a list of words from the dictionary, where words are sorted lexicographically by the rules of this new language. Derive the order of letters in this language.

For example,
Given the following words in dictionary,

[
  "wrt",
  "wrf",
  "er",
  "ett",
  "rftt"
]

The correct order is: "wertf".

Note:

    You may assume all letters are in lowercase.
    If the order is invalid, return an empty string.
    There may be multiple valid order of letters, return any one of them is fine.
*/

// in-degree BFS approach
class Solution {
public:
    string alienOrder(vector<string>& words) {
        if (words.empty()) return "";
        if (words.size() == 1) return words[0];
        string order = "";
        unordered_map<char, int> inDegree;
        unordered_map<char, vector<char>> partialOrder;
        int totalDegree = 0;
        for (int i = 0; i < words.size() -1; i++) {
            string s = words[i];
            string t = words[i+1];
            int len = max(s.size(), t.size());
            bool found = false;
            for (int j = 0; j < len; j++) {
                // "warm up" the inDegree table
                if (j < s.size() && inDegree.find(s[j]) == inDegree.end()) {inDegree[s[j]] = 0;}
                if (j < t.size() && inDegree.find(t[j]) == inDegree.end()) {inDegree[t[j]] = 0;}
                // if s[j] != t[j], and we havn't recorded the first difference yet, record it
                if (j < s.size() && j < t.size() && s[j] != t[j] && !found) {
                    // s[j] proceeds t[j]
                    partialOrder[s[j]].push_back(t[j]);
                    inDegree[t[j]]++;
                    found = true;
                }
            }
        }
        queue<char> q;
        for (auto it = inDegree.begin(); it != inDegree.end(); it++) {
            totalDegree += it->second;
            if (it->second == 0) {
                q.push(it->first);
            }
        }
        while (!q.empty()) {
            char curChar = q.front();
            order.push_back(curChar);
            q.pop();
            // check if curChar proceeds any other characters
            if (partialOrder[curChar].empty()) continue;
            for (auto it = partialOrder[curChar].begin(); it != partialOrder[curChar].end(); it++) {
                --totalDegree;
                if(--inDegree[*it] == 0) {
                    q.push(*it);
                }
            }
        }
        // check if any character's indegree is still positive
        return totalDegree == 0 ? order : "";
    }
};

// DFS topological sort approach:
class Solution {
public:
    string alienOrder(vector<string>& words) {
        string order = "";
        if (words.empty()) return order;
        unordered_set<char> letters;
        vector<pair<char, char>> partialOrders;
        for (int i = 0; i < words.size(); i++) {
            if (words[i].empty()) continue;
            for (int k = 0; k < words[i].size(); k++) {
                letters.insert(words[i][k]);
            }
            for (int j = i+1; j < words.size(); j++) {
                if (words[j].empty() || words[j] == words[i]) continue;
                // find first miss-matching characters in word i and j
                pair<char, char> oneOrder = firstFirstUnMatchChars(words[i], words[j], letters);
                // If uppercase chars are returned, then words[i] is a prefix of
                // words[j], or vice versa. In this case no ordering information
                // can be extracted, thus we need to be able to filter it.
                if (oneOrder.first != oneOrder.second) {
                    partialOrders.push_back(oneOrder);   
                }
            }
        }
        topSort(letters, partialOrders, order);
        return order;
    }

private:
    pair<char, char> firstFirstUnMatchChars(string s, string t, unordered_set<char> &letters) {
        int len = min(s.size(), t.size());
        int i = 0;
        while (i < len && s[i] == t[i]) {
            letters.insert(s[i++]);
        }
        if (i == len) { // s is a prefix of t, or vice versa
            if (s.size() > len) {
                while (i < s.size()) {
                    letters.insert(s[i++]);
                }
            } else if (t.size() > len) {
                while (i < t.size()) {
                    letters.insert(t[i++]);
                }
            }
            return make_pair('A', 'A');
        }
        // neither s nor t is fully traversed
        int iCopy = i;
        if (s.size() > i) {
            while (i < s.size()) {
                letters.insert(s[i++]);
            }
        }
        i = iCopy;
        if (t.size() > i) {
            while (i < t.size()) {
                letters.insert(t[i++]);
            }
        }
        i = iCopy;
        return make_pair(s[i], t[i]);
    }
    
    void topSort(unordered_set<char> &letters, vector<pair<char, char>> &partialOrders, string &order) {
        if (partialOrders.empty()) {
            for (auto it = letters.begin(); it != letters.end(); it++) {
                order.push_back(*it);
            }
            return;
        }
        // build adjacency list
        unordered_map<char, unordered_set<char>> adj;
        for (int i = 0; i < partialOrders.size(); i++) {
            pair<char, char> e = partialOrders[i];
            adj[e.first].insert(e.second);
        }
        unordered_set<char> visited;
        unordered_set<char> inStack;
        stack<char> s;
        for (auto it = letters.begin(); it != letters.end(); it++) {
            if (visited.find(*it) == visited.end()) {
                if (dfs(adj, *it, visited, inStack, s)) { // cycle found
                    return;
                }
            }
        }
        // no cycle found
        while (!s.empty()) {
            order.push_back(s.top());
            s.pop();
        }
        return; 
    } 
    
    bool dfs(unordered_map<char, unordered_set<char>> &adj, char index, unordered_set<char> &visited, unordered_set<char> &inStack, stack<char> &s) {
        visited.insert(index);
        inStack.insert(index);
        
        for (auto it = adj[index].begin(); it != adj[index].end(); it++) {
            if (visited.find(*it) == visited.end() && dfs(adj, *it, visited, inStack, s)) {
                // cycle found
                return true;
            }
            if (inStack.find(*it) != inStack.end()) { // cycle found
                return true;
            }
        }
        inStack.erase(index);
        s.push(index);
        return false;
    }
};
