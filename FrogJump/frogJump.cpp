#include <iostream>
#include <vector>
#include <algorithm>

bool canJump(std :: vector <std :: vector <int>> &dp, std :: vector <int> &stones, int i = 1, int y = 1){
    if(i == stones.size() - 1) return true;
    if(dp[i][y] != -1){
        return dp[i][y];
    }
    bool result = false;
    for(int j = y - 1; j <= y + 1; j++){
        if(j <= 0) continue;
        int s = stones[i] + j;
        int d = -1;
        auto it = std :: find(stones.begin(), stones.end(), s);
        if(it != stones.end()){
            d = std :: distance(stones.begin(), it);
            result = result || canJump(dp, stones, d, j);
        }
    }
    return dp[i][y] = result;
}

int main(){
    std :: vector <int> stones = {0, 1, 3, 4, 8, 9, 11};
    auto it = find(stones.begin(), stones.end(), stones[0] + 1);
    if(it != stones.end()){
        int d = distance(stones.begin(), it);
        std :: vector <std :: vector <int>> dp(stones.size(), std :: vector <int>(stones[stones.size() - 1], -1));
        (canJump(dp, stones, d)) ? std :: cout <<"\ncan jump\n" : std :: cout << "\ncan't jump\n";
    }
    return 0;
}