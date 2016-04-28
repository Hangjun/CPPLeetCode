/*
Implement a trie with insert, search, and startsWith methods.

Note:
You may assume that all inputs are consist of lowercase letters a-z.
*/

class TrieNode {
public:
    // Initialize your data structure here.
    TrieNode *ch[26];
    bool isEnd;
    
    TrieNode() : isEnd(false) {
        for (int i = 0; i < 26; i++)
            ch[i] = NULL;
    }
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    // Inserts a word into the trie.
    void insert(string word) {
        TrieNode *p = root;
        for (int i = 0; i < word.size(); i++) {
            int j = word[i] - 'a';
            if (!p->ch[j]) { p->ch[j] = new TrieNode(); }
            p = p->ch[j];
        }
        p->isEnd = true;
    }

    // Returns if the word is in the trie.
    bool search(string word) {
        TrieNode *p = root;
        for (int i = 0; i < word.size(); i++) {
            int j = word[i] - 'a';
            if (!p->ch[j]) return false;
            p = p->ch[j];
        }
        return p->isEnd;
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix) {
        TrieNode *p = root;
        for (int i = 0; i < prefix.size(); i++) {
            int j = prefix[i] - 'a';
            if (!p->ch[j]) return false;
            p = p->ch[j];
        }
        return true;
    }

private:
    TrieNode* root;
};

// Your Trie object will be instantiated and called as such:
// Trie trie;
// trie.insert("somestring");
// trie.search("key");
