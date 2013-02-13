package robots;
import java.util.Random;

import javax.swing.JOptionPane;
public class ExampleProg {
	private static final int BOT_AMOUNT = 3;
	private static final int AMOUNT_OF_DIRECTIONS = Robot.Direction.values().length; //no magic numbers means no magic numbers :P
	private static final int ROBOT_ID_START = 10;
	private static int _world_size;
	private static Random _rand;
	private static Robot[] _robots;
	private static int MOVES = 6;
	private static RobotWorld _world;
	
	public static void popupWorldSizeDialog(String msg){
		String input = JOptionPane.showInputDialog("What is the size of the Robot World you'd like to create?");
		_world_size = Integer.parseInt(input);
		_world = new RobotWorld(_world_size);
		_robots = new Robot[_world_size];
	}
	public static void placeBots(){
		_rand = new Random();
		for (int i = 0; i < BOT_AMOUNT; i++){
			Robot r = createRandomDirectionBot(i+ROBOT_ID_START);
			Point p = createRandomPosition(_world_size);
			_world.addRobot(r, p);
			_robots[i] = r;
		}
	}
	public static void moveBots(){
		boolean hasMoved = false;
		for (int i = 0; i < BOT_AMOUNT; i++){
			for (int k = 0; k < MOVES; k++){
				hasMoved = _world.moveRobot(_robots[i]);
				if (!hasMoved)
					_robots[i].turnRight();
				hasMoved = false;
				System.out.println(_world);
			}
		}
	}
	private static Robot createRandomDirectionBot(int id){
		Robot r = new Robot(id, randomizeDirection());
		return r;
	}
	private static Robot.Direction randomizeDirection(){
		int random_direction_int = _rand.nextInt(AMOUNT_OF_DIRECTIONS); 
		Robot.Direction direction = Robot.Direction.UP;
		switch (random_direction_int) {		
			case 0:
				direction = Robot.Direction.UP;
				break;
			case 1:
				direction = Robot.Direction.RIGHT;
				break;
			case 2:
				direction = Robot.Direction.DOWN;
				break;
			case 3:
				direction = Robot.Direction.LEFT;
				break;
	
			default:
				System.out.println("you fucked up badly in ExampleProg in the createRandomDirectionBot method");
				break;
		}
		
		return direction; //fixme
	}
	private static Point createRandomPosition(int world_size){
		
		int x = _rand.nextInt(world_size);
		int y = _rand.nextInt(world_size);
		return new Point(x,y);
	}
}
