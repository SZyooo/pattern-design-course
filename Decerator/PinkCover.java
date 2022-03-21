public class PinkCover extends Cover
{
	public PinkCover(Phone phone){
		super(phone);
	}
	public void showCover(){
		System.out.println("-----------------------------");
		_phone.showCover();
		System.out.println("wrap with a Pink cover");
		System.out.println("-----------------------------");
	}
	
}