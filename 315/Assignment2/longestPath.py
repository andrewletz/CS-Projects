import fileinput

class Vertex:

    def __init__(self):
        self.adj = {} # adj dictionary in form {other_node : weight}
        self.lp = -999 # longest path to this node
        self.np = 0 # number of longest paths

def longestPath(W, N):
	W[1].lp = 0
	W[1].np = 1

	for v_key in sorted(W): # for every vertice in our graph
		for av_key in W[v_key].adj: # for every vertice in its adj list
			start = v_key
			end = av_key
			weight = W[v_key].adj[av_key]
			if(W[end].lp == (W[start].lp + weight)):
				W[end].np += W[start].np # add number of paths
			else:
				W[end].np = W[start].np
			W[end].lp = max(W[end].lp, W[start].lp + weight)

	print("longest path is: {}".format(W[N].lp))
	print("number of longest paths: {}".format(W[N].np))


def driver():
	N = 0
	W = {}
	counter = 0
	for line in fileinput.input():
		if (line == "\n"):
			break
		if (counter < 1):
			in_data = line.strip().split()
			N = int(in_data[0])

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

	longestPath(W, N)

if __name__ == "__main__":
	driver()