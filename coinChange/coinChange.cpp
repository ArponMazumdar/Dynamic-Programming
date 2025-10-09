#include <iostream>
#include <vector>
#include <chrono>

int countSubsetSumToK(std :: vector <int> &coins, std :: vector <std :: vector <int>> &dp, int &n, int target, int i = 0){
    if(target == 0){
        return dp[i][target] = 1;
    }

    if(i == n - 1){
        return (target % coins[i] == 0 ? 1 : 0);
    }

    if(dp[i][target] != -1){
        //std :: cout << "recursion ID 0: dp[" << i << "][" << target << "] = " << dp[i][target] << std :: endl;  
        return dp[i][target];
    }

    int take = (target >= coins[i]) ? countSubsetSumToK(coins, dp, n, target - coins[i], i) : 0;
    int skip = countSubsetSumToK(coins, dp, n, target, i + 1);

    return dp[i][target] = take + skip;
}

int countSubsetSum_K(std :: vector <int> &coins, int &target){
    int n = coins.size();
    std :: vector <std :: vector <int>> dp (n, std :: vector <int>(target + 1, 0));

    for(int i = 1; i <= target; i++){
        if(i % coins[n - 1] == 0){
            dp[n - 1][i] = 1;
        }
    }

    for(int i = 0; i < n; i++){
        dp[i][0] = 1;
    }

    for(int i = n - 2; i >= 0; i--){
        for(int j = 1; j <= target; j++){
            int take = (j >= coins[i]) ? dp[i][j - coins[i]] : 0;
            int skip = dp[i + 1][j];
            dp[i][j] = take + skip;
        }
    }

    return dp[0][target];
}

int count_SubsetSumToK(std :: vector <int> &coins, int &target){
    int n = coins.size();
    std :: vector <int> dp(target + 1, 0);
    dp[0] = 1;
    
    for(int i = 1; i <= target; i++){
        if(i % coins[n - 1] == 0){
            dp[i] = 1;
        }
    }

    for(int i = n - 2; i >= 0; i--){
        for(int j = 1; j <= target; j++){
            int take = (j >= coins[i]) ? dp[j - coins[i]] : 0;
            int skip = dp[j];
            dp[j] = take + skip;
        }
    }

    return dp[target];
}

int count_subset_sum_to_k(std :: vector <int> &coins, std :: vector <std :: vector <int>> &dp, int &n, int target, int i = 0){
    if(target == 0){
        return 1;
    }

    if(i == n){
        return 0;
    }

    if(i == n - 1){
        return dp[i][target] = (target  % coins[i] == 0 ? 1 : 0);
    }

    int count = 0;
    for(int j = i; j < n; j++){
        if(dp[j][target] != -1){
            //std :: cout << "recursion ID 1: dp[" << j << "][" << target << "] = " << dp[j][target] << std :: endl;  
            count += dp[j][target];
            continue;
        }

        if(coins[j] <= target){
            dp[j][target] = count_subset_sum_to_k(coins, dp, n, target - coins[j], j);
            count += dp[j][target];
        }
    }
    return count;
}

int count_subset_sum_k(std :: vector < int > &coins, std :: vector <std :: vector < int >> &dp, int &n, int target, int i = 0){
    if(target == 0){
        return dp[i][0] = 1;
    }

    if(i == n - 1){
        return ((target % coins[i] == 0) ? 1 : 0);
    }

    if(dp[i][target] != -1){
        return dp[i][target];
    }

    int count = 0;
    for(int j = i; j < n; j++){
        count += ((coins[j] <= target) ? count_subset_sum_k(coins, dp, n, target - coins[j], j) : 0);
    }
    return dp[i][target] = count;
}

int main(){
    std :: vector <int> coins = {5, 1, 3, 2, 5, 7, 9};
    int target = 453;
    int n = coins.size();

    std :: vector <std :: vector <int>> dp (n, std :: vector <int>(target + 1, -1));
    auto s = std :: chrono :: high_resolution_clock :: now();
    int ans = countSubsetSumToK(coins, dp, n, target);
    auto e = std :: chrono :: high_resolution_clock :: now();
    std :: chrono :: duration < double > duration = e - s; 

    auto s_1 = std :: chrono :: high_resolution_clock :: now();
    int ans_1 = countSubsetSum_K(coins, target);
    auto e_1 = std :: chrono :: high_resolution_clock :: now();
    std :: chrono :: duration < double > duration_1 = e_1 - s_1;

    auto s_2 = std :: chrono :: high_resolution_clock :: now();
    int ans_2 = count_SubsetSumToK(coins, target);
    auto e_2 = std :: chrono :: high_resolution_clock :: now();
    std :: chrono :: duration < double > duration_2 = e_2 - s_2;

    dp.assign(n, std :: vector <int> (target + 1, -1));
    auto s_3 = std :: chrono :: high_resolution_clock :: now();
    int ans_3 = count_subset_sum_to_k(coins, dp, n, target);
    auto e_3 = std :: chrono :: high_resolution_clock :: now();
    std :: chrono :: duration < double > duration_3 = e_3 - s_3;

    dp.assign(n, std :: vector <int> (target + 1, -1));
    auto s_4 = std :: chrono :: high_resolution_clock :: now();
    int ans_4 = count_subset_sum_k(coins, dp, n, target);
    auto e_4 = std :: chrono :: high_resolution_clock :: now();
    std :: chrono :: duration <double> duration_4 = e_4 - s_4;

    std :: cout << ans << " " << duration.count() << std :: endl << ans_1 << " " << duration_1.count() << std :: endl << ans_2 << " " << duration_2.count() 
    << std :: endl << ans_3 << " " << duration_3.count() << std :: endl << ans_4 << " " << duration_4.count() << std :: endl; 
    return 0;
}