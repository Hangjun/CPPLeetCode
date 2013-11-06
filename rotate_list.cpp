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
    int size (ListNode *L)
    {
        int len = 0;
        ListNode *p = L->next;
        while (p != NULL)
        {
            len++;
            p = p->next;
        }
        return len;
    }
    
    ListNode *rotateRight(ListNode *head, int k) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        typedef ListNode *List;
        typedef ListNode *Position;
        
        //add header node
        List L = new ListNode (0);
        L->next = head;
        
        int len = size(L);
        if (len == 0 || k <= 0)
            return L->next;
        int pivot = len - (k % len); //when k > len, LeetCode has the convention of rotating at len - (k%len) node...
        //find the pivoting node
        Position p = L->next;
        int count = 1;
        while (count < pivot)
        {
            count++;
            p = p->next;
        }
        Position rotateNode = p;
        
        while (p->next != NULL)
            p = p->next;
        Position tailNode = p;
        
        tailNode->next = L->next;
        L->next = rotateNode->next;
        rotateNode->next = NULL;
        
        return L->next;
    }
};
