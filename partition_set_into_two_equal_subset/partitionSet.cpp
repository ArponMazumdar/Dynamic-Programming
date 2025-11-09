#include <iostream>
#include <vector>
#include <numeric>

int countEqualPartitions(std :: vector <std :: vector <int>> &dp, std :: vector <int> &set, int sum, int i = 0){
    if(set.size() == i){
        return (sum == 0) ? 1 : 0;
    }
    
    if(set.size() == i + 1){
        return dp[i][sum] = (set[i] == sum) ? 1 : 0;
    }
    
    if(sum == 0){
        return dp[i][sum] = 1;
    }

    if(dp[i][sum] != -1){
        return dp[i][sum];
    }

    int count = 0;
    for(int j = i; j < set.size(); j++){
        if(sum >= set[j]){
            count += countEqualPartitions(dp, set, sum - set[j], j + 1);
        }
    }
    return dp[i][sum] = count;
}

int countEqualSumPartitions(std :: vector <std :: vector <int>> &dp, std :: vector <int> &numSet, int target, int i = 0){
    if(i >= numSet.size()){
        return dp[i][target] = (target == 0) ? 1 : 0;
    }

    if(target == 0){
        return dp[i][0] = 1;
    }

    if(dp[i][target] != -1){
        return dp[i][target];
    }

    int take = (target >= numSet[i]) ? countEqualSumPartitions(dp, numSet, target - numSet[i], i + 1) : 0;
    int skip = countEqualSumPartitions(dp, numSet, target, i + 1);

    return dp[i][target] = take + skip;
}

int main(){
    std :: vector <int> set = {1, 3, 21, 6, 8, 5, 2, 13, 4, 7};
    int sum = std :: accumulate(set.begin(), set.end(), 0);
    if(sum % 2 != 0){
        std :: cout << "set can't be divided into two equal sum subset\n";
        return -1;
    }
    sum = sum / 2;
    int n = set.size();
    std :: vector <std :: vector <int>> dp(n, std :: vector <int>(sum + 1, -1));
    int ans_0 = countEqualPartitions(dp, set, sum) / 2;
    int ans_1 = countEqualSumPartitions(dp, set, sum) / 2;
    std :: cout << "number of equal partitions = \n"
    << ans_0 << std :: endl
    << ans_1 << std :: endl
    ;
    return 0;
}