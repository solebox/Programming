package AVL;

import java.util.Scanner;
/**
 * the user intreface class , from which to start the program 
 * it gets input from the user sends it to the proper methods in game
 * and outputs the result
 * @author solekiller
 *
 */
public class UserInterface {
	Game game;
	public UserInterface(){
		game = new Game();
	}
	public static void main(String args[]){
		UserInterface ui = new UserInterface();
		ui.read();
	}
	/**
	 * reads input from console
	 * and calls the private respond method
	 */
	public void read(){
		Scanner sc = new Scanner(System.in);
		String[] array;
		while ( !sc.hasNext("\\s*exit\\s*") && sc.hasNext() ){
			array = sc.nextLine().trim().split("\\s");
			respond(array);
		}
	}
	/**
	 * analyzes the input data and calls the proper method from the Game instance
	 * @param array - the array with the user input from stdin
	 */
	private void respond(String[] array){
		String cmd = array[0];
		if (cmd.equals("insert_player")){
			System.out.print("inserting player "+array[1]+"\n");
			game.insertPlayer(Integer.parseInt(array[1],10));
		}
		if (cmd.equals("get_player"))
			getPlayer(Integer.parseInt(array[1],10));
		if (cmd.equals("get_rank"))
			getRank(Integer.parseInt(array[1],10));
		if (cmd.equals("get_top"))
			getTop(Integer.parseInt(array[1],10));
		if (cmd.equals("insert_game")){
			System.out.print("inserting game: "+array[1]+" "+array[2]+"<>"+array[3]+" "+
					array[4]+"\n");
			game.insertGame(Integer.parseInt(array[1],10), array[2], Integer.parseInt(array[3],10),
					array[4]);
		}
	}
	/** calls get player , gets resulted array and outputs it in a fancy way 
	 * 
	 * @param id - the wanted player's id.
	 */
	private void getPlayer(int id){
		int[] arr = game.getPlayer(id);
		if (arr != null){
			int idnum = arr[0]; 
			int score = arr[1]; 
			int games = arr[2];
			System.out.print("\nPlayer id: "+idnum+", number of games: "+games+"," +
					" number of points:"+score+"\n");
		}else{
			System.out.print("\nPlayer "+id+" Does not exist.\n");
		}
	}
	/**gets the player id sends it to the getRank method in the game instance
	 * and sends the result to stdout
	 * @param id - the wanted player's id.
	 */
	private void getRank(int id){
		int rank = game.getRank(id);
		System.out.print("\nRank of Player "+id+" is "+rank+"\n");
	}
	/**
	 * gets the number of top players you want , sends it back to the method
	 * in game instance and post the return to the stdout
	 * @param y - how many top players you want
	 */
	private void getTop(int y){
		int[][] results = game.getTop(y);
		System.out.print("\nDisplaying "+y+" top-ranked players:\n");
		System.out.print(" Rank id points games\n");
		for (int i = 0; i < results.length; i++) {
			System.out.println((i+1)+" "+results[i][0]+" "+results[i][1]+" "+results[i][2]);
		}
		System.out.println();
	}
}
