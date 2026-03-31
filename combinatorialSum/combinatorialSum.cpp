#include <iostream>
#include <string>
#include <vector>

int combinatorialSum(std :: vector <int> &dp, std :: vector <int> &nums, int j){
    if(j == 0) return dp[0] = 1;
    if(dp[j] != -1) return dp[j];

    int count = 0;
    for(int i = 0; i < nums.size(); i++){
        if(nums[i] <= j){
            count += combinatorialSum(dp, nums, j - nums[i]);
        }
    }
    return dp[j] = count;
}

int CombinatorialSum(std :: vector <int> &nums, int target){
    std :: vector <int> dp(target + 1, 0);
    dp[0] = 1;
    for(int j = 1; j <= target; j++){
        int count = 0;
        for(int i = 0; i < nums.size(); i++){
            if(nums[i] <= j){
                count = count + dp[j - nums[i]];
            }
        }
        dp[j] = count;
    }
    return dp[target];
}

int main(){
    std :: vector <int> nums = {1, 2, 5};
    int t = 27;
    std :: vector <int> dp(t + 1, -1);
    int ans = combinatorialSum(dp, nums, t);
    int ans1 = CombinatorialSum(nums, t);
    std :: cout << "\nTotal ways to make " << t << ":\n" << ans << "\n" << ans1 << "\n";
    return 0;
}