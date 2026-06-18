import sys
input = sys.stdin.readline

t = int(input())
for _ in range(t):
    n = int(input())
    row1 = input().strip()
    row2 = input().strip()
    
    # dp[i] = min repintados considerando columnas i..n-1
    dp = [0] * (n + 1)
    for i in range(n - 1, -1, -1):
        vert_cost = 0 if row1[i] == row2[i] else 1
        best = vert_cost + dp[i + 1]
        
        if i + 1 < n:
            horiz_cost = (0 if row1[i] == row1[i+1] else 1) + (0 if row2[i] == row2[i+1] else 1)
            best = min(best, horiz_cost + dp[i + 2])
        
        dp[i] = best
    
    print(dp[0])
