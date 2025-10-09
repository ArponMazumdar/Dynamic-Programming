#include <iostream>
#include <vector>

//can jump maximum 2 steps from current stair
int ClimbStairs(int n , std :: vector <int> &memo , int currentStair = 0){
    if(currentStair == n)
        return 1;
    if(currentStair > n)
        return 0;
    if(memo[currentStair] != -1)
        return memo[currentStair];

    memo[currentStair] = ClimbStairs(n , memo , currentStair + 1) + ClimbStairs(n , memo , currentStair + 2);
    return memo[currentStair];
}

int ClimbStairsTabulation(int n){
    std :: vector <int> dp(n + 1, 0);
    dp[n] = 1;

    for(int i = n - 1; i >= 0; i--){
        dp[i] = dp[i + 1] + ((i + 2 <= n) ? dp[i + 2] : 0);
    }

    return dp[0];
}

// int ClimbStairs(int n , std :: vector <int> &memo){
//     if(n == 0)
//         return 1;
//     if(n < 0)
//         return 0;
//     if(memo[n] != -1)
//         return memo[n];
    
//     memo[n] = ClimbStairs(n - 1 , memo) + ClimbStairs(n - 2 , memo);
//     return memo[n];
// }

int main(){
    int nStairs = 3;
    std :: vector <int> dp(nStairs + 1 , -1);
    //std :: cout << ClimbStairsTabulation(nStairs) << std :: endl;
    std :: cout << ClimbStairs(nStairs , dp) << std :: endl;
    return 0;
}