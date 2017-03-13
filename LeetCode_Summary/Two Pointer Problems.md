# Two Pointer Problems


	Given a string, find the length of the longest substring T that contains at most 2 distinct characters. For example, Given s = “eceba”, T is "ece" which its length is 3.


```c++
class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        if (s.size() < 3) return s.size();
        vector<int> dict(256, 0);
        int maxLen = 0;
        int left = 0;
        int count = 0;
        for (int right = 0; right < s.size(); right++) {
            dict[s[right]]++;
            if (dict[s[right]] == 1) { // new character
                count++;
                while (count > 2) { // shrink window if needed
                    dict[s[left]]--;
                    if (dict[s[left]] == 0) count--;
                    left++;
                }
            }
            maxLen = max(maxLen, right-left+1);
        }
        return maxLen;
    }
};
```

**Remark**:
```
:
* asdf
* asdfas
* asdfa
1. 3
2. 2
```

