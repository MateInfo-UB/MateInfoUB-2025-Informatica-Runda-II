#!/usr/bin/env python3

import sys

input_file = sys.argv[1]
fin = open(input_file, "r")

N = int(fin.readline())
assert 0 <= N <= 100_000

ops = fin.readline().strip()
assert len(ops) == N

assert all(c in "isdr" for c in ops)
