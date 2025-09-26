#include <vector>
#include <algorithm>
#include <iostream>

class Solution {
public:
    /**
     * Finds the number of triplets that can form a valid triangle.
     * @param nums The integer array of potential side lengths.
     * @return The total count of valid triangle triplets.
     */
    int triangleNumber(std::vector<int>& nums) {
        int n = nums.size();
        if (n < 3) {
            return 0;
        }

        // 1. Sort the array. This is crucial for the O(n^2) two-pointer approach.
        std::sort(nums.begin(), nums.end());

        int count = 0;

        // 2. Iterate for the potential longest side 'c' (nums[i]).
        // We start i from index 2, as a triangle needs at least 3 elements.
        for (int i = n - 1; i >= 2; --i) {
            // 'c' is the largest side, nums[i]
            
            // 3. Use two pointers to search for sides 'a' (nums[left]) and 'b' (nums[right]) 
            // in the subarray nums[0...i-1].
            int left = 0;
            int right = i - 1;
            
            while (left < right) {
                // Check the only required condition: a + b > c
                if (nums[left] + nums[right] > nums[i]) {
                    // 4. Count Valid Pairs
                    
                    // Since the array is sorted, if nums[left] + nums[right] > nums[i] is true,
                    // then for any element k between left and right (left <= k < right), 
                    // nums[k] + nums[right] will also be > nums[i].
                    
                    // The number of such valid pairs is (right - left).
                    count += (right - left);
                    
                    // Since we've counted all possible valid 'a's (from left to right-1) 
                    // with the current nums[right], we can decrease 'right' to look for a smaller 'b'.
                    right--;
                } else {
                    // nums[left] is too small. Increase 'left' to find a larger 'a'.
                    left++;
                }
            }
        }

        return count;
    }
};