/*
Equations are given in the format A / B = k, where A and B are variables represented as strings, and k is a real number (floating point number). Given some queries, return the answers. If the answer does not exist, return -1.0.

Example:
Given a / b = 2.0, b / c = 3.0. 
queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? . 
return [6.0, 0.5, -1.0, 1.0, -1.0 ].

The input is: vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries , where equations.size() == values.size(), and the values are positive. This represents the equations. Return vector<double>.

According to the example above:

equations = [ ["a", "b"], ["b", "c"] ],
values = [2.0, 3.0],
queries = [ ["a", "c"], ["b", "a"], ["a", "e"], ["a", "a"], ["x", "x"] ]. 
The input is always valid. You may assume that evaluating the queries will result in no division by zero and there is no contradiction.
*/

/*
Analysis: Every query can be viewed as a path search in a directed graph. Once we reach this understanding, the rest is straightforward.
*/

class Solution {
public:
    vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
        vector<double> res;
        if (queries.empty()) return res;
        // adj[u][v] represents u/v, interpreted as the weight for the (u,v) edge
        unordered_map<string, map<string, double>> adj; 
        for (int i = 0; i < equations.size(); i++) {
            pair<string, string> e = equations[i];
            adj[e.first][e.second] = values[i];
            adj[e.second][e.first] = values[i] != 0 ? 1.0/values[i] : INT_MAX;
        }
        for (auto e : queries) {
            if (adj.find(e.first) == adj.end() || adj.find(e.second) == adj.end()) {
                res.push_back(-1.0);
                continue;
            }
            // find the path from e.first to e.second in the weighted graph
            unordered_set<string> visited;
            double sum = 1.0;
            // Caution: e.first and e.second might not be in the same connected component
            res.push_back(getWeightedPathSum(e.first, e.second, sum, adj, visited) ? sum : -1.0); 
        }
        return res;
    }
    
    bool getWeightedPathSum(string u, string v, double &sum, unordered_map<string, map<string, double>> &adj, unordered_set<string> &visited) {
        visited.insert(u);
        if (u == v) return true;
        
        for (auto n : adj[u]) {
            if (visited.count(n.first)) continue;
            sum *= n.second;
            if (getWeightedPathSum(n.first, v, sum, adj, visited)) return true;
            // backtrack
            sum /= n.second;
        }
        
        return false;
    }
};
