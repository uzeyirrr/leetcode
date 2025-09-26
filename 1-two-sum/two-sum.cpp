#include <vector>
#include <unordered_map>
#include <iostream>

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        // Create an unordered_map to store the number and its index.
        // Key: The number itself
        // Value: The index of that number in the nums array
        std::unordered_map<int, int> num_map;
        
        // Iterate through the array
        for (int i = 0; i < nums.size(); ++i) {
            int current_num = nums[i];
            
            // Calculate the required complement
            int complement = target - current_num;
            
            // 1. Check if the complement exists in the map
            // The 'find' operation is O(1) average time complexity.
            if (num_map.count(complement)) {
                // If the complement exists, we've found the solution!
                // The index of the complement is num_map[complement]
                // The index of the current number is i
                return {num_map[complement], i};
            }
            
            // 2. If the complement is not found, add the current number and its index to the map
            num_map[current_num] = i;
        }
        
        // As per constraints, a solution always exists.
        // This return is just to satisfy function signature for non-void functions.
        return {}; 
    }
};