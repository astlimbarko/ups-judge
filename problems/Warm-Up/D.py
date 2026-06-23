n, m = map(int, input().split())
cars = list(map(int, input().split()))
sector = [0] * (n + 1)
points = 0

for c in cars:
    sector[c] += 1
    # Verificar si todos los sectores tienen al menos 1
    if all(sector[j] >= 1 for j in range(1, n + 1)):
        points += 1
        for j in range(1, n + 1):
            sector[j] -= 1

print(points)
