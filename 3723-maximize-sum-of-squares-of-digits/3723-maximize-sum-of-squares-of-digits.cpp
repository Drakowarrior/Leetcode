class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        if (sum > 9 * num) return "";  // even all 9s can't reach the sum
        int nines = sum / 9, rest = sum % 9;
        return (string(nines, '9') + char('0' + rest) + string(num, '0')).substr(0, num);  // 9s, then the rest, then zeros
    }
};