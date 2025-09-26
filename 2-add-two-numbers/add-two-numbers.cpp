class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // Create a dummy node to act as the starting point of the new list.
        // This simplifies handling the head of the list.
        ListNode* dummyHead = new ListNode(0);
        
        // 'current' pointer will build the result list.
        ListNode* current = dummyHead;
        
        // 'p' and 'q' are pointers to traverse l1 and l2.
        ListNode* p = l1;
        ListNode* q = l2;
        
        // Initialize carry to 0.
        int carry = 0;
        
        // Loop continues as long as there are digits in either list OR a carry remains.
        while (p != nullptr || q != nullptr || carry != 0) {
            
            // Get the value of the current nodes, defaulting to 0 if the list is exhausted.
            int x = (p != nullptr) ? p->val : 0;
            int y = (q != nullptr) ? q->val : 0;
            
            // Calculate the sum of the digits and the previous carry.
            int sum = x + y + carry;
            
            // Update the carry for the next iteration (1 or 0).
            carry = sum / 10;
            
            // The digit for the current node is the remainder of the sum.
            int digit = sum % 10;
            
            // Create a new node with the calculated digit and attach it to the result list.
            current->next = new ListNode(digit);
            
            // Advance the current pointer to the newly created node.
            current = current->next;
            
            // Move the list pointers forward if they are not null.
            if (p != nullptr) {
                p = p->next;
            }
            if (q != nullptr) {
                q = q->next;
            }
        }
        
        // The result is the node immediately following the dummy head.
        // Note: The problem requires memory management, but in a typical competitive programming
        // environment, we only return the head of the new list.
        ListNode* result = dummyHead->next;
        delete dummyHead; // Clean up the temporary dummy head
        
        return result;
    }
};