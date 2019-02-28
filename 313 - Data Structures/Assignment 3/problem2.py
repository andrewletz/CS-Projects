import sys
from heapq import *

# Simple minheap built using Python's default heapq library
class Minheap:

    def __init__(self):
        self.t = []

    def insert(self, x):
        heappush(self.t, x)

    def remove(self):
        return heappop(self.t)

    def size(self):
    	return len(self.t)

    def peak(self):
        return self.t[0]


# Simple maxheap built using Python's default heapq library
class Maxheap:

    def __init__(self):
        self.t = []

    def insert(self, x):
        heappush(self.t, -1 * x)

    def remove(self):
        return -1 * heappop(self.t)

    def size(self):
        return len(self.t)

    def peak(self):
        return -1 * self.t[0]


def calcMedian(minheap, maxheap):
    minsize = minheap.size()
    maxsize = maxheap.size()
    if (minsize > maxsize):
        return minheap.peak()
    elif (maxsize > minsize):
        return maxheap.peak()
    return (minheap.peak() + maxheap.peak()) / 2


def driver():
    minheap = Minheap()
    maxheap = Maxheap()

    with open(sys.argv[1]) as f:
        n = int(f.readline().strip())

        first = int(f.readline().strip())
        second = int(f.readline().strip())

        # Put the larger element of the first two elements in 
        # the minheap, the smaller into the maxheap
        max_add = first if first < second else second
        min_add = first if first > second else second
        
        maxheap.insert(max_add)
        print(('%f' % calcMedian(minheap, maxheap)).rstrip('0').rstrip('.'))

        minheap.insert(min_add)
        print(('%f' % calcMedian(minheap, maxheap)).rstrip('0').rstrip('.'))

        # For every element after the first two
        # we will do at most one insertion, so this will be nlogn
        for _ in range(n - 2):
            in_data = int(f.readline().strip())

            # If the item < maxheap root, add it there, else add to minheap
            if (in_data < maxheap.peak()):
                maxheap.insert(in_data)
            else:
                minheap.insert(in_data)

            # If the heaps are unbalanced by a number greater than 1, we
            # need to rebalance by removing the root of one and inserting
            # into the other
            if (maxheap.size() - minheap.size() > 1):
                minheap.insert(maxheap.remove())
            if (minheap.size() - maxheap.size() > 1):
                maxheap.insert(minheap.remove())

            # Give the running result
            print(('%f' % calcMedian(minheap, maxheap)).rstrip('0').rstrip('.'))


if __name__ == "__main__":
    driver()
