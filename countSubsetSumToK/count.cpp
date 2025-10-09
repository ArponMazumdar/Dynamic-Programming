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

int main(){
    std :: vector <int> nums = {1, 2, 3, 4};
    int sum = 4;
    int n = nums.size();
    std :: vector <std :: vector <int>> dp(n, std :: vector <int>(sum + 1, -1));
    int ans = count(nums, dp, n, sum);
    std :: cout << ans << std :: endl;
}