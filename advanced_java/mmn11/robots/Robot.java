package robots;

public class Robot {
	private int _id;
	public enum Direction { 
		UP("^"),
	    RIGHT(">"),
	    DOWN("v"),
   	    LEFT("<");	
		private String representation;
		Direction(String representation){ this.representation = representation; }
		public String getRepresentation(){ return representation; }
		public String toString(){ return this.representation;}
	}
	private Direction _direction;
	public void turnLeft(){
		turnRight();
		turnRight();
		turnRight();
	}
	public void turnRight(){
		switch (_direction) {
		case UP:
			_direction = Direction.RIGHT;
			break;
		case RIGHT:
			_direction = Direction.DOWN;
			break;
		case DOWN:
			_direction = Direction.LEFT;
			break;
		case LEFT:
			_direction = Direction.UP;
		break;
		default:
			System.out.println("wtf no direction init?");
			break;
		}
	}
	public Robot(int id, Direction dir){
		_id = id; // need to deal with the event of a problematic id
		_direction = dir;
	}
	public Robot(Robot r){
		this(r._id, r._direction);
	}
	public String toString(){
		return _id+", "+_direction;
	}
	public Direction getDirection(){
		return _direction;
	}
	public int getID(){
		return _id;
	}
	
}
