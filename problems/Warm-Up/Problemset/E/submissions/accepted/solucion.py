import sys
input = sys.stdin.readline

t = int(input())
for _ in range(t):
    a, b, x = map(int, input().split())

    valsA = []
    cur, ops = a, 0
    while True:
        valsA.append((cur, ops))
        if cur == 0:
            break
        cur //= x
        ops += 1

    valsB = []
    cur, ops = b, 0
    while True:
        valsB.append((cur, ops))
        if cur == 0:
            break
        cur //= x
        ops += 1

    ans = float('inf')
    for va, opsA in valsA:
        for vb, opsB in valsB:
            cost = opsA + opsB + abs(va - vb)
            if cost < ans:
                ans = cost

    print(ans)
