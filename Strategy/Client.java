
import java.time.format.DateTimeFormatter;
import java.time.LocalDateTime;  
import java.util.Scanner;



public class Client{
	public static void main(String args[])
	{
		Client client = new Client();
		System.out.println("choose the way to pay your bill:");
		System.out.println("1:bank card");
		System.out.println("2:Apple Pay");
		Scanner reader = new Scanner(System.in);
		String method = reader.nextLine();
		if(method.equals(new String("1")))
			client._pay = new Bankcard();
		else if(method.equals(new String("2")))
			client._pay = new ApplePay();
		else
			System.out.println("plz input a valid code. no " + method);
		DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy/MM/dd HH:mm:ss");  
		LocalDateTime now = LocalDateTime.now();
		Bill bill = new Bill("Bill:" + dtf.format(now));
		client._pay.pay(bill);
	}
	private Pay _pay;
}