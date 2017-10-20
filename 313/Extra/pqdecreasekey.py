import math

# Created to test pseudo-code for written assignment 2

# Decreases element i and each of its predecessors by v in a binary heap.
# This method is adjusted so that indexing starts at 1 instead of the usual 0!
def PQDecreaseKey(A, i, v):
	# Decrement the first el. by the offset
	A[i - 1] = A[i - 1] - v			
	
	# If there are no predecessors we don’t need to loop
	if (i == 1):
		return

	index = i
	while (True):
		# Get the parent of A[index]
		parent = math.floor(index / 2)	

		# If this value is less than one, the index must be the root,
		# meaning there is no parent left to “improve”
		if (not(parent < 1)):
			A[parent - 1] = A[parent - 1] -  v
			index = parent
			continue
		break
	
	return


if __name__ == "__main__":
    newL = [2, 4, 6, 8, 10, 12, 14]
    PQDecreaseKey(newL, 3, 3)
    print("result of PQDecreaseKey(A, 3, 3) is {}".format(newL))

    newL2 = [2, 4, 6, 8, 10, 12, 14]
    PQDecreaseKey(newL2, 5, 3)
    print("result of PQDecreaseKey(A, 5, 3) is {}".format(newL2))

    newL3 = [2, 4, 6, 8, 10, 12, 14]
    PQDecreaseKey(newL3, 7, 124)
    print("result of PQDecreaseKey(A, 7, 124) is {}".format(newL3))
