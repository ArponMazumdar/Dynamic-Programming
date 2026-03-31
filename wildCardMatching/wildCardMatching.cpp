#include <iostream>
#include <vector>
#include <string>

bool haveMatched(std :: vector <std :: vector <int>> &dp, std :: string &s1, std :: string &s2, int i = 0, int j = 0){
    if(i == s1.size() && j == s2.size()) return true;
    if(i == s1.size()) return false;
    if(j == s2.size()){
        for(int k = i; k < s1.size(); k++){
            if(s1[k] != '*') return false;
        }
        return true;
    }
    if(dp[i][j] != -1) return dp[i][j];

    if(s1[i] == s2[j] || s1[i] == '.'){
        return haveMatched(dp, s1, s2, i + 1, j + 1);
    }
    if(s1[i] == '*'){
        bool match1 = haveMatched(dp, s1, s2, i, j + 1);
        bool match2 = haveMatched(dp, s1, s2, i + 1, j);
        return dp[i][j] =  match1 || match2;
    }
    return dp[i][j] = false;
}

bool solveMatched(std :: string &s1, std :: string &s2){
    int m = s1.size();
    int n = s2.size();
    std :: vector <std :: vector <bool>> dp(m + 1, std :: vector <bool> (n + 1, false));
    for(int j = 0; j < s2.size(); j++){
        dp[m][j] = false;
    }
    for(int i = 0; i < s1.size(); i++){
        bool flag = true;
        for(int j = i; j < s1.size(); j++){
            if(s1[j] != '*'){
                flag = false;
                break;
            }
        }
        dp[i][n] = flag;
    }
    for(int i = m - 1; i >= 0; i--){
        for(int j = n - 1; j >= 0; j--){
            if(s1[i] == s2[j] || s1[i] == '.'){
                dp[i][j] = dp[i + 1][j + 1];
            } else if(s1[i] == '*'){
                bool match1 = dp[i][j + 1];
                bool match2 = dp[i + 1][j];
                dp[i][j] = match1 || match2;
            }
            else dp[i][j] = false;
        }
    }
    return dp[0][0];
}

int main(){
    std :: string s1 = ".*";
    std :: string s2 = "abcdefghij";
    int m = s1.size();
    int n = s2.size();
    std :: vector <std :: vector <int>> memo(m, std :: vector <int>(n, -1));
    bool match = haveMatched(memo, s1, s2);
    (match) ? std :: cout << "\nmatch found!\n" : std :: cout << "\nnot matched!\n";
    return 0;
}