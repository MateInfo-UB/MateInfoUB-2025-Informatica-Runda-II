#!/usr/bin/env python3

import sys
import random

TEST_NR = int(sys.argv[1])
SAMPLES_PER_TEST = 10

N_PER_TEST = {
    0: 10,
    1: 10,
    2: 15,
    3: 15,
    4: 1000,
    5: 1000,
    6: 10000,
    7: 10000,
    8: 100_000,
    9: 100_000,
}

MAX_VAL_PER_TEST = {
    0: 100,
    1: 100,
    2: 1000_000_000,
    3: 1000_000_000,
    4: 1000_000_000,
    5: 1000_000_000,
    6: 1000_000_000,
    7: 1000_000_000,
    8: 1000_000_000,
    9: 1000_000_000,
}

print(SAMPLES_PER_TEST)

for i in range(1, SAMPLES_PER_TEST + 1):
    N = random.randint(1, N_PER_TEST[TEST_NR])
    MAX_VAL = MAX_VAL_PER_TEST[TEST_NR]

    numbers = [random.randint(1, MAX_VAL) for _ in range(N)]

    print(N)
    print(" ".join(map(str, numbers)))
