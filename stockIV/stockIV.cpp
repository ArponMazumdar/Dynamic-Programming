#include <iostream>
#include <vector>
#include <chrono>

//have to make exactly k transactions. Not allowed to make less or greater than k transactions. 

int countMaxProfit(std :: vector <std :: vector <int>> &dp, std :: vector <int> price, int k, int depth = 0){
    if(k == 0) return 0;
    if(depth == price.size()){
        return -1e9;
    }
    if(dp[depth][k] != -1)return dp[depth][k];

    int maxProfit = -1e9;
    for(int i = depth; i < price.size(); i++){
        for(int j = i + 1; j < price.size(); j++){
            int currProfit = price[j] - price[i];
            int nextProfit = countMaxProfit(dp, price, k - 1, j + 1);
            int totalProfit = currProfit + nextProfit;
            maxProfit = std :: max(totalProfit, maxProfit);
        }
    }
    return dp[depth][k] = maxProfit;
}

int countMaximumProfit(std :: vector <int> &price, int K){
    int n = price.size();
    std :: vector <std :: vector <int>> dp(n + 1, std :: vector <int> (K + 1, 0));
    for(int i = 1; i <= K; i++){
        dp[n][i] = -1e9;
    }
    for(int depth = n - 1; depth >= 0; depth--){
        for(int k = 1; k <= K; k++){
            int maxProfit = -1e9;
            for(int i = depth; i < n; i++){
                for(int j = i + 1; j < n; j++){
                    int profit = price[j] - price[i];
                    profit += dp[j + 1][k - 1];
                    maxProfit = std :: max(maxProfit, profit);
                }
            }
            dp[depth][k] = maxProfit;
        }
    }
    return dp[0][K];
}

int countNTransactionsMaxProfit(std :: vector <std :: vector <std :: vector <int>>> &dp, std :: vector <int> &price, int k, int depth = 0, bool canSell = false){
    if(k == 0) return 0;
    if(depth == price.size()) return -1e9;
    if(dp[depth][k][canSell] != -1) return dp[depth][k][canSell];

    int maxProfit = -1e9;
    if(canSell){
        int sell_now = price[depth] + countNTransactionsMaxProfit(dp, price, k - 1, depth + 1, false);
        int sell_next = countNTransactionsMaxProfit(dp, price, k, depth + 1, true);
        maxProfit = std :: max(maxProfit, std :: max(sell_now, sell_next));
    } else {
        int buy_now = countNTransactionsMaxProfit(dp, price, k, depth + 1, true) - price[depth];
        int buy_next = countNTransactionsMaxProfit(dp, price, k, depth + 1, false);
        maxProfit = std :: max(maxProfit, std :: max(buy_now, buy_next));
    }
    return dp[depth][k][canSell] = maxProfit;
}

int countMaxProfitForNtransaction(std :: vector <int> &price, int K){
    int n = price.size();
    std :: vector <std :: vector <std :: vector <int>>> dp(n + 1, std :: vector <std :: vector <int>> (K + 1, std :: vector <int>(2, 0)));
    for(int i = 1; i <= K; i++){
        for(int j = 0; j <= 1; j++){
            dp[n][i][j] = -1e9;
        }
    }
    for(int i = n - 1; i >= 0; i--){
        for(int k = 1; k <= K; k++){
            int sell_now = price[i] + dp[i + 1][k - 1][false];
            int sell_next = dp[i + 1][k][true];
            dp[i][k][1] = std :: max(sell_now, sell_next);

            int buy_now = dp[i + 1][k][true] - price[i];
            int buy_next = dp[i + 1][k][false];
            dp[i][k][0] = std :: max(buy_now, buy_next);
        }
    }
    return dp[0][K][false];
}

int calculateMaxProfit(std :: vector <int> &price, int k){
    int n = price.size();
    std :: vector <std :: vector <int>> dp(k + 1, std :: vector <int> (2, -1e9));
    dp[0][1] = dp[0][0] = 0;
    std :: vector <std :: vector <int>> curr(k + 1, std :: vector <int> (2, 0));
    for(int i = n - 1; i >= 0; i--){
        for(int j = 1; j <= k; j++){
            curr[j][1] = std :: max(price[i] + dp[j - 1][0], dp[j][1]);
            curr[j][0] = std :: max(dp[j][1] - price[i], dp[j][0]);
        }
        dp = curr;
    }
    return dp[k][0];
}

int calculateMaxProfitNtransaction(std :: vector <std :: vector <int>> &dp, std :: vector <int> &price, int k, int i = 0, int j = 0){
    if(j == 2*k) return 0;
    if(i == price.size()) return -1e9;
    if(dp[i][j] != -1) return dp[i][j];

    if(j % 2 == 0){
        int p_1 = calculateMaxProfitNtransaction(dp, price, k, i + 1, j + 1) - price[i];
        int p_2 = calculateMaxProfitNtransaction(dp, price, k, i + 1, j);
        return dp[i][j] = std :: max(p_1, p_2);
    }
    int p_1 = price[i] + calculateMaxProfitNtransaction(dp, price, k, i + 1, j + 1);
    int p_2 = calculateMaxProfitNtransaction(dp, price, k, i + 1, j);
    return dp[i][j] = std :: max(p_1, p_2);
}

int calculateMaximumProfit(std :: vector <int> &price, int K){
    int n = price.size();
    std :: vector <int> dp(2 * K + 1, -1e9);
    dp[2*K] = 0;
    std :: vector <int> curr(2 * K + 1, 0);
    for(int i = n - 1; i >= 0; i--){
        for(int j = 0; j < 2*K; j++){
            int p_1 = 0, p_2 = 0;
            if(j % 2 == 0){
                p_1 = dp[j + 1] - price[i];
                p_2 = dp[j];
                curr[j] = std :: max(p_1, p_2);
                continue;
            }
            p_1 = price[i] + dp[j + 1];
            p_2 = dp[j];
            curr[j] = std :: max(p_1, p_2);
        }
        dp = curr;
    }
    return dp[0];
}

int main(){
    int k = 14;
    std :: vector <int> price = {1, 7, 4, 7, 8, 11, 9, 20, 1, 4, 13, 2, 7, 9, 0, 13, 21, 34, 1, 7, 3, 1, 0, 9, 4, 44, 7, 21, 12, 24, 8, 9, 0, 5, 10};
    int n = price.size();
    printf("\nmaximum profit for %d transactions\nvalue \t time(milli seconds)\n", k);
    std :: vector <std :: vector <int>> dp(n, std :: vector <int>(k + 1, -1));
    auto s = std :: chrono :: high_resolution_clock :: now();
    int ans = countMaxProfit(dp, price, k);
    auto e = std :: chrono :: high_resolution_clock :: now();
    std :: chrono :: duration <long double, std :: milli> d = e - s;
    printf("%d \t   %Lf\n", ans, d.count());
    std :: vector <std :: vector <std :: vector <int>>> memo(n, std :: vector <std :: vector <int>> (k + 1, std :: vector <int>(2, -1)));
    s = std :: chrono :: high_resolution_clock :: now();
    int ans1 = countNTransactionsMaxProfit(memo, price, k);
    e = std :: chrono :: high_resolution_clock :: now();
    d = e - s;
    printf("%d \t   %Lf\n", ans1, d.count());
    s = std :: chrono :: high_resolution_clock :: now();
    int ans2 = countMaxProfitForNtransaction(price, k);
    e = std :: chrono :: high_resolution_clock :: now();
    d = e - s;
    printf("%d \t   %Lf\n", ans2, d.count());
    s = std :: chrono :: high_resolution_clock :: now();
    int ans3 = calculateMaxProfit(price, k);
    e = std :: chrono :: high_resolution_clock :: now();
    d = e - s;
    printf("%d \t   %Lf\n", ans3, d.count());
    s = std :: chrono :: high_resolution_clock :: now();
    int ans4 = countMaximumProfit(price, k);
    e = std :: chrono :: high_resolution_clock :: now();
    d = e - s;
    printf("%d \t   %Lf\n", ans4, d.count());
    dp.assign(n, std :: vector <int>(2 * k + 1, -1));
    s = std :: chrono :: high_resolution_clock :: now();
    int ans5 = calculateMaxProfitNtransaction(dp, price, k);
    e = std :: chrono :: high_resolution_clock :: now();
    d = e - s;
    printf("%d \t   %Lf\n", ans5, d.count());
    s = std :: chrono :: high_resolution_clock :: now();
    int ans6 = calculateMaximumProfit(price, k);
    e = std :: chrono :: high_resolution_clock :: now();
    d = e - s;
    printf("%d \t   %Lf\n", ans6, d.count());
    return 0;
}