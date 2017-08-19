/*
Initially, there is a Robot at position (0, 0). Given a sequence of its moves, judge if this robot makes a circle, which means it moves back to the original place.

The move sequence is represented by a string. And each move is represent by a character. The valid robot moves are R (Right), L (Left), U (Up) and D (down). The output should be true or false representing whether the robot makes a circle.

Example 1:
Input: "UD"
Output: true

Example 2:
Input: "LL"
Output: false
*/

class Solution {
public:
    bool judgeCircle(string moves) {
        unordered_map<char, pair<int, int>> ht;
        ht['U'] = make_pair(0, 1);
        ht['D'] = make_pair(0, -1);
        ht['L'] = make_pair(-1, 0);
        ht['R'] = make_pair(1, 0);
    
        pair<int, int> initialPos;
        initialPos.first = 0, initialPos.second = 0;
        
        for (char move : moves) computeNextPosition(initialPos, move, ht);
        
        return initialPos.first == 0 && initialPos.second == 0;
    }
    
private:
   
    void computeNextPosition(pair<int, int> &curPos, char move, unordered_map<char, pair<int, int>> &ht) {
        pair<int, int> delta = ht[move];
        curPos.first += delta.first;
        curPos.second += delta.second;
    }
};
