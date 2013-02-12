import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

/**
 * this is the chat server class, very strait forward
 * @author solekiller 
 *
 */
public class ChatServer {
	public static int clientIndex = 0;
	private ArrayList<Connection> _connections = new ArrayList<Connection>();
	private final int PORT = 5000;
	public static void main(String args[])
	{
		ChatServer serv = new ChatServer();
		serv.startServer();
	}
	/**
	 * this is the method that starts the server here all the server logic resides
	 */
	public void startServer(){
		try {
			ServerSocket ServSock = new ServerSocket(PORT);
			while (true) {
				Socket sock = ServSock.accept();
				synchronized (_connections) {
					Connection conn = new Connection(sock,""+clientIndex,_connections);
					clientIndex++;
					_connections.add(conn);
					conn.start();
				}
			}
		}
		catch (Exception e){
			
			System.err.println(e);
		}
	}
}
