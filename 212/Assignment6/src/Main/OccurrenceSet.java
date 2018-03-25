package Main;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;

public class OccurrenceSet<T> implements Set<T>{

	private HashMap<T, Integer> map = new HashMap<T, Integer>();
	
	@Override
	public boolean add(T input) {
		if (map.containsKey(input)) {
			map.put(input, map.get(input) + 1);
		} else {
			map.put(input, 1);
		}
		return false;
	}

	@Override
	public boolean addAll(Collection<? extends T> input) {
		for (T obj : input) {
			add(obj);
		}
		return false;
	}

	@Override
	public boolean remove(Object input) {
		if (map.containsKey(input))
			map.remove(input);
		return false;
	}

	@Override
	public boolean removeAll(Collection<?> input) {
		for (Object obj : input) {
			remove(obj);
		}
		return false;
	}
	
	@Override
	public boolean retainAll(Collection<?> input) { 
		map.keySet().retainAll(input);
		return false;
	}

	@Override
	public boolean contains(Object input) {
		if (map.containsKey(input)) {
			return true;
		} else {
			return false;
		}
	}

	@Override
	public boolean containsAll(Collection<?> input) {
		for (Object obj : input) {
			if (!(map.containsKey(obj))) {
				return false;
			}
		}
		return true;
	}
	
	@Override
	public int size() {
		return map.size();
	}
	
	@Override
	public void clear() {
		map.clear();
	}
	
	@Override
	public boolean isEmpty() { 
		return map.isEmpty();
	}

	@Override
	public Iterator<T> iterator() {
		List<Map.Entry<T, Integer>> list = new LinkedList<Map.Entry<T, Integer>>(map.entrySet());
		Collections.sort(list, new Comparator<Map.Entry<T, Integer>>() {
			public int compare(Entry<T, Integer> o1, Entry<T, Integer> o2) {
				return o1.getValue().compareTo(o2.getValue());	// sup sean
			}
		});
		ArrayList<T> aList = new ArrayList<T>();
		for (Map.Entry<T, Integer> entry : list) {
			aList.add(entry.getKey());
		}
		return aList.iterator();
	}

	@Override
	public Object[] toArray() {
		Object[] a = new Object[map.size()];
		List<Map.Entry<T, Integer>> list = new LinkedList<Map.Entry<T, Integer>>(map.entrySet());
		Collections.sort(list, new Comparator<Map.Entry<T, Integer>>() {
			public int compare(Entry<T, Integer> o1, Entry<T, Integer> o2) {
				return o1.getValue().compareTo(o2.getValue());
			}
		});
		int counter = 0;
		for (Map.Entry<T, Integer> entry : list) {
			a[counter] = entry.getKey();
			counter++;
		}
		return a;
	}
	
	public String toString() {
		Object[] thisArray = this.toArray();
		String base = "";
		for (Object obj : thisArray) {
			base = base + obj.toString() + " ";
		}
		
		return base.trim();
	}

	// Who needs this implementation anyways
	@SuppressWarnings("hiding")
	@Override
	public <T> T[] toArray(T[] arg0) {
		// TODO Auto-generated method stub
		return null;
	}

}
