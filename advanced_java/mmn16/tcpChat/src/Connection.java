
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;
import java.util.ArrayList;


/**
 * this is the connection abstraction class
 * @author solekiller
 *
 */
public class Connection  extends Thread{
	private Socket _client;
	private ArrayList<Connection> _connections;
	private BufferedWriter _myWriter;
	private BufferedReader _myReader;
	private String _nick;
	boolean _connected = true;
	/**
	 * here a connection is instantiated 
	 * @param client - the socket object reference is passed from the server via this parameter
	 * @param nick - the initial nickname of the user
	 * @param connections - an arraylist of all the connection abstraction of all users
	 */
	public Connection(Socket client,String nick,ArrayList<Connection> connections)
	{
		_nick = nick;
		_client = client;
		_connections = connections;
		String msg ="User List:\n";
		synchronized (_connections) {
			for (int i = 0; i < _connections.size(); i++) {
				msg += _connections.get(i).getNick() + '\n';
			}
		}
		msg += "################## \n welcome.\n please use /help command for usage info.";
		try {
		
			_myWriter = new BufferedWriter(new OutputStreamWriter(_client.getOutputStream()));
		    _myReader = new BufferedReader(new InputStreamReader(_client.getInputStream()));
		    _myWriter.write(msg,0,msg.length());
		    _myWriter.newLine();
			_myWriter.flush();
		    sendMessageToAllClients(_nick+" Joined the chat.");
		} catch (IOException e) {
			System.err.println(e);
		}
	}
	/**
	 * this method sends the message to be sent to all the user connections present
	 * @param msg - the message to be passed
	 */
	public void sendMessageToAllClients(String msg){
		synchronized (_connections) {
			for (int i = 0; i < _connections.size(); i++) {
				_connections.get(i).sendMessage(msg);
			}
		}
	}
	/**
	 * this is the method that sends a message to this specific user that has this connection 
	 * @param msg - the message to be sent
	 */
	public void sendMessage(String msg){
		try {
			_myWriter.write(msg, 0, msg.length());
			_myWriter.newLine();
			_myWriter.flush();
		} catch (IOException e) {
			System.err.println(e);
			_connected = false;
		}
		
	}
	/**
	 * gets the user's current nickname
	 * @return
	 */
	public String getNick(){
		return _nick;
	}
	public void removeThisConnection(){
		synchronized (_connections) {
			_connections.remove(this);
		}
	}
	/**
	 * this is the run method of the connection thread here all the descision making is done
	 */
	 public void run()
	 {
		String[] words;
		String line = null;
		String srvmsg = "";
		try {
			while (_connected){
				if (_client.isConnected() || _myReader != null){
					line = _myReader.readLine();	
					if (line != null){
						words = line.split(" ");
						if (line.toCharArray()[0] == '/'){
							if (words[0].equals("/nick")){
								_nick = words[1];
							}
							else if (words[0].equals("/help") || words[0].equals("/?")){
								srvmsg =  "/list for userlist \n /nick to change nickname\n";
								sendMessage(srvmsg);
							}else if(words[0].equals("/list")){
								srvmsg = "User List:\n";
								synchronized (_connections) {
									for (int j = 0; j < _connections.size(); j++) {
										srvmsg += _connections.get(j).getNick()+'\n';
									}
									sendMessage(srvmsg);
								}
							}else{
								srvmsg = "invalid command";
								sendMessage(srvmsg);
							}
						}else{
							sendMessageToAllClients("Client #"+_nick+":"+line);
						}
					}else{
						_connected = false;
						removeThisConnection();
						sendMessageToAllClients("Client #"+_nick+" disconnected");
					}
				}else{
					_connected = false;
					removeThisConnection();
					sendMessageToAllClients("Client #"+_nick+" disconnected");
				}
				
			}
		}catch (Exception e) {
			System.err.println(e);
		}
	 }

}
