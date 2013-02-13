import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Random;

import javax.swing.JOptionPane;

public class Game {
	private final int NUMSIZE = 4;
	private ArrayList<Integer> _digitBank;
	private ArrayList<Integer> _bools;
	private ArrayList<Integer> _almost;
	private Integer _boolAmount = 0;
	private Integer _almostAmount = 0;
	private String _currentUserInput;
	private ArrayList<Integer> _current_guess;
	private boolean _won;
	public Game(){
		_current_guess = null;
		_digitBank = new ArrayList<Integer>();
		_almost = new ArrayList<Integer>();
		_bools = new ArrayList<Integer>();
		_won = false;
		
		Collections.addAll(_digitBank,0,1,2,3,4,5,6,7,8,9);
		Collections.addAll(_bools,-1,-1,-1,-1);
	}
	public boolean getUserString(String userString){
		if(userString.toLowerCase().matches("[xhb]{4}")){
			_currentUserInput = new String(userString);
			if (_currentUserInput.toLowerCase().equals("bbbb"))
				_won = true;
			return true;
		}else{
			return false;
		}
	}
	public ArrayList<Integer> getNextGuess(){
		if (_current_guess == null){
			_current_guess = firstGuess();
		}else{
			_current_guess = nextGuess(_currentUserInput, _current_guess);
		}
		return new ArrayList<Integer>(_current_guess);
	}
	public boolean hasWon(){
		return _won;
	}
	private ArrayList<Integer> firstGuess(){
		ArrayList<Integer> guess = new ArrayList<Integer>();
		for (int i = 0; i < NUMSIZE;i++){
			guess.add(_digitBank.get(i));
		}
		return guess;
	}
	private ArrayList<Integer> nextGuess(String userString,ArrayList<Integer> lastGuess){
		ArrayList<Integer> guess = new ArrayList<Integer>();
		Collections.addAll(guess, -2,-2,-2,-2);
		char[] usrSrt = userString.toLowerCase().toCharArray();
		if (collectedEnoughDigits())
			guess = generateGuessFromCollected();
		else{
			for (int i = 0; i < NUMSIZE; i++){
				Integer digit = lastGuess.get(i);
				switch (usrSrt[i]) {
				case 'x':
					_digitBank.remove(digit);
					break;
				case 'b':
					if ( !_bools.contains(digit) ){
						_boolAmount++;
						_bools.set(i, digit);
						_digitBank.remove(digit);
					}
					break;
				case 'h':
					if (!_almost.contains(digit)){
						_almostAmount++;
						_almost.add(digit);
						_digitBank.remove(digit);	
					}
					break;
				default:
					System.out.println("bad user string got into nextGuess Method"); //fixme
					break;
				}
			}
			if (collectedEnoughDigits()){
				guess = generateGuessFromCollected();
			}else{
				guess = generateGuessFromCollectedAndDigitBank();
			}
		}
		assert !guess.contains(-1) : "guess from nextGuess contains -1s";
		assert !guess.contains(-2) : "guess from nextGuess wasnt assigned anywhere";
		return guess;
	}
	
	private void rotate(ArrayList<Integer> list){
		Integer tmp = list.get(0); //fixme
		Collections.rotate(list, 1);
		assert tmp != list.get(0) : "list not rotated";
	}
	private boolean collectedEnoughDigits(){
		return (_boolAmount + _almostAmount) == NUMSIZE; // replace magic number
	}
	private ArrayList<Integer> generateGuessFromCollected(){
		ArrayList<Integer> tempBools = new ArrayList<Integer>(_bools);
		ArrayList<Integer> tempAlmost = new ArrayList<Integer>(_almost);
		if (!tempBools.contains(-1))
			return tempBools;
		for (int i = 0; i < tempBools.size(); i++){
			if (tempBools.get(i) == -1)
				tempBools.set(i, popList(tempAlmost)); 
		}
		rotate(_almost);
		assert !(tempBools.contains(-1)) : "tempBools in generateGuessFromCollected contains -1s" ; //fixme
		return tempBools;
	}
	private ArrayList<Integer> generateGuessFromCollectedAndDigitBank(){
		ArrayList<Integer> tempBools = new ArrayList<Integer>(_bools);
		ArrayList<Integer> tempAlmost = new ArrayList<Integer>(_almost);
		ArrayList<Integer> tempBank = new ArrayList<Integer>(_digitBank);
		for (int i=0; i < tempBools.size();i++){
			if (tempBools.get(i) == -1){
				if (tempAlmost.size() != 0)
					tempBools.set(i, popList(tempAlmost));
				else
					tempBools.set(i, popList(tempBank)); //could pop original but that would make my code less readable imo
			}
		}
		assert !tempBools.contains(-1) : "tempBools contains -1s";
		return tempBools;
	}
	private Integer popList(ArrayList<Integer> list){
		Integer temp = -1;
		int size = list.size();
		temp = list.get(size -1);
		list.remove(temp); // well at least it makes my code more amusing
		assert (temp != -1) && (size == (list.size()+1)): "tail wasn't successfully removed";
		return temp; 
	}
	private void fillRemainingCells(ArrayList<Integer> list){ //might be deprecated
		ArrayList<Integer> tempAlmost = new ArrayList<Integer>(_almost);
		for (int i = 0; i < list.size(); i++){
			if (list.get(i) == -1)
				list.set(i, popList(tempAlmost));
		}
	}

}
