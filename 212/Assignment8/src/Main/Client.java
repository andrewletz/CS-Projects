package Main;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.InetAddress;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Scanner;

/*
 * Used client class from https://classes.cs.uoregon.edu/17S/cis212/examples.htm
 */

public class Client {
	private static final int PORT = 1337;

	public static void main(String[] args) {
		ArrayList<Integer> intList = getIntList();
		
		Socket socket = null;
		ObjectOutputStream outputStream = null;
		ObjectInputStream inputStream = null;		
		try {
			InetAddress address = InetAddress.getLocalHost();
			socket = new Socket(address, PORT);

			// Write all integers received from user to the server
			outputStream = new ObjectOutputStream(socket.getOutputStream());
			outputStream.flush();
			for (int i : intList) {
				outputStream.writeInt(i);
				outputStream.flush();
			}
			outputStream.writeInt(-999); // Sentinel value
			outputStream.flush();
			
			// Receive all integers that are prime back from the server
			inputStream = new ObjectInputStream(socket.getInputStream());
			ArrayList<Integer> receivedList = new ArrayList<Integer>();
			int message;
			do {
				message = inputStream.readInt();
				if(message != -999) {
					receivedList.add(message);
				}
			} while (message != -999);		
			
			
			// Print sent and received
			System.out.println("\nIntegers sent to the server:");
			for(int i : intList) {
				System.out.print(i + " ");
			}
			
			System.out.println("\nIntegers received from the server:");
			for(int i : receivedList) {
				System.out.print(i + " ");
			}
		} catch (IOException ex) {
			ex.printStackTrace();
		} finally {
			try {
				if (socket != null) {
					socket.close();
				}
				if (outputStream != null) {
					outputStream.close();
				}
				if (inputStream != null) {
					inputStream.close();
				}
			} catch (IOException ex) {
				ex.printStackTrace();
			}
		}
	}
	
	private static ArrayList<Integer> getIntList() {
		ArrayList<Integer> intList = new ArrayList<Integer>();
		Scanner sc = new Scanner(System.in);
		
		System.out.println("Enter an integer (\"!\" to send)");
		boolean running = true;
		while (running) {
			String nextInput = sc.next();
			switch (nextInput) {
			case "!":
				running = false;
				sc.close();
				break;
			default:
				intList.add(Integer.parseInt(nextInput));
				System.out.println("Enter an integer (\"!\" to send)");
				break;
			}
		}
		
		return intList;
	}
}