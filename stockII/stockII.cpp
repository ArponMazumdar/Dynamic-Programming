//you can buy and sell multiple stocks.
//But holding stocks aren't allowed. 
//If you have sell existing stock before buying any. 
//return maximum possible profit

#include <iostream>
#include <vector>
#include <queue>

int solve(std :: vector <int> &dp, std :: vector <int> &val, int depth = 0){
    if(depth >= val.size()){
        return 0;
    }
    if(dp[depth] != -1){
        return dp[depth];
    }

    int max_profit = 0;
    int curr_val = 0;
    for(int i = depth; i < val.size(); i++){
        curr_val = val[i] - val[depth];
        curr_val = curr_val + solve(dp, val, i + 1);
        max_profit = std :: max(curr_val, max_profit);
    }
    return dp[depth] = max_profit;
}

int profit(std :: vector <int> &val, std :: queue <int> &q, int depth = 0){ 
    if(depth == val.size() - 1){ 
        if(!q.empty()){ 
            return val[depth] - q.front(); 
        } else{ 
            return 0; 
        } 
    } 
    int maxProfit = 0; 
    if(!q.empty()){ 
        int sellNow = val[depth] - q.front(); 
        int currStock = q.front(); 
        q.pop(); 
        sellNow += profit(val, q, depth + 1); 
        q.push(currStock); int sellNext = profit(val, q, depth + 1); 
        maxProfit += std :: max(sellNow, sellNext); 
    } else{ 
        q.push(val[depth]); 
        int buyNow = profit(val, q, depth + 1); 
        q.pop(); 
        int buyNext = profit(val, q, depth + 1); 
        maxProfit += std :: max(buyNow, buyNext); 
    } 
    return maxProfit; 
}

int solveMaxProfit(std :: vector <std :: vector<int>> &dp, std :: vector <int> &vals, bool hasSold = true, int depth = 0){
    if(depth == vals.size() - 1){
        if(!hasSold){
            return vals[depth];
        }
        return 0;
    }
    if(dp[depth][hasSold] != -1){
        return dp[depth][hasSold];
    }

    int maxProfit = 0;
    if(!hasSold){
        int sellNow = solveMaxProfit(dp, vals, true, depth + 1) + vals[depth];
        int sellNext = solveMaxProfit(dp, vals, false, depth + 1);
        maxProfit += std :: max(sellNow, sellNext);
    } else {
        int buyNow = solveMaxProfit(dp, vals, false, depth + 1) - vals[depth];
        int buyNext = solveMaxProfit(dp, vals, true, depth + 1);
        maxProfit += std :: max(buyNow, buyNext);
    }
    return maxProfit;
}

int main(){
    std :: vector <int> val = {1, 51, 9, 3, 7, 11, 2, 4, 23, 1, 5, 4, 9, 17, 6, 10, 7};
    std :: vector <int> memo(val.size(), -1);
    int ans = solve(memo, val);
    std :: queue <int> q;
    int ans1 = profit(val, q);
    std :: vector <std :: vector <int>> dp(val.size(), std :: vector <int> (2, -1));
    int ans2 = solveMaxProfit(dp, val);
    std :: cout << "\n" << ans << "\n" << ans1 << "\n" << ans2 << "\n";
    return 0;
}