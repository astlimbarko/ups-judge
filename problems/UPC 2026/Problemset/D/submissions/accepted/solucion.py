import sys
input = sys.stdin.readline

t = int(input())
for _ in range(t):
    a, b, l = map(int, input().split())
    ks = set()
    ax = 1
    while ax <= l:
        by = 1
        while ax * by <= l:
            if l % (ax * by) == 0:
                ks.add(l // (ax * by))
            by *= b
        ax *= a
    print(len(ks))
