class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();
        if(n==1)return 1;
        if(n==2)return 2;
        int count = 0;
        while(n>0)
        {
            count++;
        n=n/2;
        }

        int power = count;
        int ans=1;
        int val = 2;
        while(power>0)
        {
            if(power%2)ans*=val;
            power/=2;
            if(power!=0)val=val*val;
        }
    return ans;
    }
};