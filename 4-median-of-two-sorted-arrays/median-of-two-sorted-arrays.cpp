#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>

class Solution {
public:
    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
        // Ensure nums1 is the smaller array to optimize the binary search range (m <= n).
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        }

        int m = nums1.size();
        int n = nums2.size();
        
        // half_len is the number of elements required on the left partition.
        // The +1 handles both odd and even total lengths correctly.
        int half_len = (m + n + 1) / 2;

        // Binary search range for the cut 'i' in nums1.
        int low = 0;
        int high = m;

        while (low <= high) {
            // i is the cut index for nums1 (number of elements from nums1 on the left)
            int i = low + (high - low) / 2;
            
            // j is the cut index for nums2 (derived from i and half_len)
            int j = half_len - i;

            // Get the boundary elements for comparison.
            // Use INT_MIN and INT_MAX to handle boundary cases (i=0, i=m, j=0, j=n).
            
            // L1 (Left of cut in nums1)
            long long L1 = (i == 0) ? LLONG_MIN : nums1[i - 1]; 
            // R1 (Right of cut in nums1)
            long long R1 = (i == m) ? LLONG_MAX : nums1[i];

            // L2 (Left of cut in nums2)
            long long L2 = (j == 0) ? LLONG_MIN : nums2[j - 1];
            // R2 (Right of cut in nums2)
            long long R2 = (j == n) ? LLONG_MAX : nums2[j];

            // Check the perfect partition conditions
            if (L1 <= R2 && L2 <= R1) {
                // Found the perfect partition!
                
                // If the total length is ODD, the median is the largest element on the left side.
                if ((m + n) % 2 != 0) {
                    return std::max(L1, L2);
                } 
                // If the total length is EVEN, the median is the average of the two middle elements.
                else {
                    long long left_max = std::max(L1, L2);
                    long long right_min = std::min(R1, R2);
                    return (left_max + right_min) / 2.0;
                }
            } 
            else if (L1 > R2) {
                // Cut in nums1 is too far right (L1 is too big). Move the cut left.
                high = i - 1;
            } 
            else { // L2 > R1
                // Cut in nums1 is too far left (L2 is too big relative to R1). Move the cut right.
                low = i + 1;
            }
        }
        
        // This line should technically never be reached due to problem constraints
        // guaranteeing a solution.
        return 0.0;
    }
};