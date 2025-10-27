#include <string>
#include <vector>
#include <iostream>

int longPal(std :: vector <std :: vector <int>> &dp, std :: string &s, int i, int j){
    if(i >= s.size() || j < 0 || j < i){
        return 0;
    }
    if(i == j){
        return 1;
    }

    if(dp[i][j] != -1){
        return dp[i][j];
    }

    int len = 0;
    if(s[i] == s[j]){
        len = longPal(dp, s, i + 1, j - 1);

        if(len == j - i - 1){
            return dp[i][j] = len + 2;
        }
    }

    int moveI = longPal(dp, s, i + 1, j);
    int moveJ = longPal(dp, s, i, j - 1);

    return dp[i][j] = std :: max(std :: max(moveI, moveJ), len);
}

//bugs here... 
int longestPalindromic(std :: string &s){
    int len = s.size();
    std :: vector <std :: vector <int>> dp(len + 1, std :: vector <int>(len, 0));

    for(int i = 0; i < len; i++){
        dp[i][i] = 1;
    }

    for(int i = len - 1; i >= 0; i--){
        int longLen = 0;
        for(int j = 0; j < len; j--){
            if(s[i] == s[j]){
                longLen = dp[i + 1][j - 1];
                if(longLen = j - i - 1){
                    dp[i][j] = longLen + 2;
                }
            }
            int moveI = dp[i + 1][j];
            int moveJ = dp[i][j + 1];

            dp[i][j] = std :: max(longLen, std :: max(moveI, moveJ));
        }
    }
    return dp[0][len - 1];
}

int main(){
    std :: string s = "popboob";
    int n = s.size();
    std :: vector <std :: vector <int>> dp(n, std :: vector <int>(n, -1));
    int len = longPal(dp, s, 0, n - 1);
    int len_1 = longestPalindromic(s);
    std :: cout << "longest palindromic substring length: "
    << len << std :: endl
    << len_1 << std :: endl
    ;
    return 0;
}