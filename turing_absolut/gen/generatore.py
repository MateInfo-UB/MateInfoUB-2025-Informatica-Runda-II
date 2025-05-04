#!/usr/bin/env python3

import sys
import random

TEST_NR = int(sys.argv[1])

N_PER_TEST = {
    1: 5,
    2: 10,
    3: 30,
    4: 30,
    5: 100,
    6: 100,
    7: 1000,
    8: 1000,
    9: 1000,
    10: 1000,
}

MAX_VAL_PER_TEST = {
    1: 10,
    2: 100,
    3: 100,
    4: 100,
    5: 1000,
    6: 1000,
    7: 1_000_000_000,
    8: 1_000_000_000,
    9: 1_000_000_000,
    10: 1_000_000_000,
}


N = N_PER_TEST[TEST_NR]
MAX_VAL = MAX_VAL_PER_TEST[TEST_NR]

numbers = [random.randint(1, MAX_VAL) for _ in range(N + 1)]

print(N)
print(" ".join(map(str, numbers)))
