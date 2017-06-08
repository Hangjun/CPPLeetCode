/*
Design and implement a data structure for Least Frequently Used (LFU) cache. It should support the following operations: get and put.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
put(key, value) - Set or insert the value if the key is not already present. When the cache reaches its capacity, it should invalidate the least frequently used item before inserting a new item. For the purpose of this problem, when there is a tie (i.e., two or more keys that have the same frequency), the least recently used key would be evicted.

Follow up:
Could you do both operations in O(1) time complexity?

Example:

LFUCache cache = new LFUCache( 2 /* capacity */ );

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.get(3);       // returns 3.
cache.put(4, 4);    // evicts key 1.
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4
*/

class LFUCache {
public:
    LFUCache(int capacity) {
        cap = capacity;
        size = 0;
        minFreq = 0;
    }
    
    int get(int key) {
        if (cachePool.find(key) == cachePool.end()) return -1;
        int curVal = cachePool[key].first;
        
        // remove this cache node from the current frequency list as we are bumping it onto the next frequency list
        frequenceList[cachePool[key].second].erase(ht[key]);
        frequenceList[++cachePool[key].second].push_back(key);
        
        // need to adjuts ht[key]'s iterator pointer position to be the last cache node of list frequenceList[++curFreq]
        ht[key] = --frequenceList[cachePool[key].second].end();
        
        if (frequenceList[minFreq].empty()) minFreq++;
        
        return curVal;
    }
    
    void put(int key, int value) {
        if (cap <= 0) return;
        
        int curVal = get(key);
        if (curVal != -1) {
            cachePool[key].first = value;
            return;
        }
        
        if (size == cap) {
            // frequenceList[minFreq].front() is the key of the cache node to be evicted
            cachePool.erase(frequenceList[minFreq].front());
            ht.erase(frequenceList[minFreq].front());
            frequenceList[minFreq].pop_front();
            --size;
        } 
        
        cachePool[key] = make_pair(value, 1);
        frequenceList[1].push_back(key);
        ht[key] = --frequenceList[1].end();
        minFreq = 1;
            
        ++size;
    }
private:
    int size;
    int cap;
    int minFreq;
    unordered_map<int, pair<int, int>> cachePool; // key -> (value, frequency)
    unordered_map<int, list<int>::iterator> ht; // key -> cache node iterator
    unordered_map<int, list<int>> frequenceList; // frequency -> list of cache nodes
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache obj = new LFUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */
