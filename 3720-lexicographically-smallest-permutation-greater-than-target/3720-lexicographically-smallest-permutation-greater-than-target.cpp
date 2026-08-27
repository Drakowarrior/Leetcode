class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();

        // Frequency of characters in s
        vector<int> cnt(26, 0);

        for (char c : s) {
            cnt[c - 'a']++;
        }

        // Try the position where we make the string greater.
        // Rightmost position is preferred.
        for (int i = n - 1; i >= 0; i--) {

            // Rebuild the frequency array for this pivot.
            vector<int> remain = cnt;

            // Try to keep target[0 ... i-1] unchanged.
            bool possible = true;

            for (int j = 0; j < i; j++) {
                int x = target[j] - 'a';

                if (remain[x] == 0) {
                    possible = false;
                    break;
                }

                remain[x]--;
            }

            if (!possible)
                continue;

            // At position i, we need the smallest
            // available character strictly greater than target[i].
            int targetChar = target[i] - 'a';

            for (int c = targetChar + 1; c < 26; c++) {

                if (remain[c] == 0)
                    continue;

                string ans = target.substr(0, i);

                // Make the first difference here.
                ans += char('a' + c);

                remain[c]--;

                // Fill the rest in sorted order.
                for (int x = 0; x < 26; x++) {
                    ans.append(remain[x], char('a' + x));
                }

                return ans;
            }
        }

        return "";
    }
};