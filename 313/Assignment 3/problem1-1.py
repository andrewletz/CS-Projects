import sys
from heapq import *

#                               0                   1              2             3                   
# Is a list of form [(string) IPv4 address, (string) A | B, (int) estimate, (int) order]
# This allows us to only use 1 heap for all HTTP requests alongside achieving a stable sort
# by including the input order
class HTTPKey(list):
    
    def __lt__(self, other):
        if (self[1] != other[1]): # If their tier isn't equal,
            return self[1] < other[1] # compare tiers
        if (self[2] != other[2]): # If their their estimates aren't the same,
            return self[2] < other[2] # compare estimates
        return self[3] < other[3] # If their tier and estimates are the same, compare order


# Simple minheap built using Python's default heapq library
class Minheap:

    def __init__(self):
        self.t = []

    def insert(self, x):
        heappush(self.t, x)

    def remove(self):
        return heappop(self.t)[0]

    def heapify(self):
        heapify(self.t)


def driver():
    heap = Minheap()
    with open(sys.argv[1]) as f:
        n = int(f.readline().strip())

        # We keep track of order so we have a stable sort
        order = 0
        for _ in range(n):
            in_data = f.readline().strip().split()
            in_data[2] = int(in_data[2])
            in_data.append(order) 
            heap.insert(HTTPKey(in_data))
            order += 1

    while(True):
        try:
            print(heap.remove())
        except IndexError as IE:
            break


if __name__ == "__main__":
    driver()
