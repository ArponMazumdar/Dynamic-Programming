#include <iostream>
#include <vector>
#include <string>

class solution{
    std :: vector <std :: vector <int>>dp;
    std :: string s1 = "";
    std :: string s2 = "";
    int m = 0; int n = 0;
public:
    solution(){}
    solution(std :: string str1, std :: string str2){
        m = str1.size();
        n = str2.size();
        s1 = str1;
        s2 = str2;
        dp.assign(m, std :: vector <int>(n, -1));
    }
    int solveDistinctSubSequence(int i = 0, int j = 0){
        if(i >= s1.size()) return 0;
        if(j == s2.size()) return 1;
        if(dp[i][j] != -1) return dp[i][j];

        if(s1[i] == s2[j]){
            int p = solveDistinctSubSequence(i + 1, j); 
            int q = solveDistinctSubSequence(i, j + 1);
            dp[i][j] = p + q;
            return dp[i][j];
        }
        dp[i][j] = solveDistinctSubSequence(i + 1, j);
        return dp[i][j];
    }
    int countDistinctSubSequence(){
        dp.assign(m + 1, std :: vector <int>(n + 1, 0));
        for(int i = m - 1; i >= 0; i--){
            dp[i][n] = 1;
            for(int j = n - 1; j >= 0; j--){
                if(s1[i] == s2[j]){
                    dp[i][j] = dp[i + 1][j] + dp[i][j + 1];
                    continue;
                }
                dp[i][j] = dp[i + 1][j];
            }
        }
        return dp[0][0];
    }
};

int main(){
    std :: string s1 = "bbagaabgagbgag";
    std :: string s2 = "bag";
    solution problem(s1, s2);
    int cnt0 = problem.solveDistinctSubSequence();
    int cnt1 = problem.countDistinctSubSequence();
    std :: cout <<"distinct sub sequences: \n"
    << cnt0 << std :: endl
    << cnt1 << std :: endl; 
    return 0;
}