"""
draw_barcode.py: Draw barcode representing a ZIP code using Turtle graphics
Authors: Andrew Letz

CIS 210 assignment 3, part 2, Fall 2016.
"""
import argparse	# Used in main program to obtain 5-digit ZIP code from command
                # line
import time	# Used in main program to pause program before exit
import turtle	# Used in your function to print the bar code

## Constants used by this program
SLEEP_TIME = 30	# number of seconds to sleep after drawing the barcode
ENCODINGS = [[1, 1, 0, 0, 0],	# encoding for '0'
             [0, 0, 0, 1, 1],	# encoding for '1'
             [0, 0, 1, 0, 1],   # encoding for '2'
             [0, 0, 1, 1, 0],	# encoding for '3'
             [0, 1, 0, 0, 1],	# encoding for '4'
             [0, 1, 0, 1, 0],	# encoding for '5'
             [0, 1, 1, 0, 0],	# encoding for '6'
             [1, 0, 0, 0, 1],	# encoding for '7'
             [1, 0, 0, 1, 0],	# encoding for '8'
             [1, 0, 1, 0, 0]	# encoding for '9'
            ]
SINGLE_LENGTH = 25	# length of a short bar, long bar is twice as long

def compute_check_digit(digits):
    """
    Compute the check digit for use in ZIP barcodes
    args:
        digits: list of 5 integers that make up zip code
    returns:
        check digit as an integer
    """
    sum = 0
    for i in range(len(digits)):
        sum = sum + digits[i]
    check_digit = 10 - (sum % 10)
    if (check_digit == 10):
        check_digit = 0
    return check_digit

def draw_bar(my_turtle, digit):
    """
    Draws a vertical bar using the turtle module.
    args:
        my_turtle: uses a turtle from the turtle module to perform the action
        digit: if a 0, draws a small bar. if anything else, draws a long bar.
    """
    my_turtle.left(90)
    if digit == 0:
        length = SINGLE_LENGTH
    else:
        length = 2 * SINGLE_LENGTH
    my_turtle.forward(length)
    my_turtle.up()
    my_turtle.backward(length)
    my_turtle.right(90)
    my_turtle.forward(10)
    my_turtle.down()

def draw_zip(my_turtle, zip):
    """
    Draws a barcode using a 5 digit zip code and the turtle module.
    args:
        my_turtle: uses a turtle from the turtle module to perform the action
        zip: a 5 digit zip code used as the basis for the barcode
    """
    draw_bar(my_turtle, 1)
    zip_str = str(zip)
    for ch in zip_str:
        my_list = ENCODINGS[int(ch)]
        for index in range(5):
            draw_bar(my_turtle, my_list[index])

    zip_list = []
    for digit in zip_str:
        zip_list.append(int(digit))

    for i in range(5):
        checksum_list = ENCODINGS[compute_check_digit(zip_list)]
        draw_bar(my_turtle, checksum_list[i])
    draw_bar(my_turtle, 1)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("ZIP", type=int)
    args = parser.parse_args()
    zip = args.ZIP
    if zip <= 0 or zip > 99999:
        print("zip must be > 0 and < 100000; you provided", zip)
    else:
        my_turtle = turtle.Turtle()
        draw_zip(my_turtle, zip)
        time.sleep(SLEEP_TIME)


if __name__ == "__main__":
    main()
