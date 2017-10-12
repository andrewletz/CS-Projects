import sys
import linkedlist
import copy

class Queue:

    def __init__(self):
        self.inner_linked_list = linkedlist.LinkedList()

    def enqueue(self, x):
        self.inner_linked_list.addFirst(x)

    def dequeue(self):
        val = self.inner_linked_list.delLast()
        if (val == None):
            raise Exception("QueueError")
            return
        return val

    def is_empty(self):
        return self.inner_linked_list.isEmpty()

    def length(self):
        return self.inner_linked_list.length()


def print_queue(q):
    qCopy = copy.deepcopy(q)
    if(qCopy.is_empty()):
        print("Empty", end='')
    while(not qCopy.is_empty()):
        dequeued = qCopy.dequeue()
        print("{} ".format(dequeued), end='')
    print("")


def queue_max(q):
    qCopy = copy.deepcopy(q)
    if(qCopy.is_empty()):
        raise Exception("QueueError")
    largest = None
    while(not qCopy.is_empty()):
        dequeued = qCopy.dequeue()
        if (largest == None or dequeued > largest):
            largest = dequeued
    return largest


def driver():
    q = Queue()
    with open(sys.argv[1]) as f:
        n = int(f.readline().strip())
        for _ in range(n):
            in_data = f.readline().strip().split()
            action, value_option = in_data[0], in_data[1:]
            if action == "enqueue":
                value = int(value_option[0])
                q.enqueue(value)
                print("{}".format(value))
            elif action == "dequeue":
                try:
                    #dequeued = q.dequeue()
                    q.dequeue()
                except:
                    print("QueueError")
                #else:
                    #print("dequeued {}".format(dequeued))
            elif action == "print":
                print_queue(q)
            elif action == "max":
                try:
                    print("{}".format(queue_max(q)))
                except:
                    print("QueueError")


if __name__ == "__main__":
    driver()
