import sys
import queue

def cycler(restaurants):
	# This runs in O(n) time utilizing a queue
	initial_length = restaurants.length()
	energy = 0
	index = 0
	counter = 0
	while(counter < initial_length):
		counter += 1
		restaurant = restaurants.dequeue() # Take out the next restaurant
		energy += restaurant[0]
		distance = restaurant[1]
		if(energy >= distance): # If we can get to the next restaurant
			energy -= distance # Get our leftover energy
		else:
			index = counter # If we cant get to the next restaurant, set the next as our starting point
		restaurants.enqueue(restaurant) # Put the restaurant back on the queue
	return index


def driver():
    q = queue.Queue()
    with open(sys.argv[1]) as f:
        n = int(f.readline().strip())
        for _ in range(n):
            in_data = f.readline().strip().split()
            e_d = (int(in_data[0]), int(in_data[1]))
            q.enqueue(e_d)
    print(cycler(q))


if __name__ == "__main__":
    driver()
