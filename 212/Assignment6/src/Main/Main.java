package Main;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;

public class Main {

	public static void main(String[] args) {
		// Testing an int set
		OccurrenceSet<Integer> intSet = new OccurrenceSet<Integer>();
		intSet.add(1);
		intSet.add(3);
		intSet.add(5);
		intSet.add(5);
		intSet.add(3);
		intSet.add(3);
		intSet.add(3);
		// Int set iterator test
		System.out.println("INT SET ITERATOR TEST");
		Iterator<Integer> it = intSet.iterator();
		System.out.println(it.next());
		System.out.println(it.next());
		System.out.println(it.next());
		
		// Int set array test
		System.out.println("\nINT SET ARRAY TEST");
		Object[] intArray = intSet.toArray();
		for(Object obj : intArray) {
			System.out.println(obj);
		}
		
		// Remove 1 then test
		intSet.remove(1);
		System.out.println("\nINT SET ARRAY TEST AFTER REMOVING 1");
		Object[] intArray2 = intSet.toArray();
		for(Object obj : intArray2) {
			System.out.println(obj);
		}
		// Re-add 1
		intSet.add(1);
		
		// Test retainAll
		System.out.println("\nTESTING RETAINALL WITH 3 AND 5");
		List<Integer> list = new ArrayList<Integer>();
		list.add(3);
		list.add(5);
		intSet.retainAll(list);
		System.out.println(intSet);
		
		// Boolean checks
		System.out.println("\nContains 3?");
		System.out.println(intSet.contains(3));
		
		System.out.println("\nContains 8?");
		System.out.println(intSet.contains(8));
		
		System.out.println("\nContains 3 and 5?");
		System.out.println(intSet.containsAll(list));
		
		System.out.println("\nIs empty?");
		System.out.println(intSet.isEmpty());
		
		System.out.println("\nSize?");
		System.out.println(intSet.size());
		
		System.out.println("\nCLEAR AND PRINT");
		intSet.clear();
		System.out.println("-> " + intSet);
		
		
		System.out.println("");
		// Quick string test to see ordering is correct
		OccurrenceSet<String> stringSet = new OccurrenceSet<String>();
		stringSet.add("hello");
		stringSet.add("hello");
		stringSet.add("world");
		stringSet.add("world");
		stringSet.add("world");
		stringSet.add("here");
		
		Object[] strArray = stringSet.toArray();
		for(Object obj : strArray) {
			System.out.println(obj);
		}
		
		System.out.println(stringSet);
	}
	
}
