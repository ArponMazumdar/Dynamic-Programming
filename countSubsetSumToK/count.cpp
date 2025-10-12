#include <iostream>
#include <vector>

int count(std :: vector <int> &nums, std :: vector <std :: vector <int>> &dp, int &n, int sum, int i = 0){
    if(sum == 0){
        return 1;
    }

    if(i == n - 1){
        return (sum == nums[i]) ? 1 : 0;
    }

    if(dp[i][sum] != -1){
        //std::cout << "recomputation case hit for " << i << ", " << sum << std :: endl;
        return dp[i][sum];
    }

    int counter = 0;
    for(int j = i; j < n; j++){
        if(sum >= nums[j]){
            counter += count(nums, dp, n, sum - nums[j], j);
        }
    }
    return dp[i][sum] = counter;
}

int cnt(int &n, std :: vector <int> &nums){
    int len = nums.size();
    std :: vector <std :: vector <int>> dp(len, std :: vector <int> (n + 1, 0));

    for(int i = 0; i < len; i++){
        dp[i][0] = 1;
    }

    for(int i = len - 1; i >= 0; i--){
        for(int j = 1; j <= n; j++){
            dp[i][j] += (j >= nums[i]) ? dp[i][j - nums[i]] : 0;
            dp[i][j] += (i + 1 < len) ? dp[i + 1][j] : 0; 
        }
    }

    return dp[0][n];
}

int main(){
    std :: vector <int> nums = {1, 2, 4, 5, 8, 11, 9};
    int sum = 17;
    int n = nums.size();
    std :: vector <std :: vector <int>> dp(n, std :: vector <int>(sum + 1, -1));
    int ans = count(nums, dp, n, sum);
    int ans_1 = cnt(sum, nums);
    std :: cout << ans << std :: endl
    << ans_1 << std :: endl;

    return 0;
}