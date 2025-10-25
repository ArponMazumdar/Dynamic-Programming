#include <string>
#include <vector>
#include <iostream>

int longestPalindrom(std :: vector <std :: vector <int>> &dp, std :: string &s, int i, int j){
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
        len = longestPalindrom(dp, s, i + 1, j - 1);

        if(len == j - i - 1){
            return dp[i][j] = len + 2;
        }
    }

    int moveI = longestPalindrom(dp, s, i + 1, j);
    int moveJ = longestPalindrom(dp, s, i, j - 1);

    return dp[i][j] = std :: max(std :: max(moveI, moveJ), len);
}

int main(){
    std :: string s = "popboob";
    int n = s.size();
    std :: vector <std :: vector <int>> dp(n, std :: vector <int>(n, -1));
    int len = longestPalindrom(dp, s, 0, n - 1);
    std :: cout << len << std :: endl;
    return 0;
}