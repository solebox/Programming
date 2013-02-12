
import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.GridLayout;
//import java.awt.event.ActionListener;


import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;

import javax.swing.JPanel;
/**
 * this is the game's view
 * the gui
 * @author solekiller 
 *
 */

public class GameView extends JFrame {
	private static final long serialVersionUID = 1L;
	//	private GameModule _gameModule; // try not to make use of module in view if possible
	private JButton[][] _buttons;
	private int _boardSize;
	private int nextEmpty = 0;
	private static final String GAME_TITLE = "I would like to play a game."; // jig-saw puzzle :)
	private JPanel _gameBoard;
	/**
	 * the constructor it gets the controller and initializes the gui using the interface it required
	 * @param controller - the controller that called it
	 * @throws CantFitSoManyButtonsInCurrentBoardSize 
	 */
	public GameView(Coordinator controller) throws CantFitSoManyButtonsInCurrentBoardSize{
		super(GAME_TITLE);
		_boardSize = controller.getBoardSize();
	
		int width, height, gap;
		width = 300; height = 200; gap = 5;
		this.setLayout(new FlowLayout());
		this.setSize(width, height);
		_gameBoard = new JPanel(new GridLayout(_boardSize, _boardSize, gap, gap));
		_gameBoard.setSize(width, height);
		this.setSize(width+100, height);
		this.add(_gameBoard);
		_buttons = new JButton[ _boardSize][_boardSize];
		ButtonData bdata;
		while (controller.hasNext()){
			try{
				bdata = controller.getNext();
				insertButton(bdata); 
			}
			catch(TryingToGetAlthoughDoesntHaveNext e){
				System.err.println("Program encountered error number 109, please contact the developer at 3012@gmail.com\n meantime just restart the game.");
			}
			catch (Exception e) {
				throw new CantFitSoManyButtonsInCurrentBoardSize(); 
			}
		}
		JButton rematch = new JButton("rematch");
		rematch.addActionListener(controller.getResetButtonListener());
		this.add(new JPanel(new FlowLayout()).add(rematch));
		this.setVisible(true);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	/**
	 * inserts a button to the matrix
	 * @param data - the data needed by the view from the controller to initialize the button matrix (value and handler)
	 */
	private void insertButton(ButtonData data){
			int row,col;
			if (nextEmpty == _boardSize*_boardSize)
				throw new ArrayIndexOutOfBoundsException();
			row = nextEmpty/_boardSize;
			col = nextEmpty%_boardSize;
			if (data.getValue() != 0)
				_buttons[row][col] = new JButton(""+data.getValue());
			else
				_buttons[row][col] = new JButton("");
			
			
	        _buttons[row][col].addActionListener( data.getListener() ); // register listener
	        _buttons[row][col].setName(""+data.getValue());
	        _buttons[row][col].setFont(new Font("Serif", Font.BOLD, 22));
	        _buttons[row][col].setForeground(Color.BLACK);
	        _gameBoard.add( _buttons[row][col] );
	        nextEmpty++;
	} 
	/**
	 * swaps the text values of the 2 given buttons in the given locations
	 * @param aLoc - the first button to swap
	 * @param bLoc - the second button to swap
	 */
	public void swapButtonText(Point aLoc, Point bLoc){
		String textA,textB;
		JButton a,b;
		b = _buttons[bLoc.getY()][bLoc.getX()];
		a = _buttons[aLoc.getY()][aLoc.getX()];
		textA = a.getText();
		textB = b.getText();
		a.setText(textB);
		b.setText(textA);
	}
	/**
	 * the message sent to the user once it prevails 
	 */
	public void victoryMessage(){
		try{
			JOptionPane.showMessageDialog(this, "You are Victorious!");
		}catch(Exception ex){
			System.err.println("error msg failed to pop");
		}
	}
	public void errorMSG(String msg){
		try{
			JOptionPane.showMessageDialog(this, msg, "Error!", JOptionPane.ERROR_MESSAGE);
		}catch(Exception ex){
			System.err.println("error msg failed to pop");
		}
	}
	/**
	 * the message sent to the prevailing user that it insitant to keep on playing without clicking rematch
	 */
	public void alreadyWonMessage(){
		try{
			JOptionPane.showMessageDialog(this, "You already won, if you want a rematch please click the rematch button.");
		}catch(Exception ex){
			System.err.println("error msg failed to pop");
		}
	}
	public void resetGame(Coordinator controller) throws NotEnoughHandlers{
		ButtonData data = null;
		for (int row = 0; row < _buttons.length; row++) {
			for (int col = 0; col < _buttons.length; col++) {
					if (controller.hasNext()){
						try{
							data = controller.getNext();
						}catch(TryingToGetAlthoughDoesntHaveNext e){
							errorMSG("Program encountered error number 109, please contact the developer at 3012@gmail.com\n meantime just restart the game.");
						}
						if (data != null && data.getValue() != 0)
							_buttons[row][col].setText(""+data.getValue());
						else
							_buttons[row][col].setText("");
					}else{
						throw new NotEnoughHandlers();
					}
			}
		}
	}
	
	
}
