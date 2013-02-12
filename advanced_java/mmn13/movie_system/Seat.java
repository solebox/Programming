/**
 * this is a representation of a logical seat in a cinema (a seat booking representation) 
 * @author solekiller
 *
 */
public class Seat {
	private enum Status {TAKEN,NOT_TAKEN}
	private int _seatNumber, _row;
	private String _movie;//maybe
	private int _hourIndex;//maybe
	private Status _status;
	public int get_seatNumber() {
		return _seatNumber;
	}

/**
 * gets the name of the movie in which the logical seat exists
 * @return movie name
 */
	public String getMovieName() {
		return _movie;
	}
/**
 * gets the hour in which the seat is booked at this instance
 * @return the booking time
 */
	public int getHourIndex() {
		return _hourIndex;
	}
/**
 * gets the number of the actual seat that is booked
 * @return the number of the seat
 */
	public int getSeatNumber() {
		return _seatNumber;
	}
/**
 * returns the row in which the actual seat is located
 * @return the row in which the actual seat resides
 */
	public int getRow() {
		return _row;
	}

	/**
	 * a constructor , sets the status value to NOT_TAKEN 
	 */
	public Seat(){
		_status = Status.NOT_TAKEN;
	}
	/**
	 * an initializer that lets the system to add attributes for the booking seat representation
	 * @param row - the row in which the actual seat resides
	 * @param seatNum - the actual seats number
	 * @param movie - the booked seat movie
	 * @param hourIndex - the booked seat hour index
	 */
	public Seat(int row,int seatNum,String movie,int hourIndex){
		super();
		_seatNumber = seatNum;
		_row = row;
		_movie = movie;
		_hourIndex = hourIndex;
	}
	/**
	 * this method returns true if seat is taken false if not
	 * @return
	 */
	public boolean isTaken(){
		return _status == Status.TAKEN;
	}
	/**
	 * this method changes the state of the seat to taken (lets you order it)
	 */
	public void occupy() {
		this._status = Status.TAKEN;
	}
	/**
	 * this method frees the seat
	 */
	public void free(){
		this._status = Status.NOT_TAKEN;
	}
}
