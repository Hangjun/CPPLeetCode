/*
Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.
*/

/*
The first solution is the use a priority queue. 

Time: O(n*logk); Space: O(k)
n = total number of nodes
k = number of lists
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
 
class MyCompare {
public:
    bool operator()(ListNode* a, ListNode* b) {
        return a->val > b->val;
    }
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode *dummyNode = new ListNode(-1);
        ListNode *head = dummyNode;
        priority_queue<ListNode*, vector<ListNode*>, MyCompare> minHeap;
        for (ListNode * l : lists) {
            if (l) minHeap.push((l));
        }
        
        while (!minHeap.empty()) {
            ListNode *curNode = minHeap.top();
            minHeap.pop();
            head->next = curNode;
            head = head->next;
            if (curNode->next) minHeap.push(curNode->next);
        }
        
        return dummyNode->next;
    }
};

/*
The second solution is to first implement the merge of 2 lists, and then use divide-and-conquer to recursively merge the k lists. Note that this problem requires in-place merge, unlike in Problem 21 (https://leetcode.com/problems/merge-two-sorted-lists/?tab=Description).
*/



