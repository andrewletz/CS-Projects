"""
is_member.py: Recursive implementation of is_member() on a set
              represented by a sorted list of integers
Authors: Andrew Letz

CIS 210 assignment 5, part 2, Fall 2016. 
"""
import argparse      # Used in main program to get PIN code from command line
from test_harness import testEQ  # Used in CIS 210 for test cases 

def gen_set(set_file):
    """
    Generates an ordered set from a text file of integers.

    Args:
        set_file: the file that contains the integers to be added
        to the set, 1 per line in any order.
    
    returns:
        an ordered set of the integers taken from set_file
    """
    the_set = []

    for line in set_file:
        the_set.append(int(line))
    return sorted(the_set)

    set_file.close()

def is_member(set, number):
    """
    Uses the binary search method recursively on a set to determine 
    whether or not it contains a number.

    Args:
        set: an ordered set of integers
        number: the number to check if it is in the set
    
    returns:
        true if number is contained in the set, false otherwise
    """
    half = len(set) // 2
    middle_el = set[half]

    if len(set) < 2:
        if middle_el == number:
            return True
        else:
            return False

    if middle_el > number:
        # print(middle_el, 'is larger than', number, ', return', set[:half])
        return is_member(set[:half], number)
    else:
        # print(middle_el, 'is smaller than', number, ', return', set[half:])
        return is_member(set[half:], number)

def run_tests():
    """
    This function runs a set of tests to help you debug your
    program as you develop it.
    """
    l = [-27, -12, -5, -1, 0, 2, 3, 6, 8, 10, 13, 25, 46, 99]
    print("**** TESTING --- Check membership of locally-defined set")
    print(l)
    testEQ("-99 is False", is_member(l, -99), False)
    testEQ("115 is False", is_member(l, 115), False)
    testEQ("-27 is True", is_member(l, -27), True)
    testEQ("99 is True", is_member(l, 99), True)
    testEQ("0 is True", is_member(l, 0), True)
    testEQ("-4 is False", is_member(l, -4), False)
    testEQ("14 is False", is_member(l, 14), False)
    print("*** End of provided test cases.  Add some of your own? ****")

def main():
    """
    Interaction if run from the command line.
    """
    parser = argparse.ArgumentParser(description="Recursive implementation of is_member()")
    parser.add_argument("set", type=argparse.FileType('r'),
                        help="A text file containing set elements, one per line.")
    parser.add_argument("number", type=int, help="number to check for membership")
    args = parser.parse_args()  # gets arguments from command line
    set_file = args.set
    number = args.number
    the_set = gen_set(set_file)
    if is_member(the_set, number):
        print(number, "is an element of the set")
    else:
        print(number, "is not an element of the set")

if __name__ == "__main__":
    #run_tests()  #FIXME: Comment this out when your program is working
    main()     #FIXME: Uncomment this when your program is working
