#! /usr/bin/env python3

N = int(input())

instructions = []

instructions.append("$X0 = 1")
for i in range(1, N + 1):
    instructions.append(f"$X{i} = $X{i - 1} * $X")

line_of_coef = []

for coef_idx in range(0, N + 1):
    l = []
    for coef in range(101):
        idx = len(instructions)
        instructions.append(f"$X{coef_idx} = $X{coef_idx} * {coef}")
        l.append(idx)

    line_of_coef.append(l)

for i in range(0, N + 1):
    instructions.append(f"$Y = $Y + $X{i}")


print(len(instructions))
for instr in instructions:
    print(instr)

print("", end="", flush=True)


poly = [int(i) for i in input().split()]
assert len(poly) == N + 1


to_del = set(i for v in line_of_coef for i in v)

for i in range(N + 1):
    to_del.remove(line_of_coef[i][poly[i]])

print(len(to_del))
print(" ".join(map(str, to_del)))
