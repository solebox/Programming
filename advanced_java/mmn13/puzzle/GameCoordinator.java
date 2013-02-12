import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JOptionPane;

/**
 * this is the actuall controller for the game
 * here all the game coordination accures and all the data and commands are passed between the model and the view
 * @author solekiller
 *
 */
public class GameCoordinator implements Coordinator { //our controller
	private GameModel _model;
	private GameView _view;
	private ButtonListener[] _buttonListeners;
	private int _buttonListenersTop = 0;
	private int _size2D; //assumption made that height == width
	private int _emptyCellListenerIndex; 
	/**
	 * this is our constructor, it makes an instance of the games model then shuffles the board
	 * after that it gets the size of the logical board and creates ActionListeners to be passed to the game's view 
	 * later on, on view initialization.
	 */
	public GameCoordinator() {
		_model = new GameModel();
		_model.shuffleGame();
		int side = _model.getBoardSize();  
		_size2D = (side*side);
		_buttonListeners = new ButtonListener[_size2D];
		int row,col,value;
		for (int i = 0; i < _size2D; i++) {
			row = i/side;
			col = i%side;
			Point tmp = new Point(col,row); 
			try{
				value = _model.getValueInLocation(tmp);
				if (value == _model.EMPTY_VALUE)
					_emptyCellListenerIndex = i;
				_buttonListeners[i] = new ButtonListener(value,tmp);
			}catch(Exception e){
				try{
					JOptionPane.showConfirmDialog(null, "error accured while trying to initialize game please restart", "Error!", JOptionPane.ERROR_MESSAGE);
				}catch(Exception ex){
					System.err.println("error msg failed to pop");
				}
			}
		}
	}
	/**
	 * the view is initialized with the coordinator as a parameter , on initialization it will use the interface implemented to request
	 * the Action handlers (with the iterator required by the interface) and the board size
	 */
	public void startGame(){
		try {
			_view = new  GameView(this);
		}
		catch(CantFitSoManyButtonsInCurrentBoardSize e){
			System.err.print("trying to fit too many buttons in gui boardsize, check controller...");
		}
		catch(Exception e){
			System.err.print("gui couldn't be initialized");
		}
	}
	/**
	 * here the coordinator delegates the move action to the model
	 */
	public void move(Point piece){
		_model.move(piece);
	}
	/**
	 * here the coordinator delegates getBoardSize to the model
	 * and returns its return value
	 * @return - board's size
	 */
	public int getBoardSize(){
		return _model.getBoardSize();
	}
	/**
	 * this method resets the game
	 */
	@Override
	public void resetGame(){
		_model.resetGame();
		int side = _model.getBoardSize();  
		int row,col,value;
		for (int i = 0; i < _size2D; i++) {
			row = i/side;
			col = i%side;
			Point tmp = new Point(col,row); 
			try{
				value = _model.getValueInLocation(tmp);
				if (value == _model.EMPTY_VALUE)
					_emptyCellListenerIndex = i;
	
				_buttonListeners[i] = new ButtonListener(value,tmp);
			}catch(Exception e){
				_view.errorMSG("issue accured while trying to restart game please try again.");
			}
		}
		_buttonListenersTop = 0;
		try {
			_view.resetGame(this);
		}
		catch(Exception e){
			_view.errorMSG("an internal error has accured please try clicking rematch again,\n if you still encounter issues try to close and reopen the game");
		}
		
	}


	/**
	 * this method returns true if there is another event listener instance to return 
	 * else, returns false
	 * 
	 */
	@Override
	public boolean hasNext() {
		if (_buttonListenersTop < _buttonListeners.length)
			return true;
		return false;
	}
	/**
	 * this methods returns a listener wrapped in a ButtonData object 
	 *  that also holds the value of the button for initialization purposes (if need be can be changed to other values , i.e letters etc)
	 * @throws TryingToGetAlthoughDoesntHaveNext 
	 */
	@Override
	public ButtonData getNext() throws TryingToGetAlthoughDoesntHaveNext {
		if (_buttonListenersTop >= (_buttonListeners.length*_buttonListeners.length))
			throw new TryingToGetAlthoughDoesntHaveNext();
		ButtonData bdata = new ButtonData();
		bdata.setListener(_buttonListeners[_buttonListenersTop]);
		bdata.setValue(_buttonListeners[_buttonListenersTop].getValue());
		_buttonListenersTop++;
		return bdata;
	}
	/**
	 * this is the actual buttonListener class
	 *
	 *
	 */
	private class ButtonListener implements ActionListener {
		private int _buttonValue; 
		private Point _buttonLocation;
		/**
		 * constructor gets value and location of button and creates an action listener
		 * @param value - the value of the button (for initialization)
		 * @param location - the location in the matrix
		 */
		private ButtonListener(int value,Point location){
			_buttonValue = value; 
			_buttonLocation = new Point(location);
		}
		/**
		 * what happens when the button is clicked...
		 * if the game is solved it will raise the already won message , you dont need to click a button if you won.
		 * if the game is not solved and this step cause the win , the victory msg pops up
		 * if the game is not solved and the step did not cause a win a turn is made.
		 */
		@Override
		public void actionPerformed(ActionEvent e) {
			if (_model.isSolved()){
				_view.alreadyWonMessage();
			}else{
				Point destination = _model.move(_buttonLocation);
				if (destination != null){
					_view.swapButtonText(destination, _buttonLocation);
					swapListenerValues(); // need to maintain values for future use if needed :) (another view from current state maybe?)
				}else{
					Toolkit.getDefaultToolkit().beep(); //i dont have a pc speaker but this is supposed to work :) // beeps when you click a piece that cant be moved
				}
				if (_model.isSolved())
					_view.victoryMessage();
			}
		}
		/**
		 * gets the value of the button from the handler associated with it
		 * @return the button value
		 */
		private int getValue(){
			return _buttonValue;
		}
		/**
		 * sets the value to the value currently in the button associated with this handler
		 * @param value - value to set
		 */
		private void setValue(int value){
			_buttonValue = value;
		}
		/**
		 * swaps values between event listeners , done after a click is successfully swapping the displayed values and the logical ones
		 * for future initialization or if we want to attach another view in the middle of a game
		 */
		private void swapListenerValues(){
			int temp = _buttonListeners[_emptyCellListenerIndex].getValue();
			_buttonListeners[_emptyCellListenerIndex].setValue(this._buttonValue);
			this._buttonValue = temp;
		}
		
		
	}
	/**
	 * hands over the reset button action listener to the view when requested
	 * in initialization
	 */
	@Override
	public ActionListener getResetButtonListener() {
		return new ResetButtonListener();
	}
	/**
	 * the reset button action listener
	 *
	 */
	private class ResetButtonListener implements ActionListener{
		/**
		 * simply calls the reset game method
		 */
		@Override
		public void actionPerformed(ActionEvent arg0) {
			resetGame();
		}
		
	}
}
