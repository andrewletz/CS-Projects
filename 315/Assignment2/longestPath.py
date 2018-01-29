import fileinput

def longestPath(W, N, M):
	LP = {1: 0}
	NP = {}

	for edge in W:
		#print("{}: LP[{}] is now the max of [{}] and [{} + {}]".format(edge, edge[1], LP.get(edge[1], -999), LP.get(edge[0], -999), W.get(edge)))
		LP[edge[1]] = max(LP.get(edge[1], -999), LP.get(edge[0], -999) + W.get(edge))
		if (LP[edge[1]] == (LP.get(edge[0], -999) + W.get(edge))):
			NP[edge[1]] = NP.get(edge[1], 1) + NP.get(edge[1], 0)

	print("longest path is: {}".format(LP.get(N)))
	print("number of longest paths: {}".format(NP[N]))


def driver():
	N = 0
	M = 0
	W = {}
	counter = 0
	for line in fileinput.input():
		if (line == "\n"):
			break

		# Add an edge pair to our adjacency list
		if (counter > 0):
			in_data = line.strip().split()
			start, end, weight = int(in_data[0]), int(in_data[1]), int(in_data[2])
			W[start, end] = weight

		else:
			in_data = line.strip().split()
			first, second = int(in_data[0]), int(in_data[1])
			N = first
			M = second

		counter += 1

	longestPath(W, N, M)

if __name__ == "__main__":
	driver()