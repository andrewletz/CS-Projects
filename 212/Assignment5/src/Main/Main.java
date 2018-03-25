package Main;

import java.io.IOException;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.NoSuchElementException;
import java.util.Scanner;

public class Main {
	
	private static ArrayList<Entry> entries = new ArrayList<Entry>();
	private static Scanner input;
	private static String fileName = "Assignment5_phonebook.txt";
	
	public static void main(String[] args) {
		openFile();
		writeToArrayList();
		closeFile();
		
		Logic.outputTextSearch(entries, "new");
		
		long selectionSortTime = System.nanoTime(); 
		ArrayList<Entry> selectionSorted = Logic.selectionSort(entries);
		System.out.println("Selection Sort: " + ((System.nanoTime() - selectionSortTime) / 1000000000.0) + " s");
		
		long mergeSortTime = System.nanoTime(); 
		ArrayList<Entry> mergeSorted = Logic.mergeSort(entries);
		System.out.println("Merge Sort: " + ((System.nanoTime() - mergeSortTime) / 1000000000.0) + " s");
		
		System.out.println("\nOriginal list sorted? " + Logic.lexiCheck(entries));
		
		System.out.println("Selection-sorted list sorted? " + Logic.lexiCheck(selectionSorted));
		System.out.println("Merge-sorted list sorted? " + Logic.lexiCheck(mergeSorted));
		
		System.out.println("Was original list modified after sorting? " + Logic.lexiCheck(entries));
	}
	
	public static void openFile() {
		try {
			input = new Scanner(Paths.get(fileName));
		}
		catch (IOException ioException) {
			System.err.println("Error opening file.");
			System.exit(1);
		}
	}
	
	public static void writeToArrayList() {
		try {
			while (input.hasNextLine()) {
				String[] split = (input.nextLine()).split("\\s+");
				String name = split[1].replaceAll(",", "");
				entries.add(new Entry(name, split[2], Integer.parseInt(split[0])));
			}
		} catch (NoSuchElementException elementException) {
			System.err.println("Nope");
		} catch (IllegalStateException stateException) {
			System.err.println("Nope 2.0");
		}
	}
	
	public static void closeFile() {
		if (input != null)
			input.close();
	}
	
}
