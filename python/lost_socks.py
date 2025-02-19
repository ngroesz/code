import random
from pprint import pprint

random.seed()

pair_counts = {}

for i in range(1000000):
    socks = sum((['L'] * 6, ['R'] * 6), [])
    random.shuffle(socks)
    lost_sock_count = int(random.random() * 4)
    for l in range(lost_sock_count):
        lost_sock_index = int(random.random() * len(socks))
        del socks[lost_sock_index]

    l_count = 0
    r_count = 0
    for sock in socks:
        if sock == 'L':
            l_count = l_count + 1
        elif sock == 'R':
            r_count = r_count + 1

    pair_count = min((l_count, r_count))

    if pair_count in pair_counts:
        pair_counts[pair_count] = pair_counts[pair_count] + 1
    else:
        pair_counts[pair_count] = 1

pprint(pair_counts)
