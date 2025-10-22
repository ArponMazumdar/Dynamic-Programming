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
        return dp[i][j] = 1 + longestLength(s1, s2, dp, i + 1, j + 1);
    }

    return dp[i][j] = std :: max(longestLength(s1, s2, dp, i, j + 1), longestLength(s1, s2, dp, i + 1, j));
}

int longestLen(std :: string &s1, std :: string &s2){
    int len_1 = s1.size();
    int len_2 = s2.size();

    std :: vector <std :: vector <int>> dp(len_1 + 1, std :: vector <int>(len_2 + 1, 0));

    for(int i = len_1 - 1; i >= 0; i--){
        for(int j = len_2 - 1; j >= 0; j--){
            if(s1[i] == s2[j]){
                dp[i][j] = 1 + dp[i + 1][j + 1];
            }
            else{
                dp[i][j] = std :: max(dp[i][j + 1], dp[i + 1][j]);
            }
        }
    }

    return dp[0][0];
}

int main(){
    std :: string s1 = "abcdefgh";
    std :: string s2 = "acbedfigjh";
    std :: vector <std :: vector <int>> dp(s1.size(), std :: vector <int>(s2.size(), -1));
    int longLen = longestLength(s1, s2, dp);
    int l_len = longestLen(s1, s2);
    std :: cout << "longest length = \n" 
    << longLen << std :: endl
    << l_len << std :: endl
    ;
    return 0;
}