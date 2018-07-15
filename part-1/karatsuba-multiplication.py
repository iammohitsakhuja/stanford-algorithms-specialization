def karatsuba(x, y):
    n = min(len(str(x)), len(str(y)))

    if n == 1:
        return x * y

    half = n // 2
    pow_ten_half = 10 ** half

    a = x // pow_ten_half
    b = x % pow_ten_half
    c = y // pow_ten_half
    d = y % pow_ten_half

    ac = karatsuba(a, c)
    bd = karatsuba(b, d)
    a_plus_b_into_c_plus_d = karatsuba(a + b, c + d)

    return (ac * pow(pow_ten_half, 2)) + bd + \
        ((a_plus_b_into_c_plus_d - ac - bd) * pow_ten_half)


result = karatsuba(
    3141592653589793238462643383279502884197169399375105820974944592,
    2718281828459045235360287471352662497757247093699959574966967627)

print(result)
