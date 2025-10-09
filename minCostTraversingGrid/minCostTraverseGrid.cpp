#include <iostream>
#include <vector>
#include <cmath>

int minCost(std :: vector < std :: vector < int > > cost , std :: vector < std :: vector <int> > dp , int i = 0 , int j = 0){
    if(i >= cost.size() || j >= cost[0].size()){
        return __INT_MAX__;
    }
    if(i == cost.size() - 1 && j == cost[0].size() - 1){
        return cost[i][j];
    }
    if(dp[i][j] != -1){
        return dp[i][j];
    }
    dp[i][j] = cost[i][j] + std :: min(minCost(cost , dp , i , j + 1) , minCost(cost , dp , i + 1 , j) , minCost(cost , dp , i + 1 , j + 1));
    return dp[i][j];
}

int main(){
    std :: vector < std :: vector < int > > cost = {{1 , 2 , 3 , 5} , 
                                                    {5 , 9 , 1 , 2} ,
                                                    {4 , 8 , 1 , 5} ,
                                                    {7 , 9 , 1 , 6}};
    int n = cost.size();
    int m = cost[0].size();
    int min = std :: min(5 , 9 , 11);
    std :: cout << min;
    std :: vector < std :: vector < int > > dp(n , std :: vector < int > (m , -1));
    std :: cout << "minimum cost = " << minCost(cost , dp);
}