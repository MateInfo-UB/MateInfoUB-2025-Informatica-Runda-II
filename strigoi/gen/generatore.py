#!/usr/bin/env python3

import sys
import random

TEST_NR = int(sys.argv[1])

N_PER_TEST = {
    0: 1,
    1: 1,
    2: 100,
    3: 98,
    4: 0,
    5: 0,
    6: 0,
    7: 1000,
    8: 1000,
    9: 1000,
}

MAX_VAL_PER_TEST = {
    0: 100,
    1: 100,
    2: 100,
    3: 100,
    4: 1_000_000_000,
    5: 1_000_000_000,
    6: 1_000_000_000,
    7: 1_000_000_000,
    8: 1_000_000_000,
    9: 1_000_000_000,
}


N = N_PER_TEST[TEST_NR]
MAX_VAL = MAX_VAL_PER_TEST[TEST_NR]

numbers = [random.randint(1, MAX_VAL) for _ in range(N + 1)]

print(N)
print(" ".join(map(str, numbers)))
