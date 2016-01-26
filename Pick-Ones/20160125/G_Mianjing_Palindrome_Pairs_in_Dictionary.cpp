/*
Given a huge dictionary with distinct strings, find all pairs that could make a palindrome string when combined.

Example: Given [abcd, dcba, lls, s, sssll], return:
[abcd, dcba]
[lls, s]
[lls, sssll]

Link: http://www.1point3acres.com/bbs/thread-167201-1-1.html
*/


/* Analysis:
The idea is, for each string in the dictonary, figure out different palindomic complements, and check if any exist in the dictionary as 
well. For each string, we loop through it, and divide it into two parts A+B. Notice that if A is palindomic, and reverse(B) exist in 
the dictionary, then reverse(B) + A + B is also palindromic. Any pair that consititues a palindrome can be decomposed this way as well. 
Thus we do not lose any admissible pair.

Suppose there are n strings, and the average length of each string is k. Then the running time of this algorithm is O(nk^2):
1. We loop through the dictionary, which takes n iterations;
2. For each string, we whether all possible prefix (and surfix) is palindomic, which takes O(k^2) time. 
*/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <utility>

using namespace std;

bool isPal(string s) {
    if (s.empty()) return true;
    int i = 0, j = s.size()-1;
    while (i < j) {
        if (s[i] != s[j]) {
            return false;
        }
        i++;
        j--;
    }
    return true;
}

vector<pair<string, string>> palindromePair(vector<string> &dict) {
    vector<pair<string, string>> res;
    if (dict.empty()) return res;
    unordered_set<string> words;
    for (int i = 0; i < dict.size(); i++) {
        words.insert(dict[i]);
    }
    for (int i = 0; i < dict.size(); i++) {
        string s = dict[i];
        for (int l = 0; l <= s.size(); l++) {
            string firstHalf = s.substr(0, l);
            string secondHalf = s.substr(l, s.size()-l);
            if (isPal(firstHalf)) {
                string tmp = secondHalf;
                reverse(tmp.begin(), tmp.end());
                if (words.find(tmp) != words.end() && tmp != s) {
                    res.push_back(make_pair(tmp, s));
                }
            }
            
            if (isPal(secondHalf)) {
                string tmp = firstHalf;
                reverse(tmp.begin(), tmp.end());
                if (words.find(tmp) != words.end() && tmp != s) {
                    res.push_back(make_pair(s, tmp));
                }
            }
        }
    }
    return res;
}

int main() {
	vector<string> dict = {"abcd", "dcba", "lls", "s", "sssll"};
	vector<pair<string, string>> res = palindromePair(dict);
	for (int i = 0; i < res.size(); i++) {
	    cout << res[i].first << ", " << res[i].second << endl;
	}
	return 0;
}

/* Analysis:
This is still not an ideal solution in two respects:
1. Handling duplicates: if the reverse of an entire string in the dictionary also exists in the dictionary, then we will get the same exact 
pair twice. How to handle this unacceptable duplication?
2. Checking all possible prefixes palindomic or not takes too much time. This can definitely be optimized via better palindomic checking 
algorithms (e.g. Manacher's algorithm), and better data structures (e.g. prefix tree). We will revisit this problem when we finish reviewing 
string related algorithms. 
*/
