/*
Given an absolute path for a file (Unix-style), simplify it.

For example,
path = "/home/", => "/home"
path = "/a/./b/../../c/", => "/c"

Corner Cases:
Did you consider the case where path = "/../"?
In this case, you should return "/".
Another corner case is the path might contain multiple slashes '/' together, such as "/home//foo/".
In this case, you should ignore redundant slashes and return "/home/foo".
*/

/*
Analysis: We use a c++ function called getline to split the string stream wrapped input string into a set of strings delimited by '/'.
*/

class Solution {
public:
    string simplifyPath(string path) {
        string res, tmp;
        vector<string> st;
        stringstream ss(path);
        
        // split the stringstream into strings delimited by '/'
        while (getline(ss, tmp, '/')) {
            if (tmp == "" || tmp == ".") continue;
            if (tmp == ".." && !st.empty()) st.pop_back();
            else if (tmp != "..") st.push_back(tmp);
        }
        
        for (string str : st) res += "/" + str;
        return res.empty() ? "/" : res;
    }
};
