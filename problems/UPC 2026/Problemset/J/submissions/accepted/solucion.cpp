#include <iostream>
#include <vector>
#include <string>
using namespace std;

int n, m;
vector<string> grid;
vector<vector<bool>> visited;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

bool dfs(int x, int y, int px, int py, char color){
    visited[x][y] = true;
    for(int d = 0; d < 4; d++){
        int nx = x + dx[d];
        int ny = y + dy[d];
        if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
        if(nx == px && ny == py) continue;
        if(grid[nx][ny] != color) continue;
        if(visited[nx][ny]) return true; // found cycle
        if(dfs(nx, ny, x, y, color)) return true;
    }
    return false;
}

int main(){
    cin >> n >> m;
    grid.resize(n);
    visited.assign(n, vector<bool>(m, false));
    
    for(int i = 0; i < n; i++) cin >> grid[i];
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(!visited[i][j]){
                if(dfs(i, j, -1, -1, grid[i][j])){
                    cout << "Yes" << "\n";
                    return 0;
                }
            }
        }
    }
    cout << "No" << "\n";
    return 0;
}
