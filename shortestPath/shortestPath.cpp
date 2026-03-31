#include <iostream>
#include <vector>
#include <queue>

int bfs(std :: vector <std :: vector <int>>& grid, std :: pair<int, int>& start, std :: pair<int, int>& end){
    int m = grid.size();
    int n = grid[0].size();
    std :: vector <std :: vector <bool>> hasVisited(m, std :: vector <bool>(n, false));
    std :: queue <std :: pair<std :: pair<int, int>, int>> q;
    q.push({{start.first, start.second}, 0});
    hasVisited[start.first][start.second] = true;
    while(!q.empty()){
        int i = q.front().first.first;
        int j = q.front().first.second;
        int dist = q.front().second;
        q.pop();
        if(i == end.first && j == end.second){
            return dist;
        }
        int dx[4] = {-1, 1, 0, 0};
        int dy[4] = {0, 0, -1, 1};
        for(int it = 0; it < 4; it++){
            int ni = i + dx[it];
            int nj = j + dy[it];
            if(ni >= 0 && ni < m && nj >= 0 && nj < n && grid[ni][nj] == 0 && !hasVisited[ni][nj]){
                hasVisited[ni][nj] = true;
                q.push({{ni, nj}, dist + 1});
            }
        }
    }
    return -1;
}

int main(){
    std :: vector <std :: vector <int>> grid = {
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0},
        {0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    };
    int m = grid.size();
    int n = grid[0].size();
    std :: pair <int, int> s = {0, 0};
    std :: pair <int, int> e = {2, 2};
    int ans = bfs(grid, s, e);
    std :: cout << "\nshortest path :\n" << ans << std :: endl;
    return 0;
}