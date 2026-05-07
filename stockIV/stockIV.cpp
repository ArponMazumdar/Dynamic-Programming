#include <iostream>
#include <vector>

int countMaxProfit(std :: vector <int> price, int k, int depth = 0){
    if(k == 0) return 0;
    if(depth == price.size()){
        return -1e9;
    }

    int maxProfit = -1e9;
    for(int i = depth; i < price.size(); i++){
        for(int j = i + 1; j < price.size(); j++){
            int currProfit = price[j] - price[i];
            int nextProfit = countMaxProfit(price, k - 1, j + 1);
            int totalProfit = currProfit + nextProfit;
            maxProfit = std :: max(totalProfit, maxProfit);
        }
    }
    return maxProfit;
}

int main(){
    int k = 5;
    std :: vector <int> price = {1, 7, 4, 7, 8, 11, 9, 20, 1, 4, 13, 2, 7, 9};
    int ans = countMaxProfit(price, k);
    (ans < 0) ? printf("\n%d transaction is not possible here\n", k) : printf("\nafter %d transaction, maximum profit: %d\n", k, ans);
    return 0;
}