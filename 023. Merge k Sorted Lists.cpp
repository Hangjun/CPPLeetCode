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
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) return NULL;
        int curSize = lists.size();
        while (curSize > 1) {
            int halfSize = (1 + curSize) / 2;
            // merge i and i+halfSize
            for (int i = 0; i < curSize && i + halfSize < curSize; i++) {
                ListNode *res = mergeTwoLists(lists[i], lists[i+halfSize]);
                lists[i] = res;
            }
            curSize = halfSize;
        }
        return lists[0];
    }
    
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *dummyNode = new ListNode(-1);
        ListNode *prevNode = dummyNode;
        prevNode->next = l1;
        
        while (l1 && l2) {
            if (l1->val < l2->val) {
                l1 = l1->next;
            } else {
                ListNode *tmp = l2->next;
                prevNode->next = l2;
                l2->next = l1;
                l2 = tmp;
            }
            prevNode = prevNode->next;
        }
        
        if (l2) prevNode->next = l2;
        return dummyNode->next;
    }
};
