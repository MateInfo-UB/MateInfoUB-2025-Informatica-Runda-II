#! /usr/bin/python3

import sys

sys.set_int_max_str_digits(10**6)

A, B = map(int, input().split())

print(A * B)
