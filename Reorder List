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
    ListNode *lastNode (ListNode *head)
    {
        ListNode *p = head;
        if (p == NULL)
        {
            return NULL;
        }
        while (p->next != NULL)
        {
            p = p->next;
        }
        return p;
    }
    
    ListNode *prevNode (ListNode *head, ListNode *query)
    {
        ListNode *p = head;
        if (p == NULL || p->next == NULL)
            return NULL;
            
        //p != NULL and p->next != NULL; scan through the list            
        while (p->next != NULL && p->next != query)
        {
            p = p->next;
        }
        if (p->next == NULL)
        {
            cerr << "query node does not exist in the linked list!" << endl;
            return NULL;
        }
        
        return p;
    }
    
    void reorderList(ListNode *head) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        typedef ListNode *Position;
        Position p = head;
        vector<Position> nodes;
        int size = 0;
        //store all the nodes in the linked list in the nodes vector
        while (p != NULL)
        {
            size++;
            nodes.push_back (p);
            p = p->next;
        }
        if (size >= 2)
        {
            vector<Position>::size_type lastNode = size - 1;
            p = head; //start over scanning the list
            while (p != NULL && p->next != NULL)
            {
                Position tail = nodes[lastNode];
                if (p->next != tail)//swap the last node to the next of p
            {
                //since we inserted the last node to the front, we have to adjust the last pointer
                Position secondToLast = nodes[lastNode - 1];
                tail->next = p->next;
                p->next = tail;
                p = tail->next; //update p
                secondToLast->next = NULL;
                lastNode--;
            }
            else //p and tail are adjacent now, we are done
                break;
            }//endwhile
        }//endif
    }
};
