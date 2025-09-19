class Solution {
public:
    int countLargestGroup(int n) {
        // Helper function to calculate sum of digits
        auto digitSum = [](int num) {
            int sum = 0;
            while (num > 0) {
                sum += num % 10;
                num /= 10;
            }
            return sum;
        };
        
        // Count frequency of each digit sum
        unordered_map<int, int> digitSumCount;
        
        for (int i = 1; i <= n; i++) {
            int ds = digitSum(i);
            digitSumCount[ds]++;
        }
        
        // Find the maximum group size
        int maxSize = 0;
        for (const auto& pair : digitSumCount) {
            maxSize = max(maxSize, pair.second);
        }
        
        // Count how many groups have the maximum size
        int result = 0;
        for (const auto& pair : digitSumCount) {
            if (pair.second == maxSize) {
                result++;
            }
        }
        
        return result;
    }
};