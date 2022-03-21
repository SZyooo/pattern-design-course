import java.util.Scanner;
public class Phone
{
	public Phone(String name)
	{
		_name = name;
		_mode = new DayMode();
	}
	public Phone(String name, PhoneMode mode)
	{
		_name = name;
		_mode = mode;
	}
	public String Name(){
		return _name ;
	}
	public void switchMode(PhoneMode mode)
	{
		System.out.println("phone's mode is switched from " + _mode.Name() + " to " + mode.Name());
		_mode = mode;
	}
	public void show()
	{
		_mode.show(this);
	}
	private String _name;
	private PhoneMode _mode;
	public static void main(String[] args)
	{
		System.out.println("input your phone's name");
		Scanner reader = new Scanner(System.in);
		String name = reader.nextLine();
		Phone phone = new Phone(name);
		phone.switchMode(new NightMode());
		phone.show();
		phone.switchMode(new DayMode());
		phone.show();
		
	}
}