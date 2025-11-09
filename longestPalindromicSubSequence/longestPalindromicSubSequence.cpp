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

int longestPalindromicsubString_spaceOptimized(std :: string &s){
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

int main(){
    std :: string s = "abaacbaba";
    int ans = longestPalindromicSubSquence(s);
    int ans_1 = longestPalindromicsubString_spaceOptimized(s);
    std :: cout << "longest Palindromic Subsequence length :\n"
    << ans << std :: endl
    << ans_1 << std :: endl;

    return 0;
}