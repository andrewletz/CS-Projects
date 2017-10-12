import sys
import stack

def isWellFormed(input_string):
    matching = {']' : '[', ')' : '(', '}' : '{', '>' : '<'}
    s = stack.Stack()

    for c in input_string:
        if c == '[' or c == '(' or c == '{' or c == '<':
            s.push(c)
        if c == ']' or c == ')' or c == '}' or c == '>':
            if(matching[c] != s.pop()):
                return False

    return True; 

def driver():
    with open(sys.argv[1]) as f:
        n = int(f.readline().strip())
        for _ in range(n):
            in_data = f.readline().strip().split()
            string = in_data[0]
            wellFormedBool = isWellFormed(string)
            print("YES" if wellFormedBool else "NO")


if __name__ == "__main__":
    driver()
