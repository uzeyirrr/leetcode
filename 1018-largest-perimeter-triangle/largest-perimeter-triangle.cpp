#include <vector>
#include <algorithm>
#include <iostream>

class Solution {
public:
    /**
     * @brief Finds the largest perimeter of a triangle with a non-zero area.
     * * @param nums The integer array of side lengths.
     * @return The largest perimeter, or 0 if no such triangle can be formed.
     */
    int largestPerimeter(std::vector<int>& nums) {
        // 1. Sort the array in non-decreasing order.
        // Sorting allows us to easily check the largest possible side lengths first.
        std::sort(nums.begin(), nums.end());

        // The length of the array.
        int n = nums.size();

        // 2. Iterate from the back of the sorted array.
        // We look for three consecutive sides: a = nums[i-2], b = nums[i-1], c = nums[i].
        // We start i from n-1, so i-2 >= 0 is ensured by the loop condition i >= 2.
        for (int i = n - 1; i >= 2; --i) {
            long long c = nums[i];      // The longest side
            long long b = nums[i-1];    // The second longest side
            long long a = nums[i-2];    // The shortest side
            
            // 3. Check the Triangle Inequality Theorem: a + b > c.
            // Using long long for the sum prevents potential overflow, although 
            // the maximum possible sum (2 * 10^6) is within a standard int range.
            if (a + b > c) {
                // The first triplet found (a, b, c) from the largest available 
                // numbers guarantees the largest possible perimeter.
                return (int)(a + b + c);
            }
        }

        // 4. If no valid triangle is found after checking all possible triplets, return 0.
        return 0;
    }
};