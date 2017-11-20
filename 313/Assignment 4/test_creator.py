import random

# Makes a max test for the HTTP requests problem
def driver():
	f = open('hugerb.input', 'w')
	f.write("1000000\n")
	num_set = set()
	for n in range(1000000):
		choice = random.random()
		if (choice <= 0.2):
			num = str(random.randint(-1000000, 1000000))
			if (num not in num_set):
				f.write("insert " + num + "\n")
				num_set.add(num)
			else:
				f.write("min" + "\n")
		elif (choice <= 0.4):
			f.write("remove " + str(random.randint(-1000000, 1000000)) + "\n")
		elif (choice <= 0.6):
			f.write("search " + str(random.randint(-1000000, 1000000)) + "\n")
		elif (choice <= 0.8):
			f.write("max" + "\n")
		elif (choice <= 1):
			f.write("min" + "\n")
		else:
			f.write("min" + "\n")
		#elif (choice <= 1):
		#	f.write("print" + "\n")

if __name__ == "__main__":
	driver()