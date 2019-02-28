package Main;

import java.util.concurrent.LinkedBlockingQueue;

public class Producer implements Runnable{
	
	private LinkedBlockingQueue<String> queue;
	private int toProduce;
	private int sum = 0;
	
	public Producer(LinkedBlockingQueue<String> queue, int tP) {
		this.queue = queue;
		this.toProduce = tP;
	}
	
	@Override
	public void run() {
		while(sum < toProduce) {
			double random = Math.random();
			String s = Double.toString(random);
			try {
				queue.put(s);
				sum++;
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			if (sum % 100 == 0) {
				System.out.println("Producer: " + sum + " events produced");
			}
			if (sum == toProduce) {
				while(queue.peek() != null) {
					try {
						Thread.sleep(10);
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}
				Main.finished = true;
			}

		}
		
	}
	
	public int getSum(){
		return this.sum;
	}

}