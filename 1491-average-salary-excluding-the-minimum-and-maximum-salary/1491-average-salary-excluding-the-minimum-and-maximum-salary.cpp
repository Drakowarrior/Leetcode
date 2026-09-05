class Solution {
public:
    double average(vector<int>& salary) {
        int sum = 0;
        for(int i = 0;i < salary.size();i++){
            sum += salary[i];
        }

        int minimum = *min_element(salary.begin(),salary.end());
        int maximum = *max_element(salary.begin(),salary.end());

        sum = sum - minimum - maximum;
        return (double) sum / (salary.size()-2);
    }
};