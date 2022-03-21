public abstract class Cover implements Phone
{
	public Cover(Phone phone){
		_phone = phone;
	}
	protected Phone _phone;
}