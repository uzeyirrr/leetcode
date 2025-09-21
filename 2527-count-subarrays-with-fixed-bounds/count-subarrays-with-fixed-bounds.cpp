#include <vector>
#include <algorithm>

class Solution {
public:
    long long countSubarrays(std::vector<int>& nums, int minK, int maxK) {
        long long count = 0;
        int bad_idx = -1;
        int min_idx = -1;
        int max_idx = -1;

        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] < minK || nums[i] > maxK) {
                bad_idx = i;
            }
            if (nums[i] == minK) {
                min_idx = i;
            }
            if (nums[i] == maxK) {
                max_idx = i;
            }

            // Calculate the number of valid subarrays ending at index i
            // The start of the subarray must be after the last "bad" element
            // and include both minK and maxK.
            int start = std::min(min_idx, max_idx);
            long long valid_subarrays = start - bad_idx;

            if (valid_subarrays > 0) {
                count += valid_subarrays;
            }
        }
        return count;
    }
};