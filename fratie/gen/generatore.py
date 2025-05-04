#!/usr/bin/env python3

import sys
import random

TEST_NR = int(sys.argv[1])
SAMPLES_PER_TEST = 10

N_PER_TEST = {
    1: 5,
    2: 10,
    3: 30,
    4: 30,
    5: 100,
    6: 100,
    7: 100_000,
    8: 100_000,
    9: 100_000,
    10: 100_000,
}

MAX_VAL_PER_TEST = {
    1: 10,
    2: 100,
    3: 100,
    4: 100,
    5: 1000,
    6: 1000,
    7: 1000_000_000,
    8: 1000_000_000,
    9: 1000_000_000,
    10: 1000_000_000,
}

print(SAMPLES_PER_TEST)

for i in range(1, SAMPLES_PER_TEST + 1):
    N = N_PER_TEST[TEST_NR]
    MAX_VAL = MAX_VAL_PER_TEST[TEST_NR]

    numbers = [random.randint(1, MAX_VAL) for _ in range(N)]

    print(N)
    print(" ".join(map(str, numbers)))
