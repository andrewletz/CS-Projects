class Node:

    def __init__(self, input_data, previous_node, next_node):
        self.data = input_data
        self.prev = previous_node
        self.next = next_node

class LinkedList:

    def __init__(self):
        self.head = None
        self.tail = None

    def isEmpty(self):
    	return self.head == None

    def length(self):
        if(self.isEmpty()):
            return 0
        count = 1
        node = self.head
        while(node.next != None):
            count += 1
            node = node.next
        return count

    def addFirst(self, input):
        oldHead = self.head
        newNode = Node(input, None, oldHead)
        if(self.isEmpty()):
            self.tail = newNode
        if(not self.isEmpty()):
            oldHead.prev = newNode
        self.head = newNode

    def addLast(self, input):
        if (self.isEmpty()):
            self.addFirst(input)
        else:
            newNode = Node(input, self.tail, None)
            self.tail.next = newNode
            self.tail = newNode

    def delLast(self):
        if (self.isEmpty()):
            return
        if (self.head.next == None):
            temp = self.head.data
            self.head = None
            return temp
        else:
            temp = self.tail.data
            prev_node = self.tail.prev
            self.tail = None
            self.tail = prev_node
            self.tail.next = None
            return temp