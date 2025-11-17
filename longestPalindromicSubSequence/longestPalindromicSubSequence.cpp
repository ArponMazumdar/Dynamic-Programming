#include <iostream>
#include <vector>
#include <string>

int longestPalindromicSubSquence(std :: string &s){
    int len = s.size();
    
    std :: vector <std :: vector <int>> dp(len, std :: vector <int>(len, 0));
    for(int i = len - 1; i >= 0; i--){
        dp[i][i] = 1;
        for(int j = i + 1; j < len; j++){
            if(s[i] == s[j]){
                dp[i][j] = 2 + dp[i + 1][j - 1];
                continue;
            }
            dp[i][j] = std :: max(dp[i + 1][j], dp[i][j - 1]);
        }
    }
    return dp[0][len - 1];
}

int longestPalindromicsubSequence_spaceOptimized(std :: string &s){
    int len = s.size();
    std :: vector <int> curr(len, 0);
    std :: vector <int> dp(len, 0);

    for(int i = len - 1; i >= 0; i--){
        curr[i] = 1;
        for(int j = i + 1; j < len; j++){
            if(s[i] == s[j]){
                curr[j] = 2 + dp[j - 1];
                continue;
            }
            curr[j] = std :: max(dp[j], curr[j - 1]); 
        }
        dp = curr;
    }
    return dp[len - 1];
}

int longestPalindromicSubSeq(std :: string &s, std :: vector <std :: vector <int>> dp, int i, int j){
    if(j < i || i >= s.size() || j < 0){
        return 0;
    }

    if(i == j){
        return 1;
    }

    if(dp[i][j] != -1){
        return dp[i][j];
    }

    int len = -1;
    if(s[i] == s[j]){
        len = 2 + longestPalindromicSubSeq(s, dp, i + 1, j - 1);
    }

    int mv_i = longestPalindromicSubSeq(s, dp, i + 1, j);
    int mv_j = longestPalindromicSubSeq(s, dp, i, j - 1);

    dp[i][j] = std :: max(len, std :: max(mv_i, mv_j));
    return dp[i][j];
}

int main(){
    std :: string s = "abaacbaba";
    int str_len = s.size();
    std :: vector <std :: vector <int>> dp(str_len, std :: vector <int> (str_len, -1));
    int ans = longestPalindromicSubSquence(s);
    int ans_1 = longestPalindromicsubSequence_spaceOptimized(s);
    int ans_2 = longestPalindromicSubSeq(s, dp, 0, str_len - 1);
    std :: cout << "longest Palindromic Subsequence length :\n"
    << ans << std :: endl
    << ans_1 << std :: endl
    << ans_2 << std :: endl;
    return 0;
}