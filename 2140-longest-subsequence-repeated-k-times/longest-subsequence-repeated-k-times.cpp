#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

class Solution {
private:
    // Helper function to check if `sub` repeated `k` times is a subsequence of `s`.
    bool isSubsequenceCheck(const std::string& s, int k, const std::string& sub) {
        std::string repeated_sub;
        repeated_sub.reserve(sub.length() * k);
        for(int i = 0; i < k; ++i) {
            repeated_sub += sub;
        }

        int s_ptr = 0;
        int sub_ptr = 0;

        while(s_ptr < s.length() && sub_ptr < repeated_sub.length()) {
            if (s[s_ptr] == repeated_sub[sub_ptr]) {
                sub_ptr++;
            }
            s_ptr++;
        }
        return sub_ptr == repeated_sub.length();
    }

public:
    std::string longestSubsequenceRepeatedK(std::string s, int k) {
        std::map<char, int> counts;
        for (char c : s) {
            counts[c]++;
        }

        std::string valid_chars = "";
        for (char c = 'z'; c >= 'a'; --c) {
            if (counts[c] >= k) {
                valid_chars += c;
            }
        }

        std::string ans = "";
        std::queue<std::string> q;
        q.push("");

        while (!q.empty()) {
            // Get all candidates of the current length
            int level_size = q.size();
            std::string level_ans = "";

            for (int i = 0; i < level_size; ++i) {
                std::string current_sub = q.front();
                q.pop();

                for (char c : valid_chars) {
                    std::string next_sub = current_sub + c;
                    if (isSubsequenceCheck(s, k, next_sub)) {
                        q.push(next_sub);
                        if (next_sub.length() > ans.length()) {
                            ans = next_sub;
                        } else if (next_sub.length() == ans.length() && next_sub > ans) {
                            ans = next_sub;
                        }
                    }
                }
            }
        }
        return ans;
    }
};