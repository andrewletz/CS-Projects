"""
Count the number of occurrences of each major code in a file.
Authors: Andrew Letz (Student I.D 951526623)

Input is a file in which major codes (e.g., "CIS", "UNDL", "GEOG")
appear one to a line. Output is a sequence of lines containing major code
and count, one per major.
"""

import argparse


def count_codes(majors_file):
    """
    Counts the majors in a file and then prints the amount
    of each.
    args:
        majors_file: the file with the list of majors
    returns:
        a printout of the count of each major
    """
    majors = []

    for line in majors_file:
        if line != "\n":    # Checks for empty lines in the file
            majors.append(line.strip())

    if len(majors) == 0:
        print("File is empty")
        return

    majors = sorted(majors)

    # Loop to count majors using control-break logic
    majors.append("!")    # Sentinel value
    count = 0
    previous_major = ""
    for major in majors:
        if (previous_major == ""):
            count = 0
        elif (major == previous_major):
            count = count + 1
        else:
            count = count + 1
            print(previous_major, count)    # if it is a new major, print the previous major with its count
            count = 0                       # and begin a new count
        previous_major = major


def main():
    """
    Interaction if run from the command line.
    Usage:  python3 counts.py  majors_code_file.txt
    """
    parser = argparse.ArgumentParser(description="Count major codes")
    parser.add_argument('majors', type=argparse.FileType('r'),
                        help="A text file containing major codes, one major code per line.")
    args = parser.parse_args()  # gets arguments from command line
    majors_file = args.majors
    count_codes(majors_file)


if __name__ == "__main__":
    main()
