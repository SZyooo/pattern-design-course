public class NightMode extends PhoneMode
{
	public NightMode()
	{
		_name = "Night Mode";
	}
	public void show(Phone phone)
	{
		System.out.println(phone.Name() + " current mode is night mode");
	}
}