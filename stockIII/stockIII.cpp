#include <iostream>
#include <vector> 

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

int main(){
    std :: vector <int> price = {5, 9, 1, 2, 12, 1, 6, 10};
    int n = price.size();
    std :: vector <std :: vector <int>> dp(n, std :: vector <int>(3, -1));
    int ans = countMaxProfitforTwoTransaction(dp, price);
    std :: cout << "\nmaximum profit after two transaction = " << ans << "\n";
    return 0;
}