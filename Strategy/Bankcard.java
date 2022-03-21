//import Pay;

public class Bankcard implements Pay
{
	public void pay(Bill bill)
	{
		System.out.println(bill.Description() + "by bankcard");
	}
} 