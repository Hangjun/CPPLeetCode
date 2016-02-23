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
        if (head == NULL) return head;
        RandomListNode *dummyNode = new RandomListNode(0);
        unordered_map<RandomListNode *, RandomListNode *> ht;

        RandomListNode *p = head;
        RandomListNode *q = dummyNode;
        while (p != NULL) {
            q->next = new RandomListNode(p->label);
            q = q->next;
            ht[p] = q;
            p = p->next;
        }
        
        p = head;
        q = dummyNode->next;
        while (p != NULL) {
            q->random = ht[p->random];
            p = p->next;
            q = q->next;
        }
        
        return dummyNode->next;
    }
};

