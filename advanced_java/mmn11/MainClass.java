import javax.swing.JOptionPane;

public class MainClass {
	public static void main(String args[]){
		GameIO gameio = new GameIO();
		
		String guess = gameio.getGuess();
		while (!gameio.hasWon()){
			if (gameio.getUserInput(guess)){
				if (!gameio.hasWon()){
					guess = gameio.getGuess();
				}else{
					boolean answeredYes = gameio.askForRematch();
					if (answeredYes){
						guess = gameio.getGuess();
					}
				}
			}else{
				gameio.badInputErrorMsg();//why did the mmn require me to manage the whole io in zee main , this looks so redundant :(
			}
		}
	}
}
