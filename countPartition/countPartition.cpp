#include <iostream>
#include <vector>

int count_Partition(int n, std::vector<std :: vector <int>> &dp, int k = 1) {
    if(n == 0) {
        return 1;
    }

    if(dp[n][k] != -1){
        //std::cout << "recomputation case hit for " << n << ", " << k << std :: endl;
        return dp[n][k];
    }

    int count = 0;
    for(int i = k; i <= n; i++){
        count += count_Partition(n - i, dp, i);
    }
    return dp[n][k] = count;
}

int main() {
    int n = 5;
    std::vector<std :: vector <int>> dp(n + 1, std :: vector <int>(n + 1, -1));
    int ans = count_Partition(n, dp);
    std::cout << "Partition for " << n << " = " << ans << std::endl;
    return 0;
}
