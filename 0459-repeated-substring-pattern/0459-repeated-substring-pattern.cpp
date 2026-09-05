class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        string concatenated = s + s;
        return concatenated.substr(1, concatenated.length() - 2).find(s) != string::npos;
    }
};