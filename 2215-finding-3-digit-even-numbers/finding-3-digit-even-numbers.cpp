#include <vector>
#include <algorithm>
#include <cmath>

class Solution {
public:
    std::vector<int> findEvenNumbers(std::vector<int>& digits) {
        // Step 1: Count the frequency of each digit (0-9).
        std::vector<int> digit_counts(10, 0);
        for (int digit : digits) {
            digit_counts[digit]++;
        }
        
        std::vector<int> result;
        
        // Step 2: Iterate through all possible 3-digit even numbers (100 to 998, step 2).
        for (int num = 100; num <= 998; num += 2) {
            
            // Step 3: Extract the three digits (h, t, u) and check their frequency.
            int temp_num = num;
            
            // Create a temporary count for the current number's digits.
            // temp_counts[d] stores how many times digit 'd' is needed.
            std::vector<int> temp_counts(10, 0);
            
            // Extract the unit digit (u)
            temp_counts[temp_num % 10]++;
            temp_num /= 10;
            
            // Extract the ten digit (t)
            temp_counts[temp_num % 10]++;
            temp_num /= 10;
            
            // Extract the hundred digit (h)
            temp_counts[temp_num % 10]++;
            // Since we start from 100, we don't need to check for leading zeros.
            
            bool can_form = true;
            for (int d = 0; d <= 9; ++d) {
                // Check if the required count of digit 'd' (temp_counts[d])
                // is available in the input (digit_counts[d]).
                if (temp_counts[d] > digit_counts[d]) {
                    can_form = false;
                    break;
                }
            }
            
            if (can_form) {
                result.push_back(num);
            }
        }
        
        // The result will naturally be sorted because we iterated in ascending order.
        return result;
    }
};