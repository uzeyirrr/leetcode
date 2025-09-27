#include <climits> // For INT_MAX and INT_MIN
#include <algorithm>
#include <string>

class Solution {
public:
    /**
     * Reverses the digits of a signed 32-bit integer x, checking for overflow.
     * * @param x The 32-bit signed integer to reverse.
     * @return The reversed integer, or 0 if overflow occurs.
     */
    int reverse(int x) {
        int reversed = 0;

        // Iterate until all digits of x have been processed.
        while (x != 0) {
            
            // 1. Get the last digit (pop)
            int pop = x % 10;
            
            // 2. Remove the last digit from x
            x /= 10;

            // 3. Overflow/Underflow check before multiplying 'reversed' by 10
            
            // Check for potential positive overflow (INT_MAX = 2,147,483,647)
            if (reversed > INT_MAX / 10) {
                return 0;
            }
            // Check for the boundary case where reversed * 10 is at INT_MAX - 7,
            // but adding the final digit (pop > 7) causes overflow.
            if (reversed == INT_MAX / 10 && pop > 7) {
                return 0;
            }

            // Check for potential negative underflow (INT_MIN = -2,147,483,648)
            if (reversed < INT_MIN / 10) {
                return 0;
            }
            // Check for the boundary case where reversed * 10 is at INT_MIN + 8,
            // but adding the final digit (pop < -8) causes underflow.
            if (reversed == INT_MIN / 10 && pop < -8) {
                return 0;
            }

            // 4. Update the reversed number
            reversed = reversed * 10 + pop;
        }

        return reversed;
    }
};
