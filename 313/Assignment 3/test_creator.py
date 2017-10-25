import random

# Makes a max test for the HTTP requests problem
def driver():
	f = open('millionhttp.input', 'w')
	f.write("1000000\n")
	for n in range(1000000):
		letter = 'A' if random.random() < 0.5 else 'B'
		f.write("IP " + letter + " " + str(random.randint(1, 10000)) + "\n")

# Makes a max test for the rolling median problem
def driver2():
	f = open('maxmedian.input', 'w')
	f.write("100000\n")
	for n in range(100000):
		f.write(str(random.randint(0, 1000000)) + "\n")
    
if __name__ == "__main__":
    driver2()
