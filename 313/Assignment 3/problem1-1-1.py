import sys
import heapq

class MyHeap(object):
   def __init__(self, initial=None, key=lambda x:x):
       self.key = key
       if initial:
           self._data = [(key(item), item) for item in initial]
           heapq.heapify(self._data)
       else:
           self._data = []

   def push(self, item):
       heapq.heappush(self._data, (self.key(item), item))

   def pop(self):
       return heapq.heappop(self._data)[1]


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
