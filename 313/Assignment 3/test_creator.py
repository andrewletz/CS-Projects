import random

# Makes a max test for the HTTP requests problem
def driver():
	f = open('tests.input', 'w')
	f.write("1000000\n")
	for n in range(1000000):
		letter = 'A' if random.random() < 0.5 else 'B'
		f.write("IP " + letter + " " + str(random.randint(1, 10000)) + "\n")
    
if __name__ == "__main__":
    driver()
