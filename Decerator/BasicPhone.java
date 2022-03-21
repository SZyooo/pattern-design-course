public class BasicPhone implements Phone
{
	public void showCover(){
		System.out.println("no cover");
	}
	public static void main(String[] args)
	{
		Phone phone = new BasicPhone();
		phone.showCover();
		Phone redPhone = new RedCover(phone);
		redPhone.showCover();
		Phone pinkRedphone = new PinkCover(redPhone);
		pinkRedphone.showCover();
	}
}