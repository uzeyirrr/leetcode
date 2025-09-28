#include <string>
#include <algorithm>
#include <iostream>

class Solution {
public:
    std::string pushDominoes(std::string dominoes) {
        int n = dominoes.length();
        // Prepend 'L' and append 'R' to handle edge cases easily.
        // The virtual 'L' at the beginning ensures any initial 'R' is opposed.
        // The virtual 'R' at the end ensures any final 'L' is opposed.
        // The length becomes n + 2.
        std::string s = 'L' + dominoes + 'R';

        // 'left' pointer marks the beginning of the current segment (the boundary force).
        // 'i' pointer iterates to find the end of the current segment (the opposing force).
        int left = 0; 

        for (int i = 1; i < n + 2; ++i) {
            // Find the right boundary force ('L' or 'R').
            if (s[i] == '.') {
                continue; // Still within a segment of standing dominoes.
            }
            
            // Now, s[left] and s[i] are the two boundary forces.
            // 'j' is the length of the segment of '.'s between s[left] and s[i].
            int j = i - left - 1; 

            if (j > 0) { // Only process if there are standing dominoes between the boundaries
                char left_char = s[left];
                char right_char = s[i];

                if (left_char == 'L' && right_char == 'L') {
                    // Case 2: L.....L -> All fall Left
                    // Update the segment between (left+1) and (i-1) to 'L'.
                    for (int k = left + 1; k < i; ++k) {
                        s[k] = 'L';
                    }
                } else if (left_char == 'R' && right_char == 'R') {
                    // Case 1: R.....R -> All fall Right
                    // Update the segment between (left+1) and (i-1) to 'R'.
                    for (int k = left + 1; k < i; ++k) {
                        s[k] = 'R';
                    }
                } else if (left_char == 'R' && right_char == 'L') {
                    // Case 4: R.....L -> Meet in the middle.
                    // j is the number of '.'s. The middle one (or two) stays '.'.
                    // For example: R...L (j=3). R R . L L
                    // Left half (j / 2) fall 'R', right half fall 'L'.
                    
                    // Fall Right: (left + 1) to (left + j / 2)
                    for (int k = left + 1; k <= left + j / 2; ++k) {
                        s[k] = 'R';
                    }
                    
                    // Fall Left: (i - 1) down to (i - j / 2)
                    // Note: If j is odd, the middle element at (left + j / 2 + 1) will remain '.'.
                    for (int k = i - 1; k >= i - j / 2; --k) {
                        s[k] = 'L';
                    }
                }
                // Case 3 (L.....R): No change, they all remain '.' which is their current state.
            }

            // Move the left pointer to the new boundary for the next segment.
            left = i;
        }

        // Return the final state, excluding the virtual 'L' and 'R' we added.
        return s.substr(1, n);
    }
};