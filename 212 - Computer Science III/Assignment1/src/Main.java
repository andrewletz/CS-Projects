import java.util.Scanner;


public class Main { 
	
	private static String defMsg = "Enter a positive integer (-3 to print, -2 to reset, -1 to quit):";
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		boolean running = true;
		int sum = 0;

		while (running) {
			System.out.println(defMsg);

			int i = sc.nextInt();

			switch (i) {
			case -1:
				System.out.println("Final S-um: " + sum);
				sc.close();
				running = false;
				break;
			case -2:
				sum = 0;
				break;
			case -3:
				System.out.println("Sum: " + sum);
				break;
			default:
				sum = sum + i;
			}
		}

	}

}
