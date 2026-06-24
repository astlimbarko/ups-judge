import sys
input = sys.stdin.readline

t = int(input())
for _ in range(t):
    n = int(input())
    h = list(map(int, input().split()))
    
    # t[n-1] = h[n-1]
    # t[i] = max(h[i], t[i+1] + 1)
    time_to_zero = h[-1]
    for i in range(n-2, -1, -1):
        time_to_zero = max(h[i], time_to_zero + 1)
    
    print(time_to_zero)
