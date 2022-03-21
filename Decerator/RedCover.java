public class RedCover extends Cover
{
	public RedCover(Phone phone){
		super(phone);
	}
	public void showCover(){
		System.out.println("-----------------------------");
		_phone.showCover();
		System.out.println("wrap with a red cover");
		System.out.println("-----------------------------");
	}
}