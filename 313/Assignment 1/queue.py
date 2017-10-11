import sys
import linkedlist

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
        self.inner_linked_list.isEmpty()

    def show(self):
        return self.inner_linked_list.show()

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
                print("Enqueued {} to the queue".format(value))
            elif action == "dequeue":
                dequeued = q.dequeue()
                print("Dequeued {} from the queue".format(dequeued))
            elif action == "print":
                print(q.show())

if __name__ == "__main__":
    driver()
