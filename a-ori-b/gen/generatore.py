#! /usr/bin/python3

import sys
import random

test = int(sys.argv[1])


def gen_random_string(length):
    return random.choice("123456789") + "".join(
        random.choice("0123456789") for _ in range(length - 1)
    )


if test < 5:
    MAX_LEN = 9
else:
    MAX_LEN = 50000

print(" ".join([gen_random_string(MAX_LEN) for _ in range(2)]))
