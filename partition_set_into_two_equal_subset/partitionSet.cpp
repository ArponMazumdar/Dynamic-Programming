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
        return 1;
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

int main(){
    std :: vector <int> set = {1, 3, 2, 6, 8, 5, 7};
    int sum = std :: accumulate(set.begin(), set.end(), 0);
    if(sum % 2 != 0){
        std :: cout << "sum can't be divided into two equal number\n";
        return -1;
    }
    sum = sum / 2;
    int n = set.size();
    std :: vector <std :: vector <int>> dp(n, std :: vector <int>(sum + 1, -1));
    int equalPartitions = countEqualPartitions(dp, set, sum);
    std :: cout << "number of equal partitions = \n"
    << equalPartitions / 2 << std :: endl
    ;
    return 0;
}