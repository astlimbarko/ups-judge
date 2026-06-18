from math import factorial
from collections import Counter

def count_perms(s):
    freq = Counter(s)
    n = len(s)
    denom = 1
    for v in freq.values():
        denom *= factorial(v)
    return factorial(n) // denom

t = int(input())
for _ in range(t):
    n = int(input())
    s = input()
    
    min_perms = -1
    best = s
    
    # Probar todas las operaciones posibles (n <= 10, O(n^2) es viable)
    for i in range(n):
        for j in range(n):
            temp = list(s)
            temp[i] = s[j]
            temp_str = ''.join(temp)
            p = count_perms(temp_str)
            if min_perms == -1 or p < min_perms or (p == min_perms and temp_str < best):
                min_perms = p
                best = temp_str
    
    print(best)
