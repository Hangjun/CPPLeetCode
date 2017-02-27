/*
Design a data structure that supports the following two operations:

void addWord(word)
bool search(word)
search(word) can search a literal word or a regular expression string containing only letters a-z or .. A . means it can represent any one letter.

For example:

addWord("bad")
addWord("dad")
addWord("mad")
search("pad") -> false
search("bad") -> true
search(".ad") -> true
search("b..") -> true
Note:
You may assume that all words are consist of lowercase letters a-z.

click to show hint.

You should be familiar with how a Trie works. If not, please work on this problem: Implement Trie (Prefix Tree) first.
*/

/*
This is an obvious Trie tree problem. The only tricky part here is that the query can contain regular expressions '.'. We can happily tackle that case with a DFS.
*/
class TrieNode {
public:
    TrieNode *ch[26];
    string key;
    
    TrieNode(): key("") {
        for (int i = 0; i < 26; i++) ch[i] = NULL;
    }
};

class WordDictionary {
public:
    /** Initialize your data structure here. */
    WordDictionary() {
        root = new TrieNode();
    }
    
    /** Adds a word into the data structure. */
    void addWord(string word) {
        TrieNode *p = root;
        for (char c : word) {
            if (!p->ch[c-'a']) p->ch[c-'a'] = new TrieNode();
            p = p->ch[c-'a'];
        }
        p->key = word;
    }
    
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        return searchDFS(word, 0, root);
    }
private:
    TrieNode *root;
    
    bool searchDFS(string word, int matched, TrieNode *curNode) {
        if (matched == word.size()) return !curNode->key.empty();
        if (word[matched] != '.') {
            return curNode->ch[word[matched]-'a'] && searchDFS(word, matched+1, curNode->ch[word[matched]-'a']);
        } else {
            for (int i = 0; i < 26; i++) {
                if (!curNode->ch[i]) continue;
                if (searchDFS(word, matched+1, curNode->ch[i])) return true;
            }
        }
        return false;
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary obj = new WordDictionary();
 * obj.addWord(word);
 * bool param_2 = obj.search(word);
 */
