#include <iostream>
#include <vector> 
#include <chrono>

int countMaxProfitforTwoTransaction(std :: vector <std :: vector <int>> &dp, std :: vector <int> &stockPrice, int maxTransaction = 2, int depth = 0){
    if(maxTransaction == 0 || depth >= stockPrice.size()){
        return 0;
    }
    if(dp[depth][maxTransaction] != -1){
        return dp[depth][maxTransaction];
    }

    int maxProfit = -1e9;
    for(int i = depth; i < stockPrice.size(); i++){
        for(int j = i + 1; j < stockPrice.size(); j++){
            int currProfit = stockPrice[j] - stockPrice[i];
            int secondProfit = countMaxProfitforTwoTransaction(dp, stockPrice, maxTransaction - 1, j + 1);
            maxProfit = std :: max(maxProfit, currProfit + secondProfit);
        }
    }
    dp[depth][maxTransaction] = maxProfit;
    return maxProfit;
}

int countTwoTransactionMaxProfit(std :: vector <std :: vector <std :: vector <int>>>& dp, std :: vector <int> &prices, int i = 0, int j = 2, bool canSell = false){
    if(j == 0 || i == prices.size()) return 0;
    if(i == prices.size() - 1){
        return (canSell) ? prices[i] : 0;
    }
    if(dp[i][j][canSell] != -1) return dp[i][j][canSell];

    int maxProfit = -1e9;
    if(canSell){
        int sell_now = prices[i] + countTwoTransactionMaxProfit(dp, prices, i + 1, j - 1, false);
        int sell_next = countTwoTransactionMaxProfit(dp, prices, i + 1, j, true);
        maxProfit = std :: max(maxProfit, std :: max(sell_now, sell_next));
    } else {
        int buy_now = countTwoTransactionMaxProfit(dp, prices, i + 1, j, true) - prices[i];
        int buy_next = countTwoTransactionMaxProfit(dp, prices, i + 1, j, false);
        maxProfit = std :: max(maxProfit, std :: max(buy_now, buy_next));
    }
    return dp[i][j][canSell] = maxProfit;
}

int countProfit(std :: vector <int> &prices){
    int n = prices.size();
    std :: vector <std :: vector <std :: vector <int>>> dp(n, std :: vector <std :: vector <int>> (3, std :: vector <int>(2, 0)));
    dp[n - 1][1][true] = prices[n - 1];
    dp[n - 1][2][true] = prices[n - 1];
    for(int i = n - 2; i >= 0; i--){
        for(int j : {1, 2}){
            for(bool canSell : {true, false}){
                int maxProfit = -1e9;
                if(canSell){
                    int sell_now = prices[i] + dp[i + 1][j - 1][false];
                    int sell_next = dp[i + 1][j][true];
                    maxProfit = std :: max(maxProfit, std :: max(sell_now, sell_next));
                } else {
                    int buy_now = dp[i + 1][j][true] - prices[i];
                    int buy_next = dp[i + 1][j][false];
                    maxProfit = std :: max(maxProfit, std :: max(buy_now, buy_next));
                }
                dp[i][j][canSell] = maxProfit;
            }
        }
    }
    return dp[0][2][false];
}

int countProfitTwoTransaction(std :: vector <int> &prices){
    int n = prices.size();
    std :: vector <std :: vector <int>> dp(n + 1, std :: vector <int>(3, 0));
    for(int i = n - 1; i >= 0; i--){
        for(const int &j : {1, 2}){
            int maxProfit = 0;
            for(int x = i; x < n; x++){
                for(int y = x + 1; y < n; y++){
                    int currProfit = prices[y] - prices[x];
                    int nextProfit = dp[y + 1][j - 1];
                    int profit = currProfit + nextProfit;
                    maxProfit = std :: max(maxProfit, profit);
                }
            }
            dp[i][j] = maxProfit;
        }
    }
    return dp[0][2];
}

int main(){
    std :: vector <int> price = {5, 9, 1, 2, 12, 1, 6, 10, 14, 2, 9, 1, 7, 21, 9, 5, 8, 7, 25};
    int n = price.size();
    printf("\nmaximum profit after 2 transactions\nvalue\ttime(micro sec)\n");
    std :: vector <std :: vector <int>> dp(n, std :: vector <int>(3, -1));
    auto s = std :: chrono :: high_resolution_clock :: now();
    int ans = countMaxProfitforTwoTransaction(dp, price);
    auto e = std :: chrono :: high_resolution_clock :: now();
    std :: chrono :: duration <long double, std :: micro> d = e - s;
    printf("%d\t%Lf\n", ans, d.count());
    std :: vector <std :: vector <std :: vector <int>>> memo (n, std :: vector <std :: vector <int>>(3, std :: vector <int>(2, -1)));
    s = std :: chrono :: high_resolution_clock :: now();
    int ans1 = countTwoTransactionMaxProfit(memo, price);
    e = std :: chrono :: high_resolution_clock :: now();
    d = e - s;
    printf("%d\t%Lf\n", ans1, d.count());
    s = std :: chrono :: high_resolution_clock :: now();
    int ans2 = countProfit(price);
    e = std :: chrono :: high_resolution_clock :: now();
    d = e - s;
    printf("%d\t%Lf\n", ans2, d.count());
    s = std :: chrono :: high_resolution_clock :: now();
    int ans3 = countProfitTwoTransaction(price);
    e = std :: chrono :: high_resolution_clock :: now();
    d = e - s;
    printf("%d\t%Lf\n", ans3, d.count());
    return 0;
}