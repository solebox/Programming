import java.util.Random;

/**
 * this is where all the game logic is
 * @author solekiller
 *
 */
public class GameModel {
	public final int EMPTY_VALUE = 0;
	private int[][] _matrix;
	private int[][] _startMatrix;
	private Point _emptyCellLocation;
	private Random rand = new Random();
	
	public GameModel(){
		_matrix = new int[][] {{1,2,3,4},
				   {5,6,7,8},
				   {9,10,11,12},
				   {13,14,15,EMPTY_VALUE}};
		_startMatrix = new int[][] {{1,2,3,4},
				   {5,6,7,8},
				   {9,10,11,12},
				   {13,14,15,EMPTY_VALUE}};
		_emptyCellLocation = new Point(_matrix.length-1,_matrix.length-1);
	}

	/**
	 * thus method restarts the game
	 */
	public void resetGame(){
		int [][] mat = {{1,2,3,4},
				   {5,6,7,8},
				   {9,10,11,12},
				   {13,14,15,EMPTY_VALUE}};
		_matrix = mat;
		_emptyCellLocation = new Point(_matrix.length -1 , _matrix.length -1);
		shuffleGame();
	}
	
	/**
	 * this method returns the board size
	 * @return board size
	 */
	public int getBoardSize(){
		return _matrix.length;
	}
	/**
	 * this method checks if a piece can be moved if that is true it moved it
	 * @param pieceLocation - the location of the piece i am trying to move
	 * @return - Point with coordinates of the destination to which the piece has moved
	 */
	public Point move(Point pieceLocation){
		Point destination = new Point(_emptyCellLocation);
		if (!inMatrix(pieceLocation))
			return null; //piece you want to move is not in matrix
		int row,column,emptyRow, emptyCol;
		row = pieceLocation.getY();
		column = pieceLocation.getX();
		emptyRow = _emptyCellLocation.getY();
		emptyCol = _emptyCellLocation.getX();
		if (nearEmpty(pieceLocation)){
			_matrix[emptyRow][emptyCol] = _matrix[row][column];
			_matrix[row][column] = EMPTY_VALUE;
			_emptyCellLocation = pieceLocation;
			return destination;
		}else{
			return null;
		}
	}
	/**
	 * checks if piece tested is near pieceLocation and returns true or false accordingly 
	 * @param pieceLocation - the location of the piece that is looking for tested
	 * @param tested - the location of the piece that is checked for proximity to the piece above
	 * @return true if tested is near pieceLocation false if not
	 */
	private boolean nearMe(Point pieceLocation, Point tested){
		if (!inMatrix(pieceLocation) || !inMatrix(tested))//pieces you want to move are not in matrix
			return false;
		int row,column,testedRow,testedCol;
		row = pieceLocation.getY();
		column = pieceLocation.getX();
		testedRow = tested.getY();
		testedCol = tested.getX();
		if ( row == testedRow )
			return (column == (testedCol + 1) || column == (testedCol - 1));
		if ( column == testedCol)
			return (row == (testedRow + 1) || row == (testedRow -1) );
		return false;
	}
	/**
	 * checks if the piece that has the location pieceLocation is near the empty cell
	 * @param pieceLocation - the location of the piece in question
	 * @return true if near empty false if not
	 */
	private boolean nearEmpty(Point pieceLocation){
			return nearMe(_emptyCellLocation, pieceLocation);
	}
	/**
	 * checks if a given piece is inside the game matrix
	 * @param loc the piece location
	 * @return true if in matrix false if outside the matrix (why didn't i take the blue pill)
	 */
	private boolean inMatrix(Point loc){
		return inMatrix(loc.getY(),loc.getX());
	}
	/**
	 * checks if a point is in the matrix by x and y parameters
	 * @param x - the x coordinate to check
	 * @param y - the y coordinate to check
	 * @return - true if in matrix false if outside (now i understand what my X meant when she said i was the one)
	 */
	private boolean inMatrix(int x, int y){
		boolean inMat = true;
		if (x < 0 || y < 0)
			inMat = false;
		if (x >= _matrix.length || y >= _matrix.length)
			inMat = false;
		return inMat;
	}
	/**
	 * randomly returns 1 or 0
	 * @return 1 or 0 
	 */
	private int binRandom(){
		return rand.nextInt(1000)%2;
	}
	/**
	 * returns amount of steps to take when shuffeling range: 3 to 1003;
	 * @return
	 */
	private int shuffleStepAmount(){
		return rand.nextInt(1000)+3;
	}
	/**
	 * does one random step each time its called (mutates one step at a time?! wtf is this a turtle? i wonder if it likes pizza..)
	 */
	private void mutate(){
		int verticalMove = binRandom();
		if (verticalMove == 1){
			verticalMove();
		}else{
			horizontalMove();
		}
	}
	/**
	 * as the name implies this method does a horizontal move (the direction is chosen randomly)
	 */
	private void horizontalMove() {
		int sideChoice = binRandom();
		int x,y;
		Point piece = new Point(_emptyCellLocation);
		x = piece.getX();
		y = piece.getY();
		if (sideChoice == 1){
			if (inMatrix(x + 1, y)){
				piece.setX(x + 1);
			}else{
				piece.setX(x - 1);
			}
		}else{
			if (inMatrix(x - 1, y)){
				piece.setY(x - 1);
			}else{
				piece.setY(x + 1);
			}
		}
		move(piece);
	}
	/**
	 * as the name implies this method does a vertical move (the direction is chosen randomly)
	 */
	private void verticalMove() {
		int sideChoice = binRandom();
		int x,y;
		Point piece = new Point(_emptyCellLocation);
		x = piece.getX();
		y = piece.getY();
		if (sideChoice == 1){
			if (inMatrix(x, y + 1)){
				piece.setY(y + 1);
			}else{
				piece.setY(y - 1);
			}
		}else{
			if (inMatrix(x, y - 1)){
				piece.setY(y - 1);
			}else{
				piece.setY(y + 1);
			}
		}
		move(piece);
	}
	/**
	 * this method does the shuffle by calling mutate 3-1003 times (depends on shuffleStepAmount's return)
	 */
	public void shuffleGame(){
		int times = shuffleStepAmount();
		for (int i = 0; i < times; i++) {
			mutate();
		}
	}
	/**
	 * pass this method a location and you will get back the value in that exact location
	 * @param location - a Point object representing the location of the piece in question
	 * @return the value
	 * @throws IllegalLocation 
	 */
	public int getValueInLocation(Point location) throws IllegalLocation{
		try{
			return _matrix[location.getY()][location.getX()];
		}
		catch (ArrayIndexOutOfBoundsException e){
			throw new IllegalLocation();
		}
	}
	/**
	 * gets the cells location
	 * @return Point object that represents its location
	 */
	public Point getEmptyCellPosition() {
		return new Point(_emptyCellLocation);
	}
	/**
	 * a method that checks if the game is solved
	 * true if solved false if not
	 * @return boolean answer to the question: is the game solved?
	 */
	public boolean isSolved(){
		boolean solved = true;
		for (int i = 0; i < _matrix.length; i++) {
			for (int j = 0; j < _matrix.length; j++) {
				if (_matrix[i][j] != _startMatrix[i][j])
					solved = false;
			}
		}
		return solved;
	}
}
