#!/usr/bin/env python3

import sys

input_file = sys.argv[1]
fin = open(input_file, "r")

N = int(fin.readline())
assert 1 <= N <= 100_000

numbers = list(map(int, fin.readline().split()))
assert len(numbers) == N + 1
assert all(1 <= x <= 1_000_000_000 for x in numbers)
