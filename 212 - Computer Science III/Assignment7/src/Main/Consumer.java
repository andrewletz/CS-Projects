package Main;

import java.util.Random;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.TimeUnit;

public class Consumer implements Runnable{

	private LinkedBlockingQueue<String> queue;
	private int sum = 0;
	private String name = "";
	
	public Consumer(LinkedBlockingQueue<String> q, String n) {
		this.queue = q;
		this.name = n;
	}
	
	@Override
	public void run() {
		Random rand = new Random();
		while (!Main.finished) {
			try {
				Thread.sleep((long)(rand.nextDouble()*10));
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			try {
				if (queue.peek() != null) {
					queue.poll(50, TimeUnit.MILLISECONDS);
					sum++;
				}
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			if (sum % 100 == 0 && sum != 0) {
				System.out.println(this.name + ": " + sum + " events consumed");
			}
		}
	}
	
	public int getSum(){
		return this.sum;
	}
	
}
