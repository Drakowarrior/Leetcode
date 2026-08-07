#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
private:
    // Helper to calculate the minimum number of digits required to satisfy remaining factors
    int get_required_length(int c2, int c3, int c5, int c7) {
        int digits = c5 + c7; // 5 and 7 can only be formed by digits 5 and 7
        
        // Group 3s into 9s as much as possible
        int ones_from_3 = (c3 + 1) / 2; 
        
        // Optimize 2s and remaining 3s combined
        int min_23_digits = 1e9;
        // Brute force structural choices for 2s and 3s since counts are small
        for (int n9 = 0; n9 <= (c3 + 1) / 2; ++n9) {
            int rem3 = max(0, c3 - 2 * n9);
            for (int n8 = 0; n8 <= (c2 + 2) / 3; ++n8) {
                int rem2 = max(0, c2 - 3 * n8);
                // 2 and 3 can form a 6
                for (int n6 = 0; n6 <= min(rem2, rem3); ++n6) {
                    int r2 = rem2 - n6;
                    int r3 = rem3 - n6;
                    // Remaining 2s can form 4s
                    int n4 = (r2 + 1) / 2;
                    int n2 = r2 % 2;
                    min_23_digits = min(min_23_digits, n9 + n8 + n6 + n4 + n2 + r3);
                }
            }
        }
        return digits + (min_23_digits == 1e9 ? 0 : min_23_digits);
    }

    // Helper to generate the lexicographically smallest trailing string for remaining factors
    string get_min_suffix(int c2, int c3, int c5, int c7, int target_len) {
        string suff = "";
        // 5s and 7s are fixed
        while (c5 > 0) { suff += '5'; c5--; }
        while (c7 > 0) { suff += '7'; c7--; }
        
        string best_23 = "";
        int min_len = 1e9;
        
        // Find combination of digits 2, 3, 4, 6, 8, 9 with minimal length and lexicographically smallest layout
        for (int n9 = 0; n9 <= 30; ++n9) {
            for (int n8 = 0; n8 <= 30; ++n8) {
                for (int n6 = 0; n6 <= 1; ++n6) { // at most one 6 is needed for pairing optimally
                    for (int n4 = 0; n4 <= 2; ++n4) {
                        for (int n2 = 0; n2 <= 2; ++n2) {
                            for (int n3 = 0; n3 <= 1; ++n3) {
                                int total_2 = 3 * n8 + n6 + 2 * n4 + n2;
                                int total_3 = 2 * n9 + n6 + n3;
                                if (total_2 >= c2 && total_3 >= c3) {
                                    int len = n9 + n8 + n6 + n4 + n2 + n3;
                                    if (len < min_len) {
                                        min_len = len;
                                        best_23 = string(n2, '2') + string(n3, '3') + string(n4, '4') +
                                                  string(n6, '6') + string(n8, '8') + string(n9, '9');
                                    } else if (len == min_len) {
                                        string curr = string(n2, '2') + string(n3, '3') + string(n4, '4') +
                                                      string(n6, '6') + string(n8, '8') + string(n9, '9');
                                        if (curr < best_23) best_23 = curr;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        
        suff += best_23;
        sort(suff.begin(), suff.end());
        
        // Pad with '1's at the front to reach target length if allowed
        if (suff.length() < target_len) {
            suff = string(target_len - suff.length(), '1') + suff;
        }
        return suff;
    }

public:
    string smallestNumber(string num, long long t) {
        int c2 = 0, c3 = 0, c5 = 0, c7 = 0;
        while (t % 2 == 0) { c2++; t /= 2; }
        while (t % 3 == 0) { c3++; t /= 3; }
        while (t % 5 == 0) { c5++; t /= 5; }
        while (t % 7 == 0) { c7++; t /= 7; }
        if (t > 1) return "-1"; // Contains invalid primes like 11, 13

        int n = num.length();
        vector<int> req2(n + 1, 0), req3(n + 1, 0), req5(n + 1, 0), req7(n + 1, 0);
        req2[0] = c2; req3[0] = c3; req5[0] = c5; req7[0] = c7;

        // Step 1: Push forward matching num's prefix
        int match_len = 0;
        for (int i = 0; i < n; ++i) {
            int d = num[i] - '0';
            if (d == 0) break; // Cannot match 0
            
            // Track factors contributed by current digit
            int r2 = req2[i], r3 = req3[i], r5 = req5[i], r7 = req7[i];
            if (d == 2 || d == 6 || d == 4 || d == 8) {
                if (d == 2) r2--;
                else if (d == 4) r2 -= 2;
                else if (d == 6) { r2--; r3--; }
                else if (d == 8) r2 -= 3;
            }
            if (d == 3 || d == 9) {
                if (d == 3) r3--;
                else if (d == 9) r3 -= 2;
            }
            if (d == 5) r5--;
            if (d == 7) r7--;

            req2[i + 1] = max(0, r2);
            req3[i + 1] = max(0, r3);
            req5[i + 1] = max(0, r5);
            req7[i + 1] = max(0, r7);
            match_len++;
        }

        // If the entire string matches perfectly and satisfies t
        if (match_len == n && req2[n] == 0 && req3[n] == 0 && req5[n] == 0 && req7[n] == 0) {
            return num;
        }

        // Step 2: Backtrack to find the first position we can increment
        for (int i = match_len; i >= 0; --i) {
            int start_digit = (i == n) ? 10 : (num[i] - '0' + 1);
            for (int d = start_digit; d <= 9; ++d) {
                int r2 = req2[i], r3 = req3[i], r5 = req5[i], r7 = req7[i];
                if (d == 2) r2--;
                else if (d == 3) r3--;
                else if (d == 4) r2 -= 2;
                else if (d == 5) r5--;
                else if (d == 6) { r2--; r3--; }
                else if (d == 7) r7--;
                else if (d == 8) r2 -= 3;
                else if (d == 9) r3 -= 2;

                r2 = max(0, r2); r3 = max(0, r3); r5 = max(0, r5); r7 = max(0, r7);
                int rem_len = n - 1 - i;
                if (get_required_length(r2, r3, r5, r7) <= rem_len) {
                    string ans = num.substr(0, i) + to_string(d);
                    ans += get_min_suffix(r2, r3, r5, r7, rem_len);
                    return ans;
                }
            }
        }

        // Step 3: If no same-length configuration fits, increase the overall string length
        int new_len = max(n + 1, get_required_length(c2, c3, c5, c7));
        return get_min_suffix(c2, c3, c5, c7, new_len);
    }
};