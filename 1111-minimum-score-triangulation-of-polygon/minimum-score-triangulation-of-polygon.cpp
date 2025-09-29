#include <vector>
#include <algorithm>
#include <climits>

class Solution {
public:
    int minScoreTriangulation(std::vector<int>& values) {
        int n = values.size();
        
        // DP[i][j] stores the minimum score to triangulate the polygon 
        // formed by vertices values[i], values[i+1], ..., values[j].
        // Note: For a valid polygon, we must have j > i + 1.
        std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));

        // L is the length of the diagonal (j - i). 
        // L = 2 means j = i + 2, which is the smallest sub-polygon (a single triangle).
        // L ranges from 2 up to n - 1.
        for (int L = 2; L < n; ++L) {
            // i is the starting vertex index.
            // j is the ending vertex index.
            for (int i = 0; i < n - L; ++i) {
                int j = i + L;
                
                // Initialize dp[i][j] to a large value (INT_MAX)
                dp[i][j] = INT_MAX;
                
                // k is the intermediate vertex used to form the base triangle (i, k, j).
                // i < k < j must hold.
                for (int k = i + 1; k < j; ++k) {
                    
                    // The score for this choice of k is:
                    // 1. Weight of the triangle (i, k, j): values[i] * values[k] * values[j]
                    // 2. Minimum score to triangulate sub-polygon (i to k): dp[i][k]
                    // 3. Minimum score to triangulate sub-polygon (k to j): dp[k][j]
                    
                    int current_score = values[i] * values[k] * values[j] + dp[i][k] + dp[k][j];
                    
                    // Update the minimum score for the polygon (i to j).
                    dp[i][j] = std::min(dp[i][j], current_score);
                }
            }
        }

        // The minimum score for the entire polygon is DP[0][n-1].
        return dp[0][n - 1];
    }
};