/*
A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.

Return a deep copy of the list. 
*/

/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        if (!head) return NULL;
        RandomListNode *dummyNode = new RandomListNode(-1);
        
        RandomListNode *copyHead = dummyNode;
        unordered_map<RandomListNode *, RandomListNode *> ht;
        RandomListNode *curNode = head;
        
        while (curNode) {
            copyHead->next = new RandomListNode(curNode->label);
            copyHead = copyHead->next;
            ht[curNode] = copyHead;
            curNode = curNode->next;
        }
        
        curNode = head;
        while (curNode) {
            ht[curNode]->random = ht[curNode->random];
            curNode = curNode->next;
        }
        
        return dummyNode->next;
    }
};
