# Author: Mohit Sakhuja

def karatsuba(x, y):
    """Performs Karatsuba multiplication on two numbers."""
    # Calculate the length of the two integers and take the minimum of the two.
    n = min(len(str(x)), len(str(y)))

    # Perform simple multiplication if any of the two numbers is less than 10.
    if n == 1:
        return x * y

    # Calculate half length and the power of 10 raised to that half length.
    half = n // 2
    power_of_10 = 10 ** half

    # Divide and conquer.
    # Here, x = (a * power_of_10) + b
    # Here, y = (c * power_of_10) + d
    a = x // power_of_10
    b = x % power_of_10
    c = y // power_of_10
    d = y % power_of_10

    # 3 recursive calls to calculate (a * c), (b * d) and ((a + b) * (c + d)).
    ac = karatsuba(a, c)
    bd = karatsuba(b, d)
    a_plus_b_into_c_plus_d = karatsuba(a + b, c + d)

    # Multiply the results with the appropriate powers of 10,
    # and add them.
    return (ac * pow(power_of_10, 2)) + bd + \
        ((a_plus_b_into_c_plus_d - ac - bd) * power_of_10)


def main():
    """The main function."""
    # Given numbers (saved for testing's sake):
    # x = 3141592653589793238462643383279502884197169399375105820974944592
    # y = 2718281828459045235360287471352662497757247093699959574966967627

    x = input("Enter first number: ")
    y = input("Enter second number: ")

    result = karatsuba(int(x), int(y))
    print(result)


main()

