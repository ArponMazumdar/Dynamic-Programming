#include <iostream>
#include <vector>

int longestIncreasingSubSequenceLength(std :: vector <std :: vector <int>> &dp, std :: vector <int> &s, int p_idx = -1, int depth = 0){
    if(depth == s.size()) return 0;
    if(p_idx != -1 && dp[p_idx][depth] != -1) {
        printf("overlapping sub problems for (%d, %d)-> Returning %d\n", p_idx, depth, dp[p_idx][depth]);
        return dp[p_idx][depth];
    }

    int curr_len = 0, max_len = 0;
    for(int i = depth; i < s.size(); i++){
        if(p_idx == -1 || s[i] >= s[p_idx]){
            curr_len = 1 + longestIncreasingSubSequenceLength(dp, s, i, i + 1);
        }
        max_len = std :: max(curr_len, max_len);
    }
    if(p_idx != -1) dp[p_idx][depth] = max_len;
    return max_len;
}

int main(){
    std :: vector <int> s = {8, 3, 1, 2, 6, 7, 9};
    int n = s.size();
    std :: vector <std :: vector <int>> dp(n, std :: vector <int>(n, -1));
    int ans = longestIncreasingSubSequenceLength(dp, s);
    printf("\nlongest increasing subsequence length = %d\n", ans);
    return 0;
}