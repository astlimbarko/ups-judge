import sys

def main():
    n = int(input())
    c = list(map(int, input().split()))
    
    # Compress into segments
    segs = [c[0]]
    for i in range(1, n):
        if c[i] != segs[-1]:
            segs.append(c[i])
    
    m = len(segs)
    if m == 1:
        print(0)
        return
    
    # dp[l][r] = min turns to unify segments l..r
    dp = [[0]*m for _ in range(m)]
    
    for length in range(2, m+1):
        for l in range(m - length + 1):
            r = l + length - 1
            dp[l][r] = dp[l+1][r] + 1
            for k in range(l+1, r+1):
                if segs[k] == segs[l]:
                    dp[l][r] = min(dp[l][r], dp[l+1][k] + dp[k][r])
    
    print(dp[0][m-1])

main()
