package Main;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;

public class Logic {
	
	/*
	 * Outputs text file with first & last name and phone number of all individuals whose last name contains the string key
	 */
	public static void outputTextSearch(ArrayList<Entry> entries, String key) {
		
		BufferedWriter bw = null;
		FileWriter fw = null;
		
		try {
			
			fw = new FileWriter("Output.txt");
			bw = new BufferedWriter(fw);
			
			for (Entry e : entries) {
				if (e.getFirst().contains(key) || e.getLast().contains(key)) {
					bw.write(e.toString());
					bw.write("\n");
				}
			}
			
		} catch (IOException e) {
			
			e.printStackTrace();
			
		} finally {
			
			try {
				
				if (bw != null)
					bw.close();
				
				if (fw != null)
					fw.close();
				
			} catch (IOException e) {
				e.printStackTrace();
			}
			
		}
	}
	
	/*
	 * Returns true if input arraylist of entries is correctly ordered by last name, false otherwise
	 */
	public static boolean lexiCheck(ArrayList<Entry> input) {
		ArrayList<String> baseArray = new ArrayList<String>(input.size());
		ArrayList<String> sortedArray = new ArrayList<String>(input.size());
		for(Entry e : input) {
			baseArray.add(e.getLast());
			sortedArray.add(e.getLast());
		}
		Collections.sort(sortedArray);
		
		for(int i = 0; i < baseArray.size() - 1; i++) {
			if (baseArray.get(i) != sortedArray.get(i)) {
				return false;
			}
		}
		return true;
		
	}
	
	public static ArrayList<Entry> selectionSort(ArrayList<Entry> input) {
		int size = input.size();
		
		// Create a new list we can mess with
		ArrayList<Entry> newList = new ArrayList<Entry>(size);
		for(Entry e : input) {
			newList.add(e.clone());
		}
		
		for(int i = 0; i < size - 1; i++) {
			int idx = i;
			Entry lowestEntry = newList.get(idx);
			for(int j = i + 1; j < size; j++) {
				if (lowestEntry.getLast().compareTo(newList.get(j).getLast()) > 0) {
					lowestEntry = newList.get(j);
					idx = j;
				}
			}
			Entry smallerEntry = lowestEntry;
			newList.set(idx, newList.get(i));
			newList.set(i, smallerEntry);
			
		}
		
		return newList;
	}
	
	public static ArrayList<Entry> mergeSort(ArrayList<Entry> input) {
		// Create a new list we can mess with and pass into the recursive method
		ArrayList<Entry> newList = new ArrayList<Entry>(input.size());
		for(Entry e : input) {
			newList.add(e.clone());
		}
		
		return mergeRecurse(newList, 0, input.size() - 1);
	}

	public static ArrayList<Entry> mergeRecurse(ArrayList<Entry> input, int low, int high) {
		if ((high-low) >= 1) {
			int middle = (low + high) / 2;
			int next = middle + 1;
			
			mergeRecurse(input, low, middle);
			mergeRecurse(input, next, high);
			
			merge(input, low, middle, next, high);
		}
		return input;
	}
	
	/*
	 * Utilized examples and description from book listed in syllabus (Java How To Program (Early Objects) (10th Edition))
	 */
	public static void merge(ArrayList<Entry> input, int left, int middle, int next, int right) {
		int leftIdx = left;
		int rightIdx = next;
		int combinedIdx = left;
		ArrayList<Entry> combined = new ArrayList<Entry>(Collections.nCopies(input.size(), new Entry("", "", 0)));
		
		while (leftIdx <= middle && rightIdx <= right) {
			if(input.get(leftIdx).getLast().compareTo(input.get(rightIdx).getLast()) < 0) {
				combined.set(combinedIdx++, input.get(leftIdx++));
			} else {
				combined.set(combinedIdx++, input.get(rightIdx++));
			}
		}
		
		if (leftIdx == next) {
			while (rightIdx <= right) {
				combined.set(combinedIdx++, input.get(rightIdx++));
			}
		} else {
			while (leftIdx <= middle) {
				combined.set(combinedIdx++, input.get(leftIdx++));
			}
		}
		
		for (int i = left; i <= right; i++) {
			input.set(i, combined.get(i));
		}
	}
}
