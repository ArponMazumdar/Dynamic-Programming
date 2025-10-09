#include <iostream>
#include <vector>
#include <climits>

int solveMemoization(std :: vector <int>& money, std :: vector <int>& memo, int& n, int i = 0){
    if(i == n - 1) return money[i];
    if(i >= n) return 0;
    if(memo[i] != -1) return memo[i];

    int max = -1;
    for(int j = i; j < n; j++){
        max = std :: max(max, money[j] + solveMemoization(money, memo, n, j + 2));
    }
    memo[i] = max;
    return memo[i];
}

int solve(std :: vector <int> &money){
    int n = money.size();
    std :: vector <int> dp(n, 0);
    dp[n - 1] = money[n - 1];

    for(int i = n - 2; i >= 0; i--){
        int max = INT_MIN;
        for(int j = i; j < n; j++){
            int curr = money[j] + ((j + 2 < n) ? dp[j + 2] : 0);
            max = std :: max(curr, max);
        }
        dp[i] = max;
    }

    return dp[0];
}

int maxMoney(std :: vector <int> &money, std :: vector <int> &dp, int &n, int i = 0){
    if(i == n - 1) return money[i];
    if(i >= n) return 0;
    if(dp[i] != -1) return dp[i];

    int add = money[i] + maxMoney(money, dp, n, i + 2);
    int skip = maxMoney(money, dp, n, i + 1);

    return dp[i] = std :: max(add, skip);
}

int maximumMoney(std :: vector <int> &money){
    int n = money.size();
    std :: vector <int> dp(n, 0);
    dp[n - 1] = money[n - 1];

    for(int i = n - 2; i >= 0; i--){
        int add = money[i] + ((i + 2) < n ? dp[i + 2] : 0);
        int skip = dp[i + 1];

        dp[i] = std :: max(add, skip);
    }

    return dp[0];
}

int main(){
    std :: vector <int> money = {2, 7, 9, 3, 1, 7, 11, 3, 9, 21, 7, 1, 1, 9, 4, 11};
    int n = money.size();
    std :: vector <int> memo(n + 1, -1);
    int ans_1 = solveMemoization(money, memo, n);
    int ans_2 = solve(money);
    memo.assign(n, -1);
    int ans_3 = maxMoney(money, memo, n);
    int ans_4 = maximumMoney(money);
    std :: cout << "maximum money robbing: " << std :: endl << ans_1 << std :: endl << ans_2 << std :: endl << ans_3 << std :: endl << ans_4 << std :: endl;
    return 0;
}