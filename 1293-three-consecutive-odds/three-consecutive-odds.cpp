#include <vector>

class Solution {
public:
    bool threeConsecutiveOdds(std::vector<int>& arr) {
        int consecutive_odd_count = 0;
        
        for (int num : arr) {
            // Check if the current number is odd: num % 2 != 0
            if (num % 2 != 0) {
                // It's odd, so increment the count
                consecutive_odd_count++;
                
                // Check if we've found three consecutive odds
                if (consecutive_odd_count == 3) {
                    return true;
                }
            } else {
                // It's even, so the sequence of consecutive odds is broken
                // Reset the count to 0
                consecutive_odd_count = 0;
            }
        }
        
        // If the loop finishes without the count reaching 3
        return false;
    }
};