#include <iostream>
#include <vector>

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

int main(){
    int k = 3;
    std :: vector <int> price = {1, 7, 4, 7, 8, 11, 9, 20, 1, 4, 13, 2, 7, 9};
    int n = price.size();
    std :: vector <std :: vector <int>> dp(n, std :: vector <int>(k + 1, -1));
    int ans = countMaxProfit(dp, price, k);
    (ans < 0) ? printf("\n%d transactions are not possible here\n", k) : printf("\nafter %d transactions, maximum profit: %d\n", k, ans);
    std :: vector <std :: vector <std :: vector <int>>> memo(n, std :: vector <std :: vector <int>> (k + 1, std :: vector <int>(2, -1)));
    int ans1 = countNTransactionsMaxProfit(memo, price, k);
    (ans1 < 0) ? printf("%d transactions are not possible here\n", k) : printf("after %d transactions, maximum profit: %d\n", k, ans1);
    return 0;
}