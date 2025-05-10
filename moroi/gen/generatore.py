#! /usr/bin/python3

import sys
import random

test = int(sys.argv[1])

N = 100_000

print(N)

if test < 4:
    # No rototol
    options = "iiiisd"
    # Pick N random options
    path = "".join([random.choice(options) for _ in range(N)])
    print(path)
elif test < 7:
    # 2 rototols
    options = "iiiisd"
    path = "".join([random.choice(options) for _ in range(N - 2)])
    # Insert 2 'r' at random positions
    p1 = random.randint(0, N - 2)
    path = path[:p1] + "r" + path[p1:]
    p2 = random.randint(p1 + 1, N - 1)
    path = path[:p2] + "r" + path[p2:]
    print(path)
else:
    # Any number of rototols
    options = "iiiiiiiiiissssddddrrrr"
    path = "".join([random.choice(options) for _ in range(N)])
    print(path)
