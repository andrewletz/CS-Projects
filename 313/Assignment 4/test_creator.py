import random

# Makes a max test for the HTTP requests problem
def driver():
	f = open('10000.input', 'w')
	f.write("10000\n")
	num_set = set()
	for n in range(10000):
		choice = random.random()
		if (choice <= 0.2):
			num = str(random.randint(-100000, 100000))
			if (num not in num_set):
				f.write("insert " + num + "\n")
				num_set.add(num)
			else:
				f.write("min" + "\n")
		elif (choice <= 0.4):
			f.write("remove " + str(random.randint(-100000, 100000)) + "\n")
		elif (choice <= 0.6):
			f.write("search " + str(random.randint(-100000, 100000)) + "\n")
		elif (choice <= 0.8):
			f.write("max" + "\n")
		elif (choice <= 0.999):
			f.write("min" + "\n")
		elif (choice <= 1):
			f.write("print" + "\n")
		else:
			f.write("min" + "\n")

if __name__ == "__main__":
	driver()
