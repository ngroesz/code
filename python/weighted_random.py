#!/usr/bin/env python3

import random

def pick_a_random_item():
    items = [30, 50, 75]

    sum_of_weight = sum(items)

    random_number = int(random.random() * sum_of_weight)

    for i in range(0, len(items)):
        if random_number < items[i]:
            return i
        random_number -= items[i]

a, b, c = [0] * 3
for i in range(0, 100):
    result = pick_a_random_item()

    if result == 0:
        a += 1
    elif result == 1:
        b += 1
    elif result == 2:
        c += 1

print("a: {}\nb: {}\nc: {}".format(a, b, c))
