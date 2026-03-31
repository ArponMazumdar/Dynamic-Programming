#include <iostream>
#include <vector>
#include <chrono>
#include <queue>

int uniquePath(std :: vector <std :: vector <int>> &dp, int& m, int& n, int i = 0, int j = 0){
    if(i == m - 1 && j == n - 1){
        return 1;
    }
    if(dp[i][j] != -1){
        return dp[i][j];
    }

    int count = 0;
    if(i < m - 1) count += uniquePath(dp, m, n, i + 1, j);
    if(j < n - 1) count += uniquePath(dp, m, n, i, j + 1);
    return dp[i][j] = count;
}

int UniquePath(int &m, int &n){
    std :: vector <int> curr(n, 0);
    std :: vector <int> dp = curr;
    curr[n - 1] = 1;

    for(int i = m - 1; i >= 0; i--){
        int count = 0;
        for(int j = n - 1; j >= 0; j--){
            if(i < m - 1) curr[j] += dp[j];
            if(j < n - 1) curr[j] += curr[j + 1];
        }
        dp = curr;
        curr.assign(n, 0);
    }

    return dp[0];
}

int bfs_uniquePath(int &m, int &n){
    std :: queue <std :: pair <int, int>> q;
    q.push({0, 1});
    q.push({1, 0});
    int count = 0;
    while(!q.empty()){
        std :: pair <int, int> p = q.front();
        q.pop();
        int i = p.first;
        int j = p.second;
        if(i == m - 1 && j == n - 1){
            count++;
        }
        if(i < m - 1) q.push({i + 1, j});
        if(j < n - 1) q.push({i, j + 1});
    }
    return count;
}

int main(){
    int m = 18;
    int n = 11;
    std :: vector <std :: vector <int>> dp(m, std :: vector <int>(n, -1));
    std :: cout << "\nTotal unique paths : \n";
    auto start = std :: chrono :: high_resolution_clock :: now();
    int ans0 = uniquePath(dp, m, n);
    auto end = std :: chrono :: high_resolution_clock :: now();
    std :: chrono :: duration <double, std :: milli> clk = end - start;
    std :: cout << ans0 << "  |  " << clk.count() << std :: endl;
    start = std :: chrono :: high_resolution_clock :: now();
    int ans1 = bfs_uniquePath(m, n);
    end = std :: chrono :: high_resolution_clock :: now();
    clk = end - start;
    std :: cout << ans1 << "  |  " << clk.count() << std :: endl;
    start = std :: chrono :: high_resolution_clock :: now();
    int ans2 = UniquePath(m, n);
    end = std :: chrono :: high_resolution_clock :: now();
    clk = end - start;
    std :: cout << ans2 << "  |  " << clk.count() << std :: endl;
    return 0;
}