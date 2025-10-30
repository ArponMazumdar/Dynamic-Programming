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

int longestPalindromic(std :: string &s){
    int len = s.size();
    std :: vector <std :: vector <int>> dp(len + 1, std :: vector <int>(len, 0));

    int start = 0;
    for(int i = len - 1; i >= 0; i--){
        dp[i][i] = 1;
        int longLen = 0;
        for(int j = i + 1; j < len; j++){
            if(s[i] == s[j]){
                longLen = dp[i + 1][j - 1];
                if(longLen == j - i - 1){
                    dp[i][j] = longLen + 2;
                    continue;
                }
            }
            int moveI = dp[i + 1][j];
            int moveJ = dp[i][j - 1];

            dp[i][j] = std :: max(longLen, std :: max(moveI, moveJ));
        }
    }
    return dp[0][len - 1];
}

std :: string longestPalSubString(std :: string &s){
    int len = s.size();
    std :: vector <std :: vector <std :: string>> dp(len, std :: vector <std :: string>(len, ""));

    for(int i = len - 1; i >= 0; i--){
        dp[i][i] = s[i];
        for(int j = i + 1; j < len; j++){
            if(s[i] == s[j]){
                std :: string str = dp[i + 1][j - 1];

                if(str.size() == j - i - 1){
                    dp[i][j] = s[i] + str + s[j];
                    continue;
                }
            }

            std :: string s1 = dp[i + 1][j];
            std :: string s2 = dp[i][j - 1];
            dp[i][j] = (s1.size() >= s2.size()) ? s1 : s2;
        }
    }
    return dp[0][len - 1];
}

std :: string longest_Palindromic(std :: string &s){
    int len = s.size();
    std :: vector <std :: string> dp(len, "");
    std :: vector <std :: string> row(len, "");
    std :: vector <std :: string> col(len, "");

    for(int i = len - 1; i >= 0; i--){
        dp[i] = s[i];
        for(int j = i + 1; j < len; j++){
            if(s[i] == s[j]){
                std :: string str = row[j - 1];

                if(str.size() == j - i - 1){
                    dp[j] = s[i] + str + s[j];
                    continue; 
                }
            }
            std :: string s1 = dp[j - 1];
            std :: string s2 = row[j];
            dp[j] = (s1.size() >= s2.size()) ? s1 : s2;
        }
        row = dp;
    }
    return dp[len - 1];
}

int main(){
    std :: string s = "madamishappy";
    int n = s.size();
    std :: vector <std :: vector <int>> dp(n, std :: vector <int>(n, -1));
    int len = longPal(dp, s, 0, n - 1);
    int len_1 = longestPalindromic(s);
    std :: string str_1 = longestPalSubString(s);
    std :: string str_2 = longest_Palindromic(s);
    std :: cout << "longest palindromic substring length: \n"
    << len << std :: endl
    << len_1 << std :: endl
    <<"longest palindromic substring: " << std :: endl
    << str_1 << std :: endl
    << str_2 << std :: endl
    ;
    return 0;
}