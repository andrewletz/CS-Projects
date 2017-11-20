import sys

class Nil:

    def __init__(self):
        self.color = "B"

class Node:

    def __init__(self, key):
        self.color = "B"
        self.key = key
        self.left = Nil()
        self.right = Nil()
        self.p = Nil()

    def __str__(self):
        # debug formatting
        # return "[ {} | {} | {} ]".format(self.left, self.key, self.right)
        return str(self.key)

# Used pseudo-implementation from Cormen's "Introduction to Algorithms" (3rd edition)
class RB:

    def __init__(self):
        self.nil = Node(None)
        self.root = self.nil

    # Left rotate and right rotate are needed for both insert
    # and delete, so we implement them first
    def left_rotate(self, x):
        y = x.right
        x.right = y.left
        if (y.left != self.nil):
            y.left.p = x
        y.p = x.p
        if (x.p == self.nil):
            self.root = y
        elif (x == x.p.left):
            x.p.left = y
        else:
            x.p.right = y
        y.left = x
        x.p = y

    def right_rotate(self, x):
        y = x.left # replace all instances of left  
        x.left = y.right # with right and vice versa
        if (y.right != self.nil):
            y.right.p = x
        y.p = x.p
        if (x.p == self.nil):
            self.root = y
        elif (x == x.p.right):
            x.p.right = y
        else:
            x.p.left = y
        y.right = x
        x.p = y

    # Inserts a node into the tree having key X (logn)
    def insert(self, key):
        z = Node(key)
        y = self.nil
        x = self.root
        while (x != self.nil):
            y = x
            if (z.key < x.key):
                x = x.left
            else:
                x = x.right
        z.p = y
        if (y == self.nil):
            self.root = z
        elif (z.key < y.key):
            y.left = z
        else:
            y.right = z
        z.left = self.nil
        z.right = self.nil
        z.color = "R"
        self.insert_fixup(z)

    def insert_fixup(self, z): # z is a node
        while (z.p.color == "R"):
            if (z.p == z.p.p.left):
                y = z.p.p.right
                if (y.color == "R"):
                    z.p.color = "B"
                    y.color = "B"
                    z.p.p.color = "R"
                    z = z.p.p
                else:
                    if (z == z.p.right):
                        z = z.p
                        self.left_rotate(z)
                    z.p.color = "B"
                    z.p.p.color = "R"
                    self.right_rotate(z.p.p)
            else: # same as previous with right and left swapped
                y = z.p.p.left
                if (y.color == "R"):
                    z.p.color = "B"
                    y.color = "B"
                    z.p.p.color = "R"
                    z = z.p.p
                else:
                    if (z == z.p.left):
                        z = z.p
                        self.right_rotate(z)
                    z.p.color = "B"
                    z.p.p.color = "R"
                    self.left_rotate(z.p.p)
        self.root.color = "B"

    # If the key X is present, removes a node having key X from the tree (logn)
    def remove(self, key):
        if (self.root == self.nil):
            print("TreeError")
            return
        z = self.search_return(self.root, key)
        if (z == self.nil):
            print("TreeError")
            return
        y = z
        y_og = y.color
        if (z.left == self.nil):
            x = z.right
            self.transplant(z, z.right)
        elif (z.right == self.nil):
            x = z.left
            self.transplant(z, z.left)
        else:
            y = self.minimum(z.right)
            y_og = y.color
            x = y.right
            if (y.p == z):
                x.p = y
            else:
                self.transplant(y, y.right)
                y.right = z.right
                y.right.p = y
            self.transplant(z, y)
            y.left = z.left
            y.left.p = y
            y.color = z.color
        if (y_og == "B"):
            self.remove_fixup(x)

    def transplant(self, u, v):
        if (u.p == self.nil):
            self.root = v
        elif (u == u.p.left):
            u.p.left = v
        else:
            u.p.right = v
        v.p = u.p

    def remove_fixup(self, x):
        while (x != self.root and x.color == "B"):
            if (x == x.p.left):
                w = x.p.right
                if (w.color == "R"):
                    w.color = "B"
                    x.p.color = "R"
                    self.left_rotate(x.p)
                    w = x.p.right
                if (w.left.color == "B" and w.right.color == "B"):
                    w.color = "R"
                    x = x.p
                elif (w.right.color == "B"):
                    w.left.color = "B"
                    w.color = "R"
                    self.right_rotate(w)
                    w = x.p.right
                w.color = x.p.color
                x.p.color = "B"
                w.right.color = "B"
                self.left_rotate(x.p)
                x = self.root
            else:
                w = x.p.left
                if (w.color == "R"):
                    w.color = "B"
                    x.p.color = "R"
                    self.right_rotate(x.p)
                    w = x.p.left
                if (w.right.color == "B" and w.left.color == "B"):
                    w.color = "R"
                    x = x.p
                else:
                    if (w.left.color == "B"):
                        w.right.color = "B"
                        w.color = "R"
                        self.left_rotate(w)
                        w = x.p.left
                w.color = x.p.color
                x.p.color = "B"
                w.left.color = "B"
                self.right_rotate(x.p)
                x = self.root
        x.color = "B"

    def search_return(self, x, key): # returns the found node if it exists
        while (x != self.nil) and (key != x.key):
            if key < x.key:
                x = x.left
            else:
                x = x.right
        return x

    # Returns a boolean indicating whether the key X is present (logn)
    def search(self, key):
        current = self.root
        while (current != self.nil):
            if (key == current.key):
                return True
            elif (key < current.key):
                current = current.left # descend left if our key is smaller
            else: # descend right if it isn't
                current = current.right
        return False

    # Returns an integer, the largest key in the tree. Does not alter the tree (logn)
    # Default is largest in entire tree, can also return max of subtree rooted at node
    def maximum(self, node=None):
        if (self.root == self.nil):
            return "Empty"
        if (node == None):
            node = self.root
        while (node.right != self.nil): # keep descending right until we hit a leaf
            node = node.right
        return node

    # Returns an integer, the smallest key in the tree. Does not alter the tree (logn)
    # Default is smallest in entire tree, can also return min of subtree rooted at node
    def minimum(self, node=None):
        if (self.root == self.nil):
            return "Empty"
        if (node == None):
            node = self.root
        while (node.left != self.nil): # keep descending left until we hit a leaf
            node = node.left
        return node

    def isEmpty(self):
        if (self.root == None or self.root == self.nil):
            return True
        return False

# Runtime O(n), in-order traversal representation
# Returns a list, approved by Andrew on Piazza
def print_tree(root_node, lst):
    if (root_node == None or type(root_node) == Nil or root_node == Node(None)):
        return
    print_tree(root_node.left, lst)
    if (root_node.key != None):
        lst.append(root_node.key)
    print_tree(root_node.right, lst)
    return lst

def driver():
    rb = RB()
    
    with open(sys.argv[1]) as f:
        n = int(f.readline().strip())
        #linecount = 0
        for _ in range(n):
            #linecount += 1
            #print("LC: {}".format(linecount))
            in_data = f.readline().strip().split()
            if (len(in_data) == 1):
                if(in_data[0] == "max"):
                    print(rb.maximum())
                elif(in_data[0] == "min"):
                    print(rb.minimum())
                elif(in_data[0] == "print"):
                    if (rb.isEmpty()):
                        print("Empty")
                    else:
                        lst = []
                        print(*print_tree(rb.root, lst), sep=" ")
            elif (in_data[0] == "insert"): # No output
                rb.insert(int(in_data[1]))
            elif(in_data[0] == "remove"): # No output unless not found (covered in method)
                rb.remove(int(in_data[1]))
            elif(in_data[0] == "search"):
                b = rb.search(int(in_data[1]))
                if (b):
                    print("Found")
                else:
                    print("NotFound")

if __name__ == "__main__":
    driver()
