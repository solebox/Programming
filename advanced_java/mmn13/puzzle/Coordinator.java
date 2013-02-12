import java.awt.event.ActionListener;
/**
 *  any controller must implement this interface in order to work with our view
 * @author solekiller
 *
 */
public interface Coordinator {
	/**
	 * a method needed to reset the game
	 */
	public abstract void resetGame();
	/**
	 * a method to move a piece in the game
	 * @param piece - a piece to move in the game
	 */
	public abstract void move(Point piece);
	/**
	 * checks if there is another ButtonData Object to retrive using the iterator (holds the value of the button and the handler)
	 * @return true if there is another false if there isnt
	 */
	public abstract boolean hasNext();
	/**
	 * gets the next ButtonData object
	 * @return Button data used to initialize the button in the board
	 */
	public abstract ButtonData getNext() throws TryingToGetAlthoughDoesntHaveNext;
	/**
	 * gets the reset button's Action listener 
	 * @return the reset button action listener
	 */
	public abstract ActionListener getResetButtonListener();
	/**
	 * gets the board size
	 * @return - the board's size
	 */
	public int getBoardSize();
}

