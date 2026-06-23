import sys
input = sys.stdin.readline

t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))

    iterations = 0
    while True:
        # Paso 1: buscar algun i con a[i] > b[i]
        found1 = False
        for i in range(n):
            if a[i] > b[i]:
                a[i] -= 1
                found1 = True
                break

        # Paso 2: buscar algun i con a[i] < b[i]
        for i in range(n):
            if a[i] < b[i]:
                a[i] += 1
                break

        iterations += 1

        if not found1:
            break

    print(iterations)
