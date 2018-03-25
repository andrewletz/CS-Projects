package Main;

import java.util.ArrayList;
import java.util.Random;

public class Main {
	
	public static void main(String[] args) {
		ArrayList<Measurable> objs = new ArrayList<>();
		int numRect = 0, numBox = 0, numCircle = 0, numSphere = 0;
		
		Random rand = new Random();
		for (int i = 0; i < 1000; i++) {
			int num = rand.nextInt(4);
			switch (num) {
			case 0:
				objs.add(new Rectangle(nextDouble(), nextDouble()));
				numRect++;
				break;
			case 1:
				objs.add(new Box(nextDouble(), nextDouble(), nextDouble()));
				numBox++;
				break;
			case 2:
				objs.add(new Circle(nextDouble()));
				numCircle++;
				break;
			case 3:
				objs.add(new Sphere(nextDouble()));
				numSphere++;
				break;
			}
		}
		
		System.out.println("rects: " + numRect + " boxes: " + numBox + " circles: " + numCircle + " spheres: "
				+ numSphere);
		System.out.println("sum: " + calculateSum(objs));
	}
	
	private static double nextDouble() {
		Random rand = new Random();
		return rand.nextDouble() * (1 - java.lang.Double.MIN_VALUE) + java.lang.Double.MIN_VALUE;
	}
	
	private static double calculateSum(ArrayList<Measurable> objs) {
		double sum = 0;
		for (Measurable obj : objs) {
			sum += obj.getArea();
		}
		
		return sum;
	}

}
