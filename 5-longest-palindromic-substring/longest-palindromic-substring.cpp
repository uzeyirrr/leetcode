#include <string>
#include <iostream>
#include <algorithm>

class Solution {
private:
    /**
     * Helper function to expand around a center (left, right)
     * and update the longest palindrome found so far.
     * @param s The input string.
     * @param left The initial left index of the center.
     * @param right The initial right index of the center.
     * @param start A reference to the starting index of the longest palindrome found.
     * @param maxLen A reference to the length of the longest palindrome found.
     */
    void expandAroundCenter(const std::string& s, int left, int right, int& start, int& maxLen) {
        // Expand as long as the indices are within bounds and the characters match
        while (left >= 0 && right < s.length() && s[left] == s[right]) {
            left--;
            right++;
        }

        // The 'while' loop breaks one step *after* the longest palindrome is found.
        // The indices were (left+1) and (right-1) for the actual palindrome boundaries.
        // Current length is (right-1) - (left+1) + 1 = right - left - 1
        int currentLen = right - left - 1;

        // Update the longest palindrome if the current one is longer
        if (currentLen > maxLen) {
            maxLen = currentLen;
            // The starting index of the new longest palindrome is left + 1
            start = left + 1;
        }
    }

public:
    std::string longestPalindrome(std::string s) {
        if (s.length() < 2) {
            return s;
        }

        int start = 0; // Stores the starting index of the longest palindromic substring
        int maxLen = 1; // Stores the length of the longest palindromic substring

        // Iterate through all possible centers
        for (int i = 0; i < s.length(); ++i) {
            // Case 1: Odd length palindrome (center is a single character s[i])
            expandAroundCenter(s, i, i, start, maxLen);

            // Case 2: Even length palindrome (center is between s[i] and s[i+1])
            expandAroundCenter(s, i, i + 1, start, maxLen);
        }

        // Return the longest palindromic substring
        // s.substr(start, length) returns the substring starting at 'start' of 'maxLen' length.
        return s.substr(start, maxLen);
    }
};

