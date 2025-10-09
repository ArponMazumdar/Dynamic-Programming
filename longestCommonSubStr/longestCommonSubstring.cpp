#include <string>
#include <iostream>
#include <vector>

int longestLength(std :: string &s1, std :: string &s2, std :: vector <std :: vector <int>> &dp, int i = 0, int j = 0){
    if(i == s1.size() || j == s2.size()){
        return 0;
    }

    if(dp[i][j] != -1){
        return dp[i][j];
    }

    if(s1[i] == s2[j]){
        return 1 + longestLength(s1, s2, dp, i + 1, j + 1);
    }

    return dp[i][j] = std :: max(longestLength(s1, s2, dp, i, j + 1), longestLength(s1, s2, dp, i + 1, j));
}

int main(){
    std :: string s1 = "abcdefgh";
    std :: string s2 = "edfaghjcb";
    std :: vector <std :: vector <int>> dp(s1.size(), std :: vector <int>(s2.size(), -1));
    int longLen = longestLength(s1, s2, dp);
    std :: cout << "longest length = " << longLen << std :: endl;
    return 0;
}