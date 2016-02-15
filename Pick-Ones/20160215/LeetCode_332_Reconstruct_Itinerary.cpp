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

/* Key:
Data Structure!
*/

// Submission/Attemp #1: Does not compile since it is only an idea:

class Solution {
public:
    vector<string> findItinerary(vector<pair<string, string>> tickets) {
        vector<string> res;
        if (tickets.empty()) return res;
        unordered_map<string, vector<string, string>> ht;
        for (auto e : tickets) {
            ht[e.first].push_back(e.second);
        }
        for (auto i : ht) {
            sort(ht[i].begin(), ht[i].end());
        }
        unordered_set<pair<string, string>> visitedEdges;
        findItineraryDFS("JFK", ht, visitedEdges, res);
        
        return res;
    }
    
    void findItineraryDFS(string u, unordered_map<string, vector<string, string>> &ht, unordered_set<pair<string, string>> &visitedEdges, vector<string> res) {
        res.push_back(u);
        
        for (auto v : ht[u]) {
            if (visitedEdges.find(make_pair(u, v)) == visitedEdges.end()) {
                visitedEdges.insert(make_pair(u, v));
                findItineraryDFS(v, ht, visitedEdges, res);
            }
        }
    }
};

/* Analysis:
The struggle that I had was that I was having a hard time recording visited edges. A better data structure can be used to overcome this 
difficulty. Instead of using unordered_map<string, vector<string>> ht, and then sort the value vector<string> associated with each starting 
city, which is the key, we can simply use unordered<string, map<string, int>> ht. Here the map data structure will sort the destinations given 
a starting city automatically. Moreover, ht[u][v], which is an int, can be used to detect visitedness of the directed edge (u, v).

Moreover, since there maybe many solutions, the stopping criterion for the DFS needs to be more clever. Instead of search for node, we can 
simply stop as soon as the result contains n+1 nodes, where n is the number of tickets. This stopping criterion is more natural.

Reference: https://www.hrwhisper.me/leetcode-reconstruct-itinerary/
*/

// Submission #2: Accepted.
class Solution {
public:
    vector<string> findItinerary(vector<pair<string, string>> tickets) {
        vector<string> res;
        if (tickets.empty()) return res;
        unordered_map<string, map<string, int>> ht;
        for (auto e : tickets) {
            ht[e.first][e.second]++;
        }
        string start = "JFK";
        res.push_back(start);
        findItineraryDFS(start, tickets.size()+1, ht, res);
        return res;
    }
    
    bool findItineraryDFS(string u, const int &n, unordered_map<string, map<string, int>> &ht, vector<string> &res) {
        // return true <=> an itinerary has been found
        if (res.size() == n) return true;
        for (auto v = ht[u].begin(); v != ht[u].end(); v++) { // iterator for ht[u]: map<string, int>
            if (v->second != 0) { 
                v->second--;
                res.push_back(v->first);
                if (findItineraryDFS(v->first, n, ht, res)) return true;
                res.pop_back();
                v->second++;
            }
        }
        // false <=> itinerary cannot be found starting at u, need to backtrack
        return false;
    }
};


//Submission #3: Accepted. Another flavor of DFS.
class Solution {
public:
    vector<string> findItinerary(vector<pair<string, string>> tickets) {
        vector<string> res;
        if (tickets.empty()) return res;
        unordered_map<string, map<string, int>> ht;
        for (auto e : tickets) {
            ht[e.first][e.second]++;
        }
        string start = "JFK";
        findItineraryDFS(start, tickets.size()+1, ht, res);
        return res;
    }
    
    bool findItineraryDFS(string u, const int &n, unordered_map<string, map<string, int>> &ht, vector<string> &res) {
        res.push_back(u);
        // return true <=> an itinerary has been found
        if (res.size() == n) return true;
        for (auto v = ht[u].begin(); v != ht[u].end(); v++) { // iterator for ht[u]: map<string, int>
            if (v->second != 0) { 
                v->second--;
                if (findItineraryDFS(v->first, n, ht, res)) return true;
                v->second++;
            }
        }
        // false <=> itinerary cannot be found starting at u, need to backtrack
        res.pop_back();
        return false;
    }
};


