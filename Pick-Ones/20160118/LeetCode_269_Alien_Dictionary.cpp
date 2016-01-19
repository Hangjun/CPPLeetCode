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

// Submission #1: DFS cycle detection: Accepted
class Solution {
public:
    string alienOrder(vector<string>& words) {
        string order = "";
        if (words.empty()) return order;
        unordered_set<char> letters;
        computeAllChars(words, letters);
        vector<pair<char, char>> partialOrders;
        for (int i = 0; i < words.size(); i++) {
            if (words[i].empty()) continue;
            for (int j = i+1; j < words.size(); j++) {
                if (words[j].empty() || words[j] == words[i]) continue;
                // find first miss-matching characters in word i and j
                pair<char, char> oneOrder = firstFirstUnMatchChars(words[i], words[j]);
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
    void computeAllChars(vector<string> &words, unordered_set<char> &letters) {
        if (words.empty()) return;
        for (int i = 0; i < words.size(); i++) {
            for (int j = 0; j < words[i].size(); j++) {
                letters.insert(words[i][j]);
            }
        }
    }
    
    pair<char, char> firstFirstUnMatchChars(string s, string t) {
        int len = min(s.size(), t.size());
        int i = 0;
        while (i < len && s[i] == t[i]) i++;
        if (i == len) { // s is a prefix of t, or vice versa
            return make_pair('A', 'A');
        }
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

/* Submission #2: Optimizing the time to collect all the distinct characters: Failed

Your input

["wrt","wrf","er","ett","rftt"]

Your answer

"wrt\x00fe"
*/

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
        if (s.size() > len) {
            while (i < s.size()) {
                letters.insert(s[i++]);
            }
        }
        i = iCopy;
        if (t.size() > len) {
            while (i < t.size()) {
                letters.insert(t[i++]);
            }
        }
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

/* Analysis:
This means that we have included the NULL character somewhere. There are two bugs in function firstFirstUnMatchChars:
1. On lines 181 and 187, we get to here if i < len and the while-loop terminated. Thus we need to traverse the remaining substring starting from
i, NOT len!
2. On line 192, before returning, we have already messed up the index i. i no longer points to the index where s and t first differ. Thus 
we need to reset i = iCopy before returning.
*/

// Submission #3: Accepted.
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
