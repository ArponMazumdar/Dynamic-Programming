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

int cnt_Partition(int &num){
    std :: vector <std :: vector <int>> dp(num + 1, std :: vector <int>(num + 1, 0));

    for(int i = 0; i <= num; i++){
        dp[i][0] = 1;
    }

    for(int i = num; i >= 0; i--){
        for(int j = 1; j <= num; j++){
            dp[i][j] += (j >= i) ? dp[i][j - i] : 0;
            dp[i][j] += (i < num) ? dp[i + 1][j] : 0;
        }
    }
    return dp[0][num];
}

int main() {
    int n = 14;
    std::vector<std :: vector <int>> dp(n + 1, std :: vector <int>(n + 1, -1));
    int ans = count_Partition(n, dp);
    int ans_1 = cnt_Partition(n);
    
    std::cout << "Partition for " << n << " : \n"
    << ans << std :: endl
    << ans_1 << std :: endl;
    return 0;
}
