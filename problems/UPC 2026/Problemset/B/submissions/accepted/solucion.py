import sys
input = sys.stdin.readline

t = int(input())
for _ in range(t):
    n, f, a, b = map(int, input().split())
    messages = list(map(int, input().split()))
    ok = True
    prev = 0
    for m in messages:
        diff = m - prev
        cost = min(diff * a, b)
        f -= cost
        if f <= 0:
            ok = False
        prev = m
    print("YES" if ok else "NO")
