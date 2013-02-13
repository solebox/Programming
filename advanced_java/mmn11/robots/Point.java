package robots;

public class Point {
	private int _x,_y;

	public Point(){
		this(0,0);
	}
	public Point(int x, int y){
		_x = x;
		_y = y;
	}
	public Point(Point p){
		this(p._x,p._y);

	}
	public void setX(int x){
		_x = x;
	}
	public int getX(){
		return _x;
	}
	public void setY(int y){
		_y = y;
	}
	public int getY(){
		return _y;
	}

	public String toString(){
		return _x+", "+_y;
	}

}