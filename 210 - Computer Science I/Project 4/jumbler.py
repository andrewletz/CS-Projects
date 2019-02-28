"""
Solve a jumble (anagram) by checking against each word in a dictionary
Authors: Andrew Letz    

Usage: python3 jumbler.py jumbleword wordlist.txt
"""

import argparse

def jumbler(jumble, dict_file_name):
    """
    Searches a dictionary file for an anagram equivalent to a given jumble.

    Args:
        jumble: a jumbled string of letters
        dict_file_name: a dictionary text file, with words separated
        by a line
    
    output:
        prints the matches, then the amount of matches compared to
        the total number of words in dict_file_name

    """

    file = open(dict_file_name, "r")

    ln_count = 0
    matches = 0
    for line in file:
        ln_count += 1
        strip_line = line.strip()
        if(sorted(strip_line) == sorted(jumble)):
            print(strip_line)
            matches += 1

    if(matches == 0):
        print('No matches')
    elif(matches == 1):
        print('1 match in', ln_count, 'words')
    else:
        print(matches, 'matches in', ln_count, 'words')

    file.close()

def main():
    """
    collect command arguments and invoke jumbler()
    inputs:
        none, fetches arguments using argparse
    effects:
        calls jumbler()
    """
    parser = argparse.ArgumentParser(description="Solve a jumble (anagram)")
    parser.add_argument("jumble", type=str, help="Jumbled word (anagram)")
    parser.add_argument('wordlist', type=str,
                        help="A text file containing dictionary words, one word per line.")
    args = parser.parse_args()  # gets arguments from command line
    jumble = args.jumble
    wordlist = args.wordlist
    jumbler(jumble, wordlist)

if __name__ == "__main__":
    main()
