/*
Given an array of words and a length L, format the text such that each line has exactly L characters and is fully (left and right) justified.

You should pack your words in a greedy approach; that is, pack as many words as you can in each line. Pad extra spaces ' ' when necessary so that each line has exactly L characters.

Extra spaces between words should be distributed as evenly as possible. If the number of spaces on a line do not divide evenly between words, the empty slots on the left will be assigned more spaces than the slots on the right.

For the last line of text, it should be left justified and no extra space is inserted between words.

For example,
words: ["This", "is", "an", "example", "of", "text", "justification."]
L: 16.

Return the formatted lines as:
[
   "This    is    an",
   "example  of text",
   "justification.  "
]
Note: Each word is guaranteed not to exceed L in length.

Corner Cases:
A line other than the last line might contain only one word. What should you do in this case?
In this case, that line should be left-justified.
*/

class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> res;
        int begin = 0;
        while (begin < words.size()) {
            int last = begin;
            int linesize = words[begin++].size();
            while (begin < words.size() && linesize + 1 + words[begin].size() <= maxWidth) {
                linesize += 1 + words[begin].size();
                begin++;
            }
            
            int spaces = 1, extra = 0;
            if (begin < words.size() && begin != last + 1) {
                spaces = (maxWidth - linesize) / (begin - last - 1) + 1;
                extra = (maxWidth - linesize) % (begin - last - 1);
            }
            
            res.push_back(words[last++]);
            while (extra--) {
                res.back().append(spaces+1, ' ');
                res.back().append(words[last++]);
            }
            while (last < begin) {
                res.back().append(spaces, ' ');
                res.back().append(words[last++]);
            }
            res.back().append(maxWidth-res.back().size(), ' ');
        }
        
        return res;
    }
};
