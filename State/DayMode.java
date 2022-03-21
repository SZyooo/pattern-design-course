public class DayMode extends PhoneMode
{
	public DayMode()
	{
		_name = "Day Mode";
	}
	public void show(Phone phone)
	{
		System.out.println(phone.Name() + "current mode is Day mode");
	}
}