import sys
input = sys.stdin.readline

t = int(input())
for _ in range(t):
    n, rk, ck, rd, cd = map(int, input().split())
    
    if rd <= rk and cd <= ck:
        if rk == rd:
            ans = n - cd
        elif ck == cd:
            ans = n - rd
        else:
            ans = max(n - cd, n - rd)
    elif rd >= rk and cd >= ck:
        if rk == rd:
            ans = cd
        elif ck == cd:
            ans = rd
        else:
            ans = max(cd, rd)
    elif rd <= rk and cd >= ck:
        if rk == rd:
            ans = cd
        elif ck == cd:
            ans = n - rd
        else:
            ans = max(n - rd, cd)
    else:
        if rk == rd:
            ans = n - cd
        elif ck == cd:
            ans = rd
        else:
            ans = max(rd, n - cd)
    
    print(ans)
