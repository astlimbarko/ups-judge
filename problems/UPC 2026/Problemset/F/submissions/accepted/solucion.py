t = input()
length = len(t)

# Count non-'a' characters
non_a = sum(1 for c in t if c != 'a')

if non_a % 2 != 0:
    print(":(")
else:
    non_a_in_s = non_a // 2
    # len_s = length - non_a_in_s (since s' has length non_a_in_s)
    len_s = length - non_a_in_s
    
    if len_s <= 0 or len_s > length:
        print(":(")
    else:
        s = t[:len_s]
        s_prime_expected = t[len_s:]
        
        # Verify
        s_prime = ''.join(c for c in s if c != 'a')
        
        if s_prime == s_prime_expected:
            print(s)
        else:
            print(":(")
