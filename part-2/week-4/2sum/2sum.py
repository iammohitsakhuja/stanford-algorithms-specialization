from sys import argv
from time import time


def main(argv):
    """Main function for the program."""
    # Ensure proper usage.
    if len(argv) != 4:
        print("Usage: python %s file_name target_left target_right" % argv[0])
        exit(1)

    file_name = argv[1]
    start = int(argv[2])
    end = int(argv[3])

    # Load the numbers from the file, and benchmark the time taken.
    load_start_time = time()
    numbers = load_numbers(file_name)
    load_end_time = time()
    time_loading = load_end_time - load_start_time

    print("No. of distinct numbers: " + str(len(numbers)))

    # Count the number of achievable targets within the range [start, end],
    # and benchmark the time taken.
    counting_start_time = time()
    count = count_achievable_targets(numbers, start, end)
    counting_end_time = time()
    time_counting = counting_end_time - counting_start_time

    print("Count of achievable targets: " + str(count), end="\n\n")

    # Display the benchmark results.
    print("TIME IN loading the numbers into the hash table: %8.3fs" %
          time_loading)
    print("TIME IN counting achievable targets:             %8.3fs" %
          time_counting)
    print("TIME IN total:                                   %8.3fs" %
          (time_loading + time_counting))


def load_numbers(file_name):
    """Loads numbers from a file into a set."""
    numbers = set()
    with open(file_name) as file:
        for line in file.readlines():
            numbers.add(int(line))
    return numbers


def count_achievable_targets(numbers, start, end):
    """
    Counts the number of targets within the range [start, end] that can be
    achieved by adding x and y, where x and y are two distinct numbers in
    `numbers`.
    """
    count = 0
    for target in range(start, end + 1):
        for number in numbers:
            x = target - number
            if x != number:
                if x in numbers:
                    count += 1
                    break

    return count


main(argv)
