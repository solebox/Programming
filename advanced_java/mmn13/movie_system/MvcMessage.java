import java.util.ArrayList;

/**
 * this is the message that is passed from the observable model to the observer view 
 * it holds current seat order data
 * @author solekiller
 *
 */
public class MvcMessage {
	private ArrayList<Seat> _mySeats;
	private double _subTotal;
	/**
	 * the method that is used by the model to input the current order status (using logical seat representation)
	 * @param mySeats - the list of the seats
	 */
	public void setSeats(ArrayList<Seat> mySeats){ //for model 
		_mySeats = new ArrayList<Seat>(mySeats);
	}
	/**
	 * the view uses this method to get the current list when it recives the object in the update method
	 * @return
	 */
	public ArrayList<Seat> getSeats(){
		return _mySeats; // cloning it again would be redundant 
	}
	/**
	 * method that sets the subtotal field to give the client the price he has to pay
	 * @param subTotal
	 */
	public void setSubTotal(double subTotal){
		_subTotal = subTotal;
	}
	/**
	 * a method that the view uses to get the subtotal to present it to the client when it shows him the reciept 
	 * @return the total amount to pay at a given order state
	 */
	public double getSubtotal(){
		return _subTotal;
	}
}
