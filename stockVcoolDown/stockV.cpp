#include <iostream>
#include <vector>
#include <chrono>

int countMaxProfitWithCoolDown(std :: vector <int> &dp, std :: vector <int> &price, int depth = 0){
    if(depth >= price.size()) return 0;
    if(dp[depth] != -1) return dp[depth];

    int maxProfit = 0;
    for(int i = depth; i < price.size(); i++){
        for(int j = i + 1; j < price.size(); j++){
            int currTran = price[j] - price[i];
            currTran += countMaxProfitWithCoolDown(dp, price, j + 2);
            maxProfit = std :: max(currTran, maxProfit);
        }
    }
    return dp[depth] = maxProfit;
}

int countCoolDownMaxProfit(std :: vector <std :: vector <int>> &dp, std :: vector <int> &price, int i = 0, bool j = false){
    if(i >= price.size()) return 0;
    if(dp[i][j] != -1) return dp[i][j];
    if(j){
        int sell_now = price[i] + countCoolDownMaxProfit(dp, price, i + 2, false);
        int sell_next = countCoolDownMaxProfit(dp, price, i + 1, true);
        return dp[i][j] = std :: max(sell_now, sell_next);
    }
    int buy_now = countCoolDownMaxProfit(dp, price, i + 1, true) - price[i];
    int buy_next = countCoolDownMaxProfit(dp, price, i + 1, false);
    return dp[i][j] = std :: max(buy_now, buy_next);
}

int coolDownMaxProfit(std :: vector <int> &price){
    int n = price.size();
    std :: vector <std :: vector <int>> dp(n + 1, std :: vector <int>(2, 0));

    for(int i = n - 1; i >= 0; i--){
        int sell_now = price[i];
        sell_now += (i + 2 >= n) ? 0 : dp[i + 2][0];
        int sell_next = dp[i + 1][1];
        dp[i][1] = std :: max(sell_now, sell_next);
        int buy_now = dp[i + 1][1] - price[i];
        int buy_next = dp[i + 1][0];
        dp[i][0] = std :: max(buy_now, buy_next);
    }
    return dp[0][0];
}

int countCoolDownMaxProfit(std :: vector <int> &price){
    int n = price.size();
    std :: vector <int> dp(n, 0);
    for(int depth = n - 1; depth >= 0; depth--){
        int maxProfit = 0;
        for(int i = depth; i < n; i++){
            for(int j = i + 1; j < n; j++){
                int currTran = price[j] - price[i];
                currTran += (j + 2 >= n) ? 0 : dp[j + 2];
                maxProfit = std :: max(currTran, maxProfit);
            }
        }
        dp[depth] = maxProfit;
    }
    return dp[0];
}

int main(){
    std :: vector <int> price = {1, 7, 4, 7, 8, 11, 9, 20, 1, 4, 13, 2, 7, 9, 0, 13, 21, 34, 1, 7, 3, 1, 0, 9, 4, 44, 7, 21, 12, 24, 8, 9, 0, 5, 10, 18, 21, 1, 9, 12};
    int n = price.size();
    printf("\nMaximum profit with cooldown\nvalue \t time(milli second)\n");
    std :: vector <int> dp(n, -1);
    auto s = std :: chrono :: high_resolution_clock :: now();
    int ans = countMaxProfitWithCoolDown(dp, price);
    auto e = std :: chrono :: high_resolution_clock :: now();
    std :: chrono :: duration <long double, std :: milli> d = e - s;
    printf("%d \t %Lf\n", ans, d.count());
    std :: vector <std :: vector <int>> memo(n, std :: vector <int>(2, -1));
    s = std :: chrono :: high_resolution_clock :: now();
    ans = countCoolDownMaxProfit(memo, price);
    e = std :: chrono :: high_resolution_clock :: now();
    d = e - s;
    printf("%d \t %Lf\n", ans, d.count());
    s = std :: chrono :: high_resolution_clock :: now();
    ans = coolDownMaxProfit(price);
    e = std :: chrono :: high_resolution_clock :: now();
    d = e - s;
    printf("%d \t %Lf\n", ans, d.count());
    s = std :: chrono :: high_resolution_clock :: now();
    ans = countCoolDownMaxProfit(price);
    e = std :: chrono :: high_resolution_clock :: now();
    d = e - s;
    printf("%d \t %Lf\n", ans, d.count());
    return 0;
}