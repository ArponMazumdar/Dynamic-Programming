#include <iostream>
#include <vector>
#include <string>

std :: string lcs(std :: vector <std :: vector <std :: string>> &dp, std :: string &s1, std :: string &s2, int i = 0, int j = 0){
    if(i == s1.size() || j == s2.size()){
        return "";
    }

    if(!dp[i][j].empty()){ 
        return dp[i][j];
    }
    std :: string s;
    std :: string s_;
    if(s1[i] == s2[j]){
        s = s1[i] + lcs(dp, s1, s2, i + 1, j + 1); 
    }
    else{
        std :: string curr_s1 = lcs(dp, s1, s2, i, j + 1);
        std :: string curr_s2 = lcs(dp, s1, s2, i + 1, j);
        
        s_ = (curr_s1.size() > curr_s2.size()) ? curr_s1 : curr_s2;
    }
    return dp[i][j] = (s.size() > s_.size()) ? s : s_;
}

std :: string lcs_(std :: string &s1, std :: string &s2){
    int len1 = s1.size();
    int len2 = s2.size();

    std :: vector <std :: vector <std :: string>> dp(len1 + 1, std :: vector <std :: string>(len2 + 1, ""));

    for(int i = len1 - 1; i >= 0; i--){
        for(int j = len2 - 1; j >= 0; j--){
            if(s1[i] == s2[j]){
                dp[i][j] = s2[j] + dp[i + 1][j + 1];
            }
            else{
                std :: string s1_ = dp[i + 1][j];
                std :: string s2_ = dp[i][j + 1];
                dp[i][j] = (s1_.size() > s2_.size()) ? s1_ : s2_;
            }
        }
    }

    return dp[0][0];
}

int main(){
    std :: string s1 = "aicdehfn";
    std :: string s2 = "gacbdiehfjkn";
    std :: vector <std :: vector <std :: string>> dp(s1.size(), std :: vector <std :: string>(s2.size(), ""));
    std :: string LCS = lcs(dp, s1, s2);
    std :: string LCS1 = lcs_(s1, s2);
    std :: cout <<"longest common substring : \n"
    << LCS << std :: endl
    << LCS1 << std :: endl
    ;
    return 0;
}