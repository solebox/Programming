import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Observable;
import java.util.Scanner;

import javax.swing.JOptionPane;

/**
 * this is our movie ticketing system logic class the model
 * @author solekiller
 */
public class MovieSystemModel extends Observable {
	private ArrayList<String> _movieNames;
	private HashMap<String, Seat[][][]> _movieSeatsTable; //indices are :movieName => arr[hour][row][seat]
	public final Hour[] HOURS = {Hour.FOUR_PM,Hour.SEVEN_PM,Hour.TEN_PM} ;//using ints because i can assume there are only 3 options (and they are all round)
	private final double PRICE = 149.99; 
	private double _subTotal = 0.0;
	private int _rows,_seats;
	private ArrayList<Seat> _mySeats;
	private MvcMessage _msg;
 /**
  * this method initializes the movie system logic module, the model
  * @param rows the amount of rows in our movie theater 
  * @param seats the amount of seats in each row
  * i want to emphasize that the seats i am using are not a representation of the physical seats but the logical seats 
  * the seats that correspond to the ticket , i.e the same seat with the same number and row in a different hour would be regarded as a different seat 
  * since it will have different states at different times and different movie screenings...
  */
	public MovieSystemModel(int rows,int seats){
		_rows = rows; 
		_seats = seats;
		_movieNames = new ArrayList<String>();
		_mySeats = new ArrayList<Seat>();
		_movieSeatsTable = new HashMap<String, Seat[][][]>();
		_msg = new MvcMessage();
		if (getMovieNameList()){
			filleMovieSeatsTable(); //causes an exception
		}else{
			try{
				JOptionPane.showMessageDialog(null, "omg i couldnt get the movie name list!! call the developers!!!", "error", JOptionPane.ERROR_MESSAGE);
			}catch(Exception e){
				System.err.print("this is aquard, something went wrong: "+ e);
			}
		}
	}
	/**
	 * a method to occupy a logical seat
	 * @param movieName - the movie name in which the logical seat we want to occupy exists
	 * @param row - the row in which the seat exists
	 * @param seatNum - the seat's number
	 * @param screeningHour - the screening hour in which the logical seat exists 
	 * @return - if the seat was successfully occupied null is returned if not the logical seat instance is returned 
	 * @throws Exception
	 */
	public Seat occupySeat(String movieName,int row, int seatNum,Hour screeningHour) throws Exception{
		Seat[][][] seats;
		int hour = getHourIndex(screeningHour);
		if (hour == -1)
			throw new HourDoesntExist(); 
		if (_movieNames.contains(movieName)){
			seats = _movieSeatsTable.get(movieName);
			if (row < 0 || row > seats.length ||seatNum < 0 || seatNum > seats[0].length)
				throw new SeatDoesntExist();
			else{
				if (!seats[hour][row][seatNum].isTaken()){
					seats[hour][row][seatNum].occupy();
					_mySeats.add(seats[hour][row][seatNum]); //copies the reference 
					_subTotal = _subTotal + PRICE;
					updateMessageAndSendtoObservers();
					return null;
				}
			}
		}else{
			throw new NoSuchMovie();
		}
		return _movieSeatsTable.get(movieName)[hour][row][seatNum]; //seat is occupied already
	}
	/**
	 * a method to free an already taken seat by the client
	 * @param movieName the movie in which the logical seat to free resides
	 * @param seatToFree - the logical seat's number
	 * @param hhour - the hour in which the debuted screening the seat was ordered for is taking place
	 * @throws Exception
	 */
	public void freeSeat(String movieName, Seat seatToFree,Hour hhour) throws Exception{
		Seat[][][] seats;
		int hour = getHourIndex(hhour);
		if (_movieNames.contains(movieName)){
			seats = _movieSeatsTable.get(movieName);
			if (_mySeats.contains(seatToFree)){
				_mySeats.remove(seatToFree);
				_subTotal = _subTotal - PRICE;
				seats[hour][seatToFree.getRow()][seatToFree.getSeatNumber()].free();
				updateMessageAndSendtoObservers();
			}else{
				throw new NotYourSeat();
			}
		}else{
			throw new NoSuchMovie();
		}
	}
/**
 * a method to acquire the movies from which the client can choose
 * @return a string array filled with the possible movies to which the client can buy tickers 
 */
	public String[] getMovieNames(){
		return ((String[])_movieNames.toArray(new String[_movieNames.size()]));
	}
	/**
	 * and array of screening times to which the client can order seats
	 * @return - and array of possible screening hours  
	 */
	public Hour[] getScreeningTimes(){
		return HOURS;
	}
	/**
	 * returns the currently taken seats 
	 * @param movieName - movie in question 
	 * @param screeningHourIndex - screening time for the movie in question (different screenings different tickets)
	 * @return an array list filled with only the occupied seats 
	 */
	public ArrayList<Seat> getCurrentTheaterTakenSeats(String movieName,int screeningHourIndex){
		ArrayList<Seat> occupied = new ArrayList<Seat>();
		Seat tmp = null;
		for (int i = 0; i < _mySeats.size(); i++) {
			tmp = _mySeats.get(i);
			if (tmp.getMovieName() == movieName && tmp.getHourIndex() == screeningHourIndex)
				occupied.add(tmp);
		}
		return occupied;
	}
	// this method updates the message object and sends it to the observers (adds subtotal and current seat order)
	private void updateMessageAndSendtoObservers() {
		_msg.setSeats(_mySeats);
		_msg.setSubTotal(_subTotal);
		setChanged();
		notifyObservers(_msg);
	}
	// fills movie seat table
	private void filleMovieSeatsTable(){
		for (int i = 0; i < _movieNames.size(); i++) { 
			_movieSeatsTable.put(_movieNames.get(i),new Seat[HOURS.length][_rows][_seats]);
			for (int hour = 0; hour < HOURS.length ; hour++) {
				for (int row = 0; row < _rows; row++) {
					for (int seatNum = 0; seatNum < _seats; seatNum++) {
						_movieSeatsTable.get(_movieNames.get(i))[hour][row][seatNum] = new Seat(row, seatNum, _movieNames.get(i), hour);//alot of loops but the complexity is in fact O(N) 
					}																					
				}
			}
		}

	}
	// private method to get movie list (the logistics )
	private boolean getMovieNameList(){
		try{
			Scanner input = new Scanner(new File("src/data/movies.dat"));
			while (input.hasNextLine()) {
				String st = input.nextLine();
				_movieNames.add(new String(st));
			}
			input.close();
			return true;
		}
		catch(Exception e){
			System.out.println(e);
			return false;
		}

	}
	// gets a certain hour's index
	private int getHourIndex(Hour hour){
		for (int i = 0; i < HOURS.length; i++) {
			if (HOURS[i].getKey() == hour.getKey()) 
				return i;	
		}
		return -1;
	}


	
}
