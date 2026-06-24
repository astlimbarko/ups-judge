import sys
input = sys.stdin.readline

t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    xs = list(map(int, input().split()))
    
    pos = sorted([x for x in xs if x > 0], reverse=True)
    neg = sorted([-x for x in xs if x < 0], reverse=True)
    
    dist = 0
    
    # Each group of k, travel 2 * farthest in that group
    for i in range(0, len(pos), k):
        dist += 2 * pos[i]
    
    for i in range(0, len(neg), k):
        dist += 2 * neg[i]
    
    # Don't return from the overall farthest
    farthest = 0
    if pos:
        farthest = max(farthest, pos[0])
    if neg:
        farthest = max(farthest, neg[0])
    
    dist -= farthest
    
    print(dist)
