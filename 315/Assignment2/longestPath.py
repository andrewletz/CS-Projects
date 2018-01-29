import fileinput

class Vertex:

    def __init__(self):
        self.adj = {}
        self.lp = -999
        self.np = 0

def longestPath(W, N, M):
	W[1].lp = 0

	for v_key in W:
		for av_key in W[v_key].adj:
			start = v_key
			end = av_key
			weight = W[v_key].adj[av_key]
			W[end].lp = max(W[end].lp, W[start].lp + weight)
			

	print("longest path is: {}".format(W[N].lp))
	#print("number of longest paths: {}".format(NP[N]))


def driver():
	N = 0
	M = 0
	W = {}
	counter = 0
	for line in fileinput.input():
		if (line == "\n"):
			break
		if (counter < 1):
			in_data = line.strip().split()
			first, second = int(in_data[0]), int(in_data[1])
			N = first
			M = second
		# Add an edge pair to our adjacency list
		if (counter > 0):
			in_data = line.strip().split()
			start, end, weight = int(in_data[0]), int(in_data[1]), int(in_data[2])
			if (W.get(start) == None):
				W[start] = Vertex()
				W[start].adj[end] = weight
			else:
				W[start].adj[end] = weight
 
		counter += 1

	for i in range(1, N+1):
		if (W.get(i) == None):
			W[i] = Vertex()

	longestPath(W, N, M)

if __name__ == "__main__":
	driver()