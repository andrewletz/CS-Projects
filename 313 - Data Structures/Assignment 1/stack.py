import sys
import linkedlist

class Stack:

    def __init__(self):
        self.inner_linked_list = linkedlist.LinkedList()

    def push(self, x):
        self.inner_linked_list.addLast(x)

    def pop(self):
        val = self.inner_linked_list.delLast()
        if (val == None):
            raise Exception("StackError")
            return
        return val

    def is_empty(self):
        self.inner_linked_list.isEmpty()

    def show(self):
        return self.inner_linked_list.show()

def driver():
    s = Stack()
    with open(sys.argv[1]) as f:
        n = int(f.readline().strip())
        for _ in range(n):
            in_data = f.readline().strip().split()
            action, value_option = in_data[0], in_data[1:]
            if action == "push":
                value = int(value_option[0])
                s.push(value)
                print("Pushed {} to the stack".format(value))
            elif action == "pop":
                popped = s.pop()
                print("Popped {} from the stack".format(popped))
            elif action == "print":
                print(s.show())

if __name__ == "__main__":
    driver()
