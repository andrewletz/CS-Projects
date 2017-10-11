import sys
import linkedlist
import copy

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
        return self.inner_linked_list.isEmpty()

    def length(self):
        return self.inner_linked_list.length()


def print_stack(s):
    sCopy = copy.deepcopy(s)
    if(sCopy.is_empty()):
        print("Empty", end='')
    while(not sCopy.is_empty()):
        popped = sCopy.pop()
        print("{} ".format(popped), end='')
    print("")


def stack_max(s):
    sCopy = copy.deepcopy(s)
    if(sCopy.is_empty()):
        raise Exception("StackError")
    largest = None
    while(not sCopy.is_empty()):
        popped = sCopy.pop()
        if (largest == None or popped > largest):
            largest = popped
    return largest


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
                #print("push {}".format(value))
            elif action == "pop":
                try:
                    popped = s.pop()
                except:
                    print("StackError")
                else:
                    print("{}".format(popped))
            elif action == "print":
                print_stack(s)
            elif action == "max":
                try:
                    print("{}".format(stack_max(s)))
                except:
                    print("StackError")

if __name__ == "__main__":
    driver()
