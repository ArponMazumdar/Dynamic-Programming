#include <iostream>
#include <vector>
#include <string>

bool solve(std :: vector <std :: vector <int>> &dp, std :: string &s, std :: string &p, int i = 0, int j = 0){
    if(i == s.size() && j == p.size()) return dp[i][j] = true; //if both of the string has exhausted, they are matching
    if(i == s.size()){
        for(;j < p.size();){
            if(j + 1 < p.size() && p[j + 1] == '*'){
                j = j + 2;
            } else return dp[i][j] = false; 
        }
        return dp[i][j] = true;
    }
    if(j == p.size()) return i == s.size(); 
    if(dp[i][j] != -1) return dp[i][j];

    if(j + 1 < p.size() && p[j + 1] == '*'){
        bool skip = solve(dp, s, p, i, j + 2);
        bool take = false;
        if(s[i] == p[j] || p[j] == '.'){
            take = solve(dp, s, p, i + 1, j);
        }
        return dp[i][j] = skip || take;
    }
    if(s[i] == p[j] || p[j] == '.'){
        return dp[i][j] = solve(dp, s, p, i + 1, j + 1);
    }
    return dp[i][j] = false;
}

bool tabulation(std :: string &s, std :: string &p){
    int m = s.size();
    int n = p.size();
    std :: vector <std :: vector <bool>> dp(m + 1, std :: vector <bool>(n + 1, false));
    for(int i = 0; i < n; i++){
        bool flag = true;
        for(int j = i; j < n;){
            if(j + 1 < n && p[j + 1] == '*'){
                j = j + 2;
            } else {
                flag = false;
                break;
            }
        }
        dp[m][i] = flag;
    }
    dp[m][n] = true;
    for(int i = m - 1; i >= 0; i--){
        for(int j = n - 1; j >= 0; j--){
            if(j + 1 < n && p[j + 1] == '*'){
                bool skip = dp[i][j + 2];
                bool take = false;
                if(s[i] == p[j] || p[j] == '.'){
                    take = dp[i + 1][j];
                }
                dp[i][j] = skip || take;
                continue;
            }
            if(s[i] == p[j] || p[j] == '.'){
                dp[i][j] = dp[i + 1][j + 1];
            }
        }
    }
    return dp[0][0];
}

int main(){
    std :: string s = "d";
    std :: string p = ".*dc*";
    int m = s.size();
    int n = p.size();
    std :: vector <std :: vector <int>> dp(m + 1, std :: vector <int>(n + 1, -1));
    if(tabulation(s, p)){
        printf("\nMatch found!\n");
    } else {
        printf("\nUnable to match!\n");
    }
    // for(int i = 0; i <= m; i++){
    //     for(int j = 0; j <= n; j++){
    //         printf("%d ", dp[i][j]);
    //     }
    //     printf("\n");
    // }
    return 0;
}