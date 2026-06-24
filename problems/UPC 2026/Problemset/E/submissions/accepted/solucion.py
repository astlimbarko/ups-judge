t = int(input())
for _ in range(t):
    n, d = map(int, input().split())
    result = []
    
    # By 1: always
    result.append(1)
    
    # By 3: digit sum = d * n!. Div by 3 iff d*n! % 3 == 0
    # For n>=3, n! % 3 == 0, so always
    # For n==2, n!=2, d*2 % 3 == 0 iff d % 3 == 0
    if n >= 3 or (d * 2) % 3 == 0:
        result.append(3)
    
    # By 5: last digit is d
    if d % 5 == 0:
        result.append(5)
    
    # By 7: d * repunit(n!) % 7 == 0
    # repunit(k) % 7 == 0 iff k % 6 == 0
    # For n>=3, n! % 6 == 0, so repunit(n!)%7==0, always
    # For n==2, n!=2, repunit(2)=11, 11%7=4, d*4%7==0 iff d%7==0
    if n >= 3 or d % 7 == 0:
        result.append(7)
    
    # By 9: digit sum = d * n!. Div by 9 iff d*n! % 9 == 0
    if n >= 6:
        nfact_mod9 = 0
    elif n == 5:
        nfact_mod9 = 3  # 120%9
    elif n == 4:
        nfact_mod9 = 6  # 24%9
    elif n == 3:
        nfact_mod9 = 6  # 6%9
    else:
        nfact_mod9 = 2  # 2%9
    
    if (d * nfact_mod9) % 9 == 0:
        result.append(9)
    
    print(' '.join(map(str, result)))
