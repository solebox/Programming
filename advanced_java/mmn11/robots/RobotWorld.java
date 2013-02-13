package robots;

public class RobotWorld {
	private Robot[][] _world;
	private int _size;
	private PointList _robot_locations;
	
	public RobotWorld(int size){
		_size = size;
		_robot_locations = new PointList(size);
		if (size <= 0)
			throw new Error("invalid robot world size");
		_world = new Robot[size][size];
	}
	public boolean addRobot(Robot r, Point p){
		float x,y;
		int world_size;
		x = p.getX();
		y = p.getY();
		world_size = _world.length;
		if (x < 0 || y < 0 || x >= world_size || y >= world_size)
			return false;
		//robot insertion logic goes here
		if ( _robot_locations.isPointInList(p) || _robot_locations.isFull() || getPosition(r) != null) //added isPointInList check for real world performance (i know its still O(n^2)) 
			return false;
		_robot_locations.addPoint(p);
		_world[p.getX()][p.getY()] = r;
		//robot insertion logic
		return true; 
	}
	public Point getPosition(Robot r){
		Robot tmp_r;
		Point[] current_locations = _robot_locations.getPoints();
		for (Point p: current_locations){
			tmp_r = _world[p.getX()][p.getY()];
			if (tmp_r != null){
				if (tmp_r.getID() == r.getID())
					return new Point(p);
			}
		}
		return null;
	}
	public Robot getRobot(Point p){
		if (p.getX() > 0 && p.getX() < _size && p.getY() > 0 && p.getY() < _size  )
			if (_robot_locations.isPointInList(p)) //could have just returned the cell since a cell without a robot is already a null (java initialised it), but im not a ninja just yet :)
				return _world[p.getX()][p.getY()];
		return null;
	}
	public boolean removeRobot(Robot r){
		Point p = getPosition(r);
		if (p != null){
			_world[p.getX()][p.getY()] = null;
			_robot_locations.removePoint(p);
			return true;
		}
		return false;
	}
	public boolean moveRobot(Robot r){
		Point p = getPosition(r);
		int x;
		int y;
		if (p == null)
			return false;
		x = p.getX();
		y = p.getY();
		switch (r.getDirection()) {
		case UP:
			y--;
			break;
		case RIGHT:
			x++;
			break;
		case DOWN:
			y++;
			break;
		case LEFT:
			x--;
			break;
		default:
			break;
		}
		if (x < 0 || y <0 || x >= _size || y >= _size || squareBuisy(x,y))
			return false;
		_world[x][y] = r;
		_world[p.getX()][p.getY()] = null;
		_robot_locations.removePoint(p);
		_robot_locations.addPoint(new Point(x,y));
		assert(_world[x][y] != null);
		return true;
	}
	public String toString(){
		String str = "";
		for ( int y	= 0; y < _size ; y++){
			for (int x = 0; x < _size; x++){
				if (_world[x][y] != null )
					str += _world[x][y];
				else
					str += "_ ";
			}
			str+="\n";
		}
		return str;
	}
	private boolean squareBuisy(int x,int y){
		if (_robot_locations.isPointInList(x, y))
			return true;
		return false;
	}
}
