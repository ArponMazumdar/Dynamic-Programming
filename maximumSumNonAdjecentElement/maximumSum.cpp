#include <iostream>
#include <vector>
#include <climits>

int maxSum(std :: vector <int> &nums, std :: vector <int> &dp, int &len, int n = 0){
    if(n >= len){
        return 0;
    }

    if(n == len - 1){
        return dp[n] = nums[n];
    }

    if(dp[n] != -1){
        return dp[n];
    }

    int ans = 0;
    int max = INT_MIN;
    for(int i = n; i < len; i++){
        ans = (dp[i] == -1) ? nums[i] + maxSum(nums, dp, len, i + 2) : dp[i];
        max = std :: max(ans, max);
        ans = 0;
    }
    return dp[n] = max;
}

int maximumSum(std :: vector <int> &nums){
    int n = nums.size();
    std :: vector <int> dp(n, 0);
    dp[n - 1] = nums[n - 1];

    int curr_Sum = 0;
    int curr_Max = INT_MIN;
    for(int i = n - 2; i >= 0; i--){
        for(int j = i; j < n; j++){
            curr_Sum = nums[j];
            curr_Sum += (j + 2 < n) ? dp[j + 2] : 0; 
            curr_Max = std :: max(curr_Max, curr_Sum);
        }
        dp[i] = curr_Max;
        curr_Max = INT_MIN;
    }

    return dp[0];
}

int max_sum(std :: vector <int> &nums, std :: vector <int> &dp, int &n, int i = 0){
    if(i == n - 1) return nums[i];
    if(i >= n) return 0;
    if(dp[i] != -1) return dp[i];

    int add = nums[i] + max_sum(nums, dp, n, i + 2);
    int skip = max_sum(nums, dp, n, i + 1);

    return dp[i] = std :: max(add, skip);
}

int maximum_sum(std :: vector <int> &nums){
    int n = nums.size();
    std :: vector <int> dp(n, 0);
    dp[n - 1] = nums[n - 1];

    for(int i = n - 2; i >= 0; i--){
        int add = nums[i] + (i + 2 < n ? dp[i + 2] : 0);
        int skip = dp[i + 1];

        dp[i] = std :: max(add, skip);
    }

    return dp[0];
}

int main(){
    std :: vector <int> nums = {1, 3, 6, 7, 2, 11, 5, 17, 1, 94, 7, 2, 9, 1, 8, 5, 11, 2};
    int len = nums.size();

    std :: vector <int> dp(len, -1);
    int ans_1 = maxSum(nums, dp, len);
    int ans_2 = maximumSum(nums);
    dp.assign(len, -1);
    int ans_3 = max_sum(nums, dp, len);
    int ans_4 = maximum_sum(nums);

    std :: cout << "maximum sum of non adjacent element: " << std :: endl << ans_1 << std :: endl << ans_2 << std :: endl << ans_3 << std :: endl << ans_4 << std :: endl;
    return 0;
}