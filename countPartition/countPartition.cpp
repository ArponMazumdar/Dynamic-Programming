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

    for(int i = 1; i <= num; i++){
        int cnt = 0;
        for(int j = i; j >= 1; j--){
            cnt += dp[i - j][j];
        }
        dp[i][i] = cnt;
    }
    return dp[num + 1][num + 1];
}

int main() {
    int n = 5;
    std::vector<std :: vector <int>> dp(n + 1, std :: vector <int>(n + 1, -1));
    int ans = cnt_Partition(n);
    std::cout << "Partition for " << n << " = " << ans << std::endl;
    return 0;
}
