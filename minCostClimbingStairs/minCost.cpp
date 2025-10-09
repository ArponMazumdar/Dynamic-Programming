#include <iostream>
#include <vector>
#include <algorithm>

int minimumCost(std :: vector <int> &cost , std :: vector <int> &minCost , int nStair , int iStair){
    if(iStair == nStair - 1){
        return cost[nStair - 1];
    }
    if(iStair == nStair){
        return 0;
    }

    if(minCost[iStair] != -1){
        return minCost[iStair];
    }

    minCost[iStair] = cost[iStair] + std :: min(minimumCost(cost , minCost , nStair , iStair + 1) , minimumCost(cost , minCost , nStair , iStair + 2));
    return minCost[iStair];
}

int minCost(std :: vector <int>& cost){
    int n = cost.size();
    std :: vector <int> dp(n, 0);
    dp[n - 1] = cost[n - 1];

    int curr_Min = 0;
    int curr_Cost = __INT_MAX__;
    for(int i = n - 2; i >= 0; i--){
        for(int j = i; j < n - 1; j++){
            int curr_Min = cost[j];
            
        }
    }
    return dp[0];
}

int main(){
    std :: vector <int> cost = {0 , 1 , 2 , 2, 6, 3, 7, 1, 5, 2};
    int nStair = cost.size();
    std :: vector <int> minCost(nStair - 1 , -1);
    int ans = std :: min(minimumCost(cost , minCost , nStair , 0) , minimumCost(cost , minCost , nStair , 1));
    std :: cout << ans << std :: endl;
    return 0;
}