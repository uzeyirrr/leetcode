#include <iostream>
#include <string>
#include <algorithm>

class Solution {
public:
    int longestSubsequence(std::string s, int k) {
        int n = s.length();
        int count_zeros = 0;
        
        // Count all the '0's in the string.
        for (char c : s) {
            if (c == '0') {
                count_zeros++;
            }
        }
        
        long long current_value = 0;
        long long power_of_2 = 1;
        
        // Start with the length of all '0's. The value is 0.
        int length = count_zeros;
        
        // Iterate from right to left to add '1's greedily.
        for (int i = n - 1; i >= 0; --i) {
            if (s[i] == '1') {
                // Check for potential overflow before adding.
                if (current_value + power_of_2 <= k) {
                    current_value += power_of_2;
                    length++;
                } else {
                    // If adding the '1' makes the number too large,
                    // any further '1's to the left will be even larger.
                    // We can stop here.
                    break;
                }
            }
            
            // Prepare for the next digit to the left.
            if (power_of_2 > k) {
                 break;
            }
            power_of_2 *= 2;
        }
        
        return length;
    }
};