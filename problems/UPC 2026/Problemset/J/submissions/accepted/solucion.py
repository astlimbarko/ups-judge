import sys
sys.setrecursionlimit(100000)

def solve():
    n, m = map(int, input().split())
    grid = []
    for _ in range(n):
        grid.append(input().strip())
    
    visited = [[False]*m for _ in range(n)]
    
    def dfs(x, y, px, py, color):
        visited[x][y] = True
        for dx, dy in [(0,1),(0,-1),(1,0),(-1,0)]:
            nx, ny = x+dx, y+dy
            if 0 <= nx < n and 0 <= ny < m:
                if nx == px and ny == py:
                    continue
                if grid[nx][ny] != color:
                    continue
                if visited[nx][ny]:
                    return True
                if dfs(nx, ny, x, y, color):
                    return True
        return False
    
    for i in range(n):
        for j in range(m):
            if not visited[i][j]:
                if dfs(i, j, -1, -1, grid[i][j]):
                    print("Yes")
                    return
    print("No")

solve()
