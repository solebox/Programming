
public class ClientMain {
	/**
	 * here the client main resides, this is where it all begins for the client side
	 */
	public static final int DEFAULT_WIDTH=500,DEFAULT_HEIGHT=500;
	public static void main(String args[]){
		String host = "";
		if (args.length > 0)
			host = args[0];
		new ClientView(DEFAULT_WIDTH, DEFAULT_HEIGHT,host);
	}
}
