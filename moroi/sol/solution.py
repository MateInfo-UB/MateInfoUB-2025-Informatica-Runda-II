#! /usr/bin/env python3

N = int(input())

deltas = [(1, 0), (0, 1), (-1, 0), (0, -1)]

ans = 0

operations = input().strip().split("r")

for op in operations:
    x, y, dir = 0, 0, 0
    for s in op:
        if s == "i":
            x += deltas[dir][0]
            y += deltas[dir][1]
        elif s == "s":
            dir = (dir + 1) % 4
        elif s == "d":
            dir = (dir - 1) % 4
        else:
            assert False, f"Unknown command: {s}"

    ans += abs(x) + abs(y)

print(ans)
