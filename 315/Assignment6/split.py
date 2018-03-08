import fileinput

words = {}

def dict(w):
	return w in words;

iterDPrint = {}
def iterSplit(s, n):
	a = [i for i in range(n)]
	global iterD
	iterD = {key: False for key in a}

	for i in range(n - 1, -1, -1): # go backwards
		if (iterD[i] == False) and dict(s[i:n]):
			iterD[i] = True
			iterDPrint[i] = s[i:n]

		if iterD[i] == True:
			if i == 0:  # reached the end so if true it is splittable
				return True

			for j in range(i - 1, -1, -1):

				if (iterD[j] == False) and dict(s[j:i]):
					iterD[j] = True
					iterDPrint[j] = s[j:i]

				if (j == 0) and (iterD[j] == True): # reached the end so if true it is splittable
					return True
		

	return False


memo = {}
# returns true if possible to correctly add spaces to x_i, x_i+1... x_n
def split(s, n, i):
	#print("n: {} i: {}".format( n, i))
	if (i == n):
		return True
	if (i in memo):
		return memo[i]
	boo = False
	j = i
	for j in range(n): #
		boo = boo or (dict(s[i:j+1]) and split(s, n, j + 1))
	memo[i] = boo
	return boo

def driver():
	with open("diction10k.txt") as f:
		for line in f:
			words[line.strip()] = True

	counter = 0
	for line in fileinput.input():
		if (line == "\n"):
			break

		if (counter > 0):
			string = line.strip()
			print("\nphrase number:", counter)
			print(string, "\n")


			print("memoized attempt:")
			canBeSplit = split(string, len(string), 0)
			if (canBeSplit):
				print("YES, can be split")
			else:
				print("NO, cannot be split")
			

			if (canBeSplit):
				sortedKeys = []
				for key in memo:
					if(memo[key] == True):
						sortedKeys.append(key)
				sortedKeys = sorted(sortedKeys)

				i = 0
				for key in sortedKeys:
					if (i < len(sortedKeys) - 1):
						i += 1
						print(string[key:sortedKeys[i]], end=' ')

				print(string[sortedKeys[i]:len(string)], end='')
				print("")


			print("\niterative attempt:")
			canBeSplitIter = iterSplit(string, len(string))
			if (canBeSplitIter):
				print("YES, can be split")
			else:
				print("NO, cannot be split")

			if (canBeSplitIter):
				prStr = ""
				i = 0
				while i < len(string):
					word = iterDPrint[i]
					prStr += word
					prStr += " "
					i += len(word)
				print(prStr)

			iterD.clear()
			iterDPrint.clear()
			memo.clear()

 
		counter += 1

if __name__ == "__main__":
	driver()