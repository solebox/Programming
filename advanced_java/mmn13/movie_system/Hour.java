/**
 * this is the screening time enumerator , made it just to practice the enum possibilities , i know there is Date and Time and so on..
 * @author solekiller
 *
 */
public enum Hour {
	//possible values :P 
		TWELVE_AM("00:00",0),
	  	ONE_AM("01:00",1),
	    TWO_AM("02:00",2),
	    THREE_AM("03:00",3),
	    FOUR_AM("04:00",4),
	    FIVE_AM("05:00",5),
	    SIX_AM("06:00",6),
	    SEVEN_AM("07:00",7),
	    EIGHT_AM("08:00",8),
	  	NINE_AM("09:00",9),
	  	TEN_AM("10:00",10),
	  	ELEVEN_AM("11:00",11),
	  	TWELVE_PM("12:00",12),
	  	ONE_PM("13:00",13),
	  	TWO_PM("14:00",14),
	  	THREE_PM("15:00",15),
		FOUR_PM("16:00",16),
		FIVE_PM("17:00",17),
		SIX_PM("18:00",18),
		SEVEN_PM("19:00",19),
		EIGHT_PM("20:00",20),
		NINE_PM("21:00",21),
		TEN_PM("22:00",22),
		ELEVEN_PM("23:00",23);
		

	    private final String _representation;   // in kilograms
	    private final int _key; // in meters
	    Hour(String representation, int ord) {
	        _representation = representation;
	        _key = ord;
	    }
	    /**
	     * get string representation of enum value
	     */
	    public String toString(){
	    	return _representation;
	    }
	    /**
	     * get the key of the enum value
	     * @return some uniq number that is the key of the enum // i know of ordinal(enum) but i wanted my own :D
	     */
	    public int getKey(){
	    	return _key;
	    }
	 
}
