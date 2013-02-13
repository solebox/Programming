package robots;

public class PointList {
	private Point[] _points;
	private int _top;
	
	public PointList(Point[] points){
		_points = new Point [points.length];
		for (int i=0; i < points.length;i++){
			_points[i] = new Point(points[i]);
		}
	}
	public PointList(int size){
		_points = new Point[size];
		_top = 0;
	}
	
	
	public boolean addPoint(Point p){
		if (_top == _points.length)
			return false;
		_points[_top] = new Point(p);
		_top++;
		return true;
	}

	public boolean removePoint(Point p){
		return removePoint(p.getX(), p.getY());
	}
	public boolean removePoint(int x, int y){
		for (int i = 0; i < _top; i++){
			if (_points[i] != null && _points[i].getX() == x && _points[i].getY() == y){
					_points[i] = _points[_top-1];
					_top--;
				return true;
			}
		}
		return false;
	}
	public boolean isPointInList(Point p){
		return isPointInList(p.getX(),p.getY());
	}
	public boolean isPointInList(int x, int y){
		for (int i=0; i<_top ; i++){
			if (_points[i].getX() == x && _points[i].getY() == y)
				return true;
		}
		return false;
	}
	public boolean isFull(){
		if (_top == _points.length)
			return true;
		return false;
	}
	public Point[] getPoints(){
		Point[] points = new Point[_top];
		for (int i = 0; i < _top;i++){
			points[i] = new Point(_points[i]);
		}
		return points;
	}
}
