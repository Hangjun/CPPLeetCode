/*
Given a list of airline tickets represented by pairs of departure and arrival airports [from, to], reconstruct the itinerary in order. All of the tickets belong to a man who departs from JFK. Thus, the itinerary must begin with JFK.

Note:

    If there are multiple valid itineraries, you should return the itinerary that has the smallest lexical order when read as a single string. For example, the itinerary ["JFK", "LGA"] has a smaller lexical order than ["JFK", "LGB"].
    All airports are represented by three capital letters (IATA code).
    You may assume all tickets form at least one valid itinerary.

Example 1:
tickets = [["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]]
Return ["JFK", "MUC", "LHR", "SFO", "SJC"].

Example 2:
tickets = [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
Return ["JFK","ATL","JFK","SFO","ATL","SFO"].
Another possible reconstruction is ["JFK","SFO","ATL","JFK","ATL","SFO"]. But it is larger in lexical order. 
*/

/* We revisit this problem just to double check my understanding. */

// Submission #1: Accepted.
class Solution {
public:
    vector<string> findItinerary(vector<pair<string, string>> tickets) {
        vector<string> res;
        if (tickets.empty()) return res;
        // ht["JFK"]["SFO"] = 2 means there are two tickets from JFK to SFO
        unordered_map<string, map<string, int>> ht;
        // preprocessing
        for (auto e : tickets) {
            ht[e.first][e.second]++;
        }
        string start = "JFK";
        res.push_back(start);
        findItineraryDFS(start, ht, tickets.size() + 1, res);
        
        return res;
    }
    
    bool findItineraryDFS(string u, unordered_map<string, map<string, int>> &ht, const int &n, vector<string> &res) {
        // recursion invariant: city u has been pushed into res, checking remaining cities
        // terminating condition
        if (res.size() == n) {return true;}
        
        // search in lexical next possible city to fly to
        for (auto it = ht[u].begin(); it != ht[u].end(); it++) {
            if (it->second > 0) {
                // recursively search from city it->first
                it->second--;
                res.push_back(it->first);
                if (findItineraryDFS(it->first, ht, n, res)) {return true;}
                res.pop_back();
                it->second++;
            }
        }
        
        return false;
    }
};

/* Here is another sytle of DFS: */
class Solution {
public:
    vector<string> findItinerary(vector<pair<string, string>> tickets) {
        vector<string> res;
        if (tickets.empty()) return res;
        // ht["JFK"]["SFO"] = 2 means there are two tickets from JFK to SFO
        unordered_map<string, map<string, int>> ht;
        // preprocessing
        for (auto e : tickets) {
            ht[e.first][e.second]++;
        }
        string start = "JFK";
        findItineraryDFS(start, ht, tickets.size() + 1, res);
        
        return res;
    }
    
    bool findItineraryDFS(string u, unordered_map<string, map<string, int>> &ht, const int &n, vector<string> &res) {
        res.push_back(u);
        // recursion invariant: city u has been pushed into res, checking remaining cities
        // terminating condition
        if (res.size() == n) {return true;}
        
        // search in lexical next possible city to fly to
        for (auto it = ht[u].begin(); it != ht[u].end(); it++) {
            if (it->second > 0) {
                // recursively search from city it->first
                it->second--;
                if (findItineraryDFS(it->first, ht, n, res)) {return true;}
                it->second++;
            }
        }
        
        res.pop_back();
        return false;
    }
};

/* Analysis:
I think both implementations are fine. The second implementation cleans up the mess right where it fails, whereas the first implementation 
does that after returning back to upper level. 

The first implementation is natural in this problem since we know "JFK" is the starting node, and there exists at least one solution. The 
second implementation is more robust in that it deals with the case where no desired itinerary exists. 

From another perspective, the DFS prototype for graph traversal is:
    dfs (u) {
        visited[u] = true;
        
        for all v in neighbors(u) {
            if (!visited[v]) {
                dfs(v);
            }
        }
        
        // backtrack at the current level
        visited[u] = false; // optional depending on whether we need to search again
    }

It seems that the second implementation fits the above prototype better as it cleans up the mess right where it fails, instead of doing 
that after returning back to upper level.
*/


