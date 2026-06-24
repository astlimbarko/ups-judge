p, n = map(int, input().split())
used = set()
ans = -1
for i in range(1, n + 1):
    x = int(input())
    h = x % p
    if h in used:
        ans = i
        break
    used.add(h)
print(ans)
