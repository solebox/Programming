import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;
import java.awt.Point;

public class Main {

	public static void main(String[] args) {
		int iterations = 6;
		Random rand = new Random();
		ArrayList<String> helper = new ArrayList<String>();
		Scanner scanner = new Scanner(System.in);
		GenLinkedList<String> list = new GenLinkedList<String>();
		GenLinkedList<Point> pointList = new GenLinkedList<Point>();
		GenLinkedList<CompPoint> compPointList = new GenLinkedList<CompPoint>();
		int x,y;
		String tmp;
		for (int i = 0; i < iterations; i++) {
			tmp = scanner.next();
			list.add(tmp);
		}
		System.out.println(list);
		for (int i = 0; i < iterations; i++) {
			try{
				tmp = list.remove();
				helper.add(tmp);
			}catch(EmptyListException e){
				System.out.println(e);
			}
		}
		for (int i = 0; i < iterations; i++) {
			list.add(helper.get(helper.size()-1));
			helper.remove(helper.size()-1);
		}
		System.out.println(list);
		for (int i = 0; i < 10; i++) {
			x = rand.nextInt(100);
			y = rand.nextInt(100);
			pointList.add(new Point(x, y));
		}
		System.out.println(pointList);
		for (int i = 0; i < 10; i++) {
			x = rand.nextInt(100);
			y = rand.nextInt(100);
			compPointList.add(new CompPoint(x,y));
		}
		System.out.print(compPointList+"\n");
		System.out.println(GenLinkedList.minimum(compPointList));
	}	
}