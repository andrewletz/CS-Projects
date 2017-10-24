import sys
from heapq import *

#                               0                   1              2             3                   
# Is a list of form [(string) IPv4 address, (string) A | B, (int) estimate, (int) order]
class HTTPKey(list):
    
    def __lt__(self, other):
        if (self[1] == other[1] and self[2] == other[2]):
            #print('{} is the same as {}'.format(self[0], other[0]))
            #print('{} is < {}'.format(self[3], other[3]))
            return self[3] < other[3]
        return self[1] < other[1] or self[2] < other[2]


class Minheap:

    def __init__(self):
        self.t = []

    def insert(self, x):
        heappush(self.t, x)

    def remove(self):
        return heappop(self.t)

    def heapify(self):
        heapify(self.t)


def driver():
    heap = Minheap()
    with open(sys.argv[1]) as f:
        n = int(f.readline().strip())
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
