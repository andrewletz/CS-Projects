package Main;

public class Entry {

	private String firstName;
	private String lastName;
	private int phoneNumber;
	
	public Entry(String firstName, String lastName, int phoneNumber) {
		this.firstName = firstName;
		this.lastName = lastName;
		this.phoneNumber = phoneNumber;
	}
	
	public String toString() {
		return (phoneNumber + " " + firstName + ", " + lastName);
	}
	
	public String toFancyString() {
		return ("#: " + phoneNumber + " | " + firstName + " | " + lastName);
	}
	
	public String getFirst() {
		return this.firstName;
	}
	
	public String getLast() {
		return this.lastName;
	}
	
	public int getPhoneNumber() {
		return this.phoneNumber;
	}
	
	/*
	 * Deep copy/clone of this entry object
	 */
	public Entry clone() {
		Entry clone = new Entry(this.firstName, this.lastName, this.phoneNumber);
		return clone;
	}
}
