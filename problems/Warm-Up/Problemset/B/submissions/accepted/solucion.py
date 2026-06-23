import sys
input = sys.stdin.readline

t = int(input())
for _ in range(t):
    n = int(input())
    s = input().strip()

    # Expandir: rellenar gaps de 1 entre dos 1's iterativamente
    maxS = list(s)
    changed = True
    while changed:
        changed = False
        for i in range(1, n - 1):
            if maxS[i] == '0' and maxS[i-1] == '1' and maxS[i+1] == '1':
                maxS[i] = '1'
                changed = True

    maxOnes = maxS.count('1')

    # Minimo: en cada bloque de 1's consecutivos de longitud k, min = k//2 + 1
    minOnes = 0
    blockLen = 0
    for i in range(n):
        if maxS[i] == '1':
            blockLen += 1
        else:
            if blockLen > 0:
                minOnes += blockLen // 2 + 1
                blockLen = 0
    if blockLen > 0:
        minOnes += blockLen // 2 + 1

    print(minOnes, maxOnes)
