import java.awt.Point;


public class CompPoint extends Point implements Comparable<CompPoint> {

	/**
	 * 
	 */
	private static final long serialVersionUID = 2761217136534178888L;
	public CompPoint(int x, int y) {
		super(x,y);
	}
	@Override
	public int compareTo(CompPoint o) {
		return ((this.x+this.y)-(o.x+o.y));
	}

}
