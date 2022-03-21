//import Pay;

public class ApplePay implements Pay
{
	public void pay(Bill bill)
	{
		System.out.println(bill.Description() + "by ApplePay");
	}
}