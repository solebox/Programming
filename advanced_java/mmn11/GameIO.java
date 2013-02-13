import java.util.ArrayList;
import java.util.Scanner;

import javax.swing.JOptionPane;


public class GameIO {
	private Game _game;
	private ArrayList<Integer> _guess;
	private int _guess_amount;
	private Scanner scanIn;
	
	public GameIO(){
		_game = new Game();
		_guess_amount = 0;
		scanIn = new Scanner(System.in);
	}
	public String getGuess(){
		_guess = _game.getNextGuess();
		_guess_amount++;
		String stringGuess = "";
		for (Integer i: _guess){
			stringGuess = stringGuess + i;
		}
		return stringGuess;
	}
	public boolean getUserInput(){
		String userString = scanIn.nextLine();
		boolean goodInput = _game.getUserString(userString);
		return goodInput;
	}
	public boolean getUserInput(String guess){
		String input = JOptionPane.showInputDialog(null,guess,"my guess",JOptionPane.INFORMATION_MESSAGE);
		if (input == null) // treating cancel as bad input (would have done it differently but java doesn't supply means to remove that button
			return false;
		boolean goodInput = _game.getUserString(input);
		return goodInput;
	}
	public boolean hasWon(){
		return _game.hasWon();
	}
	public boolean askForRematch(){
		String input = JOptionPane.showInputDialog("It took me "+ guessAmount() +" guesses to win, rematch? (yes to continue, anything else to quit)");
		if (input != null && input.toLowerCase().matches("[y][e][s]")){
			restartGame();
			return true;
		}else{
			JOptionPane.showMessageDialog(null,"thank you for playing have a nice day","bye",JOptionPane.INFORMATION_MESSAGE);
			return false;
		}
	}
	private int guessAmount(){ //maybe some day there will be a different way of getting the guess amount
		return _guess_amount;
	}
	private void restartGame(){
		_game = new Game();
		_guess_amount = 0;
	}
	public void badInputErrorMsg(){
		JOptionPane.showMessageDialog(null,"bad input, please re-enter your answer","bad input",JOptionPane.OK_OPTION);
	}
}
