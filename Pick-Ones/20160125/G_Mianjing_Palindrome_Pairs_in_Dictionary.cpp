/*
Given a huge dictionary with distinct strings, find all pairs that could make a palindrome string when combined.

Example: Given [abcd, dcba, lls, s, sssll], return:
[abcd, dcba]
[lls, s]
[lls, sssll]
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
                    res.push_back(make_pair(s, tmp));
                }
            }
             
            if (isPal(secondHalf)) {
                string tmp = firstHalf;
                reverse(tmp.begin(), tmp.end());
                if (words.find(tmp) != words.end() && tmp != s) {
                    res.push_back(make_pair(tmp, s));
                }
            }
        }
    }
    return res;
}

int main() {
	// your code goes here
	return 0;
}

