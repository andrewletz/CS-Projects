import sys
import fileinput

def driver():
	counter = 0
	for line in fileinput.input():
		if (counter > 0):
			in_data = line.strip().split()
			first, second = int(in_data[0]), int(in_data[1])
			addition = first + second
			mult = first * second
			print("{} {}".format(addition, mult))
		counter += 1

if __name__ == "__main__":
	driver()