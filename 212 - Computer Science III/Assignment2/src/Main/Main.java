package Main;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.InputMismatchException;
import java.util.Scanner;
import java.util.Random;

public class Main {
	
	private static int step = 1;
	private static int arrayLength;
	private static double density;
	
	public static void main(String[] args) {
		boolean running = true;
		Scanner sc = new Scanner(System.in);

		while (running) {
			switch (step) {
			case 1:
				System.out.println("Please enter array length:");
				try {
					arrayLength = sc.nextInt();
					if (arrayLength < 1) {
						System.out.println("Array must be greater than 0.");
						break;
					} else {
						step++;
					}
				} catch (InputMismatchException invalidInput) {
					System.out.println(invalidInput + " : Invalid array length (integer)!");
					sc.next();
				}
				break;
			case 2:
				System.out.println("Please enter array density:");
				try {
					density = sc.nextDouble();
					if (density < 0.0 || density > 1.0) {
						System.out.println("Density must be between 0.0 and 1.0.");
						break;
					} else {
						step++;
					}
				} catch (InputMismatchException invalidInput) {
					System.out.println(invalidInput + " : Invalid array density (double)!");
					sc.next();
				}
				break;
			case 3:
				running = false;
				sc.close();
				break;
			default:
			}
		}
		
		long createDenseTime = System.nanoTime();   
		int[] array = denseArray(arrayLength, density);
		System.out.println("Time to create dense array of length " + arrayLength + ": " + ((System.nanoTime() - createDenseTime) / 1000000) + " ms");
		
		long convertDenseTime = System.nanoTime();   
		ArrayList<int[]> convertedArray = denseToSparse(array);
		System.out.println("Time to convert dense array of length " + arrayLength + " to length " + convertedArray.size() + " sparse array: " + ((System.nanoTime() - convertDenseTime) / 1000000) + " ms");
		
		long createSparseTime = System.nanoTime();   
		ArrayList<int[]> sArray = sparseArray(arrayLength, density);
		System.out.println("Time to create sparse array of length " + arrayLength + ": " + ((System.nanoTime() - createSparseTime) / 1000000) + " ms");
		
		long convertSparseTime = System.nanoTime();   
		int[] convertedToDense = sparseToDense(sArray, arrayLength);
		System.out.println("Time to convert sparse array of length " + arrayLength + " to length " + convertedToDense.length + " dense array: " + ((System.nanoTime() - convertSparseTime) / 1000000) + " ms");
		
		long findMaxDenseTime = System.nanoTime();
		int[] maxDense = denseMax(array);
		System.out.println("Max value in dense array: " + maxDense[0] + " at " + maxDense[1]);
		System.out.println("Time taken to find: " + ((System.nanoTime() - findMaxDenseTime) / 1000000) + " ms");
		
		long findMaxSparseTime = System.nanoTime();
		int[] maxSparse = sparseMax(sArray);
		System.out.println("Max value in sparse array: " + maxSparse[0] + " at " + maxSparse[1]);
		System.out.println("Time taken to find: " + ((System.nanoTime() - findMaxSparseTime) / 1000000) + " ms");
		
	}
	
	private static int[] denseArray(int l, double d) {
		int[] array = new int[l];
		Random rand = new Random();
		for (int i = 0; i < array.length; i++) {
			if (rand.nextDouble() >= d) {
				array[i] = 0;
			} else {
				array[i] = rand.nextInt(1000000);
			}
		}
		return array;
	}
	
	private static ArrayList<int[]> sparseArray(int l, double d) {
		ArrayList<int[]> arrayL = new ArrayList<int[]>();
		Random rand = new Random();
		for (int i = 0; i < l; i++) {
			if (rand.nextDouble() <= d) {
				int a[]= {i, rand.nextInt(1000000)};
				arrayL.add(a);
			}
		}
		return arrayL;
	}
	
	private static ArrayList<int[]> denseToSparse(int[] dArray) {
		ArrayList<int[]> arrayL = new ArrayList<int[]>();
		for (int i = 0; i < dArray.length; i++) {
			if (dArray[i] != 0) {
				int a[]= {i, dArray[i]};
				arrayL.add(a);
			}
		}
		return arrayL;
	}
	
	private static int[] sparseToDense(ArrayList<int[]> sparse, int l) {
		int[] dense = new int[l];
		for (int i = 0; i < sparse.size(); i++) {
			int[] a = sparse.get(i);
			dense[a[0]] = a[1];
		}
		return dense;
	}
	
	private static int[] denseMax(int[] dArray) {
		int[] max = {0, 0};
		for (int i = 0; i < dArray.length; i++) {
			if (dArray[i] > max[0]) {
				max[0] = dArray[i];
				max[1] = i;
			}
		}
		return max;
	}
	
	private static int[] sparseMax(ArrayList<int[]> sparse) {
		int[] max = {0, 0};
		for (int[] a : sparse) {
			if (a[1] > max[1]) {
				max[0] = a[0];
				max[1] = a[1];
			}
		}
		return max;
	}
}


