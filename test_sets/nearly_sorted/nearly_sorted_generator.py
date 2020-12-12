#!/usr/bin/python3

import sys, random, math

for n in range(int(sys.argv[1])):
    offset = math.floor(random.random() * 10 ** int(sys.argv[2]))
    print(n+offset)
