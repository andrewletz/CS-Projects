package Main;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.TimeUnit;

public class Main {

	static boolean finished = false;
	
	public static void main(String[] args) throws InterruptedException {
		
		LinkedBlockingQueue<String> queue = new LinkedBlockingQueue<String>(100);
		
		ExecutorService eService = Executors.newCachedThreadPool();
		
		Producer p = new Producer(queue, 1000);
		Consumer c1 = new Consumer(queue, "Consumer 1");
		Consumer c2 = new Consumer(queue, "Consumer 2");
//		Consumer c3 = new Consumer(queue, "Consumer 3");
		
		eService.execute(p);
		eService.execute(c1);
		eService.execute(c2);
//		eService.execute(c3);
		
		eService.shutdown();
		eService.awaitTermination(1, TimeUnit.MINUTES);
		
		System.out.println("\nProducer produced " + p.getSum() + " events");
		System.out.println("Consumer 1 consumed " + c1.getSum() + " events");
		System.out.println("Consumer 2 consumed " + c2.getSum() + " events");
//		System.out.println("Consumer 3 consumed " + c3.getSum() + " events");
	}
	
}