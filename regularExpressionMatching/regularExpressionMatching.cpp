#include <iostream>
#include <vector>
#include <string>

bool solve(std :: vector <std :: vector <int>> &dp, std :: string &s, std :: string &p, int i = 0, int j = 0){
    if(i == s.size() && j == p.size()) return true; //if both of the string has exhausted, they are matching
    if(i == s.size()){
        for(;j < p.size();){
            if(j + 1 < p.size() && p[j + 1] == '*'){
                j = j + 2;
            } else return false; 
        }
        return true;
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

int main(){
    std :: string s = "abcccddddef";
    std :: string p = ".*.*";
    int m = s.size();
    int n = p.size();
    std :: vector <std :: vector <int>> dp(m, std :: vector <int>(n, -1));
    if(solve(dp, s, p)){
        printf("\nMatch found!\n");
    } else {
        printf("\nUnable to match!\n");
    }
    return 0;
}