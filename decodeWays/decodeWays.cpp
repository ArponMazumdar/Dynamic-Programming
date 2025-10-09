#include <iostream>
#include <vector>
#include <string> 

int solveMemoization(std :: string& message, std :: vector <int> & memo, int& n, int i = 0){
    if(i == n) return 1;
    if(i > n) return 0;
    if(memo[i] != -1) return memo[i];

    memo[i] = (message[i] == '0') ? 0 : solveMemoization(message, memo, n, i + 1);

    if(i <= n - 2 && message[i] == '1'){
        memo[i] = memo[i] + solveMemoization(message, memo, n, i + 2);
    }
    if(i <= n - 2 && (message[i] == '2' && message[i + 1] <= '6')){
        memo[i] = memo[i] + solveMemoization(message, memo, n, i + 2);
    }
    return memo[i];
}

int solveTabulation(std :: string& message){
    int n = message.size();
    std :: vector <int> dp(n + 1, 0);
    dp[n] = 1;
    for(int i = n - 1; i >= 0; i--){
        if(message[i] != '0'){
            dp[i] += dp[i + 1]; 
        }
        if(i <= n - 2 && message[i] == '1'){
            dp[i] += dp[i + 2];
        }
        if(i <= n - 2 && message[i] == '2' && message[i + 1] <= '6'){
            dp[i] += dp[i + 2];
        }
    }
    return dp[0];
}

int main(){
    std :: string message = "20611";
    int n = message.size();
    std :: vector <int> memo(n + 1, -1);
    std :: cout << "number of ways to decode " << message << " = " << solveMemoization(message, memo, n) << std :: endl;
    return 0;
}