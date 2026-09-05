class Solution {
public:
    int signFunc(int n){
        if(n % 2 == 0){
            return 1;
        }
        else{
            return -1;
        }
    }
    int arraySign(vector<int>& nums) {
        int negs = 0;
        for(int i = 0;i<nums.size();i++){
            if(nums[i]<0){
                negs++;
            }
            else if (nums[i] == 0){
                return 0;
            }
        };
        return signFunc(negs);
    }
};