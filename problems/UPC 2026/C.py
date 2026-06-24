t = int(input())
for _ in range(t):
    n = int(input())
    colors = set(map(int, input().split()))
    c = len(colors)
    while c not in colors:
        colors.add(c)
        c = len(colors)
    print(c)
