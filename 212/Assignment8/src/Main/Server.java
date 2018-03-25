package Main;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

/*
 * Used server class from https://classes.cs.uoregon.edu/17S/cis212/examples.htm
 */

public class Server {
	private static final int PORT = 1337;
	
	public static void main(String[] args) {	
		System.out.println("Running server on port " + PORT);
		
		ServerSocket serverSocket = null;
		Socket socket = null;
		ObjectOutputStream outputStream = null;
		ObjectInputStream inputStream = null;		
		try {
			serverSocket = new ServerSocket(PORT);
			socket = serverSocket.accept();
			
			outputStream = new ObjectOutputStream(socket.getOutputStream());
			outputStream.flush();
			
			inputStream = new ObjectInputStream(socket.getInputStream());
			
			// Get all values from the client
			ArrayList<Integer> intList = new ArrayList<Integer>();
			int message;
			do {
				message = inputStream.readInt();
				if(message != -999 && isPrime(message)) {
					intList.add(message);
				}
			} while (message != -999);
			
			
			// Write all primes back to client
			for (int i : intList) {
				outputStream.writeInt(i);
				outputStream.flush();
			}
			outputStream.writeInt(-999); // Write sentinel value to terminate the client's loop
			outputStream.flush();
		} catch (IOException ex) {
			ex.printStackTrace();
		} finally {
			try {
				if (serverSocket != null) {
					serverSocket.close();
				}
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
		
		System.out.println("Server closed");
	}
	
	/*
	 * https://stackoverflow.com/questions/20798391/java-isprime-function
	 * ^- credit to Tareq Salaheldeen for this isPrime function
	 */
	private static boolean isPrime(int num) {
        if (num < 2) { 
        	return false;
        }
        if (num == 2) {
        	return true;
        }
        if (num % 2 == 0) {
        	return false;
        }
        for (int i = 3; i * i <= num; i += 2) {
            if (num % i == 0) {
            	return false;
            }
        }
        return true;
	}
	
}