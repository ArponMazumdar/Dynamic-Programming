#include <iostream>
#include <vector>
#include <string>

int longestCommonSubString(std :: string &s1, std :: string &s2){
    int len1 = s1.size();
    int len2 = s2.size();

    std :: vector <std :: vector <int>> dp(len1 + 1, std :: vector <int>(len2 + 1, 0));
    int maxLen = 0;
    for(int i = len1 - 1; i >= 0; i--){
        for(int j = len2 - 1; j >= 0; j--){
            if(s1[i] == s2[j]){
                dp[i][j] = 1 + dp[i + 1][j + 1];
                maxLen = std :: max(dp[i][j], maxLen);
            }
            else{
                dp[i][j] = 0;
            }
        }
    }
    return maxLen;
}

//try to memoize it...
int longestCommonSubStr( std :: vector <std :: vector <std :: vector <int>>> &dp, std :: string &s1, std :: string &s2, int maxLen = 0, int i = 0, int j = 0){
    if(i == s1.size() || j == s2.size()){
        return maxLen;
    }

    if(dp[i][j][maxLen] != -1){
        //std :: cout << "recomputation!!" << std :: endl;
        return dp[i][j][maxLen];
    }
    int sLen = 0;
    if(s1[i] == s2[j]){
        sLen = longestCommonSubStr(dp, s1, s2, maxLen + 1, i + 1, j + 1);
    }

    int moveS1 = longestCommonSubStr(dp, s1, s2, 0, i + 1, j);
    int moveS2 = longestCommonSubStr(dp, s1, s2, 0, i, j + 1);
    int len = std :: max(moveS1, moveS2);

    return dp[i][j][maxLen] = std :: max(sLen, len);
}

int longestCommonSubstring(std :: string &s1, std :: string &s2){
    int len1 = s1.size();
    int len2 = s2.size();

    int maxLen = -1;
    for(int i = 0; i < len1; i++){
        for(int j = 0; j < len2; j++){
            int currLen = 0;
            while(i + currLen < len1 && j + currLen < len2 && s1[i + currLen] == s2[j + currLen]){
                currLen++;
            }
            maxLen = std :: max(currLen, maxLen);
        }
    }
    return maxLen;
}

int main(){
    std :: string s1 = "10110";
    std :: string s2 = "101";
    int n1 = s1.size();
    int n2 = s2.size();
    int m = std :: min(n1, n2);
    int len = longestCommonSubString(s1, s2);
    std :: vector <std :: vector <std :: vector <int>>> dp(n1, std :: vector <std :: vector <int>>(n2, std :: vector <int>(m, -1)));
    int len1 = longestCommonSubStr(dp, s1, s2);
    int len2 = longestCommonSubstring(s1, s2);
    std :: cout <<"longest common sub string:\n" 
    << len << std :: endl
    << len1 << std :: endl
    << len2 << std :: endl
    ;
    return 0;
}