#include <vector>
#include <iostream>
#include <chrono>

int solveMaxProfit(std :: vector <int> &dp, std :: vector <int> &val, int &fee, int d = 0){
    if(d == val.size()) return 0;
    if(dp[d] != -1) return dp[d];

    int max_profit = 0;
    for(int i = d; i < val.size(); i++){
        for(int j = i + 1; j < val.size(); j++){
            int cur_val = val[j] - val[i] - fee;
            cur_val += solveMaxProfit(dp, val, fee, j + 1);
            max_profit = std :: max(max_profit, cur_val);
        }
    }
    return dp[d] = max_profit;
}

int countMaxProfit(std :: vector <std :: vector <int>> &dp, std :: vector <int>&val, int &fee, int i = 0, int j = 0){
    if(i == val.size()){
        return 0;
    }
    if(dp[i][j % 2] != -1){
        return dp[i][j % 2];
    }

    if(j % 2){
        int p = val[i] + countMaxProfit(dp, val, fee, i + 1, j + 1) - fee;
        int q = countMaxProfit(dp, val, fee, i + 1, j);
        return dp[i][1] = std :: max(p, q);
    }
    //return dp[i][0] = std :: max(countMaxProfit(dp, val, fee, i + 1, j + 1) - val[i], countMaxProfit(dp, val, fee, i + 1, j));
    int p = countMaxProfit(dp, val, fee, i + 1, j + 1) - val[i];
    int q = countMaxProfit(dp, val, fee, i + 1, j);
    return dp[i][0] = std :: max(p, q);
}

int findMaxProfit(std :: vector <int> &val, int &fee){
    int n = val.size();
    std :: vector <int> dp(2, 0);
    std :: vector <int> curr = dp;
    for(int i = n - 1; i >= 0; i--){
        for(int j = 0; j <= n; j++){
            int p = 0, q = 0;
            if(j % 2){
                p = val[i] + dp[0] - fee;
                q = dp[1];
                curr[1] = std :: max(p, q);
            } else {
                p = -val[i] + dp[1];
                q = dp[0];
                curr[0] = std :: max(p, q);
            }
        }
        dp = curr;
    }
    return dp[0];
}

int main(){
    int fee = 2;
    std :: vector <int> price = {8, 3, 1, 9, 7, 2, 11, 17, 6, 1, 8, 12, 19, 21, 6, 10, 7};
    int n = price.size();
    std :: vector <int> dp(n, -1);

    auto s = std :: chrono :: high_resolution_clock :: now();
    int ans = solveMaxProfit(dp, price, fee);
    auto e = std :: chrono :: high_resolution_clock :: now();
    std :: chrono :: duration <long double, std :: milli> d = e - s;
    printf("maximum profit after paying %d transaction fee\n", fee);
    printf("%d\t%Lf\n", ans, d.count());

    std :: vector <std :: vector <int>> memo(n, std :: vector <int>(2, -1));
    s = std :: chrono :: high_resolution_clock :: now();
    ans = countMaxProfit(memo, price, fee);
    e = std :: chrono :: high_resolution_clock :: now();
    d = e - s;
    printf("%d\t%Lf\n", ans, d.count());

    s = std :: chrono :: high_resolution_clock :: now();
    ans = findMaxProfit(price, fee);
    e = std :: chrono :: high_resolution_clock :: now();
    d = e - s;
    printf("%d\t%Lf\n", ans, d.count());
    
    return 0;
}