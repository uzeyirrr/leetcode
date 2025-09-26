#include <string>
#include <unordered_set>
#include <algorithm>
#include <iostream>

class Solution {
public:
    int lengthOfLongestSubstring(std::string s) {
        int n = s.length();
        if (n == 0) {
            return 0;
        }

        // Use an unordered_set to quickly check for duplicate characters within the current window.
        std::unordered_set<char> char_set;
        
        int max_len = 0;
        int left = 0; // The left boundary of the sliding window

        // The right pointer iterates through the entire string, expanding the window.
        for (int right = 0; right < n; ++right) {
            
            // 1. Handle Duplicates: While the current character s[right] is already in the set,
            // we must shrink the window from the left.
            while (char_set.count(s[right])) {
                // Remove the character at the left pointer
                char_set.erase(s[left]);
                
                // Move the left boundary to the right
                left++;
            }
            
            // 2. Expand Window: Add the new character to the set.
            char_set.insert(s[right]);
            
            // 3. Update Max Length: Calculate the current window size (right - left + 1) 
            // and update the maximum length found so far.
            // (right - left) is the current size of the set/window.
            max_len = std::max(max_len, right - left + 1);
        }

        return max_len;
    }
};