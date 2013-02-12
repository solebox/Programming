
/**
 * a class that represents a Point in a 2d area
 * @author jacob
 *
 */
public class Point {
	private int _x,_y;
	/**
	 * an empty constructor
	 * creates a point with x and y set to 0
	 */
	public Point(){
		this(0,0);
	}
	/**
	 * this constructor creates a point with the given x and y coordinates
	 * @param x - the x coordinate
	 * @param y - the y coordinate 
	 */
	public Point(int x, int y){
		_x = x;
		_y = y;
	}
	/**
	 * this is a copy constructor
	 * it recives a point and makes a new one with the same coordinates
	 * @param p - the point we want to copy
	 */
	public Point(Point p){
		this(p._x,p._y);

	}
	/**
	 * a setter method for x
	 * @param x - the new value we want to give x
	 */
	public void setX(int x){
		_x = x;
	}
	/**
	 * a getter method for x
	 * @return - the x value out point holds
	 */
	public int getX(){
		return _x;
	}
	/**
	 * a setter method for y
	 * @param y - the value we want to set y to
	 */
	public void setY(int y){
		_y = y;
	}
	/**
	 * a getter method for y
	 * @return - the y value out point holds
	 */
	public int getY(){
		return _y;
	}
	/**
	 * returns the String representation of our point
	 */
	public String toString(){
		return _x+", "+_y;
	}

}