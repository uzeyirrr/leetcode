#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

class Solution {
public:
    int numEquivDominoPairs(std::vector<std::vector<int>>& dominoes) {
        // Use an array to store the frequency of normalized dominoes.
        // Since values are 1-9, the normalized domino (min, max) will form a 
        // unique integer key between 11 (for [1,1]) and 99 (for [9,9]).
        // An array of size 100 is sufficient, indexed from 0 to 99.
        std::vector<int> counts(100, 0);
        int equivalent_pairs = 0;

        // 1. Normalize and Count Frequencies
        for (const auto& domino : dominoes) {
            int a = domino[0];
            int b = domino[1];

            // Normalize: Ensure the smaller number comes first.
            int min_val = std::min(a, b);
            int max_val = std::max(a, b);

            // Create a unique key: 10 * min + max
            // e.g., [1, 2] -> 12, [2, 1] -> 12, [3, 4] -> 34, [7, 7] -> 77
            int key = min_val * 10 + max_val;

            // Increment the count for this normalized domino.
            counts[key]++;
        }

        // 2. Calculate the Number of Pairs
        // For a domino that appears 'k' times, the number of pairs (i, j) where i < j is
        // the combination "k choose 2", which is k * (k - 1) / 2.
        for (int count : counts) {
            if (count >= 2) {
                // Formula: k * (k - 1) / 2
                equivalent_pairs += count * (count - 1) / 2;
            }
        }

        return equivalent_pairs;
    }
};