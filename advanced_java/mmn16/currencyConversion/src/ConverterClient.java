import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;

/**
 * here all the client logic resides
 * @author solekiller
 *
 */
public class ConverterClient {
	private DatagramSocket _socket;
	private final String _address = "localhost";
	private final int _port = 4444;
	private int _requestIndex = 0;
	private final int _udeRequestTimeout = 5000;
	public static final String[] _currencies = {"ILS","KRONE","YUAN","PESO","EURO","USD"};
	private String _host;
	public ConverterClient(String host){
		_host = host;
		try {
			_socket = new DatagramSocket();
		} catch (SocketException e) {
			e.printStackTrace();
		}
	}
	/**
	 * this is the static method that returns all the possible currencies , it is static since it was
	 * taken into account that a user of this logic might want to initialized the end-user interface before 
	 * instanciating the connection and the client logic
	 * @return - a string array representation of the possible currencies
	 */
	public static String[] getCurrencies(){
		return _currencies;
	}
	/**
	 * this method is in charge of querieng the server for currency conversion
	 * @param from - the currencie symbol to convert from
	 * @param to - the currency symbol to convert to
	 * @param amount - the amount to be converted
	 * @return - a string representation 
	 */
	public String queryServer(String from,String to, Double amount){
		byte[] buff = new byte[256];
		_requestIndex++;
		String[] response;
		String msg = ""+_requestIndex+","+from+","+to+","+amount.toString();
		buff = msg.getBytes();
		DatagramPacket packet;
		try {
			
			InetAddress address = InetAddress.getByName(_address);
			if (_host.length() != 0){
				InetAddress.getByName(_host);
			}
			packet = new DatagramPacket(buff,buff.length,address,_port);
			_socket.send(packet);
			_socket.setSoTimeout(_udeRequestTimeout);
			buff = new byte[265];
			packet = new DatagramPacket(buff, buff.length);
			_socket.receive(packet);
			msg = new String(packet.getData());
			response = msg.split(",");
			msg = response[1];
			if (Integer.parseInt(response[0]) == _requestIndex)
				return msg;
		} catch (UnknownHostException e) {
			System.err.println(e);
		}
		catch (IOException e) {
			System.err.println(e);
		}
		return null; //failed to return msg
	}
	/**
	 * a method that tells the client to close the socket to the server
	 */
	public void disconnect(){
		_socket.close();
	}

}
