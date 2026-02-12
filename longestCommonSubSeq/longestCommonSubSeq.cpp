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

int solveLongLen(std :: vector <std :: vector <int>>& dp, std :: string s1, std :: string s2, int s1_idx = 0, int s2_idx = 0){
    if(s1_idx >= s1.length() || s2_idx >= s2.length()){
        return 0;
    }
    if(dp[s1_idx][s2_idx] != -1){
        return dp[s1_idx][s2_idx];
    }
    int maxLen = 0;
    for(int i = s1_idx; i < s1.size(); i++){
        int currLen = 0;
        for(int j = s2_idx; j < s2.size(); j++){
            if(s1[i] == s2[j]){
                currLen = 1 + solveLongLen(dp, s1, s2, i + 1, j + 1);
                maxLen = std :: max(currLen, maxLen);
            }
        }
    }
    return dp[s1_idx][s2_idx] = maxLen;
}

int main(){
    std :: string s1 = "afgidckuncdjgkl";
    std :: string s2 = "uicctscndakjhl";
    std :: vector <std :: vector <int>> dp(s1.size(), std :: vector <int>(s2.size(), -1));
    int longLen = longestLength(s1, s2, dp);
    int l_len = longestLen(s1, s2);
    dp.assign(s1.size(), std :: vector <int>(s2.size(), -1));
    int long_len = solveLongLen(dp, s1, s2);
    std :: cout << "longest length = \n" 
    << longLen << std :: endl
    << l_len << std :: endl
    << long_len << std :: endl
    ;
    return 0;
}