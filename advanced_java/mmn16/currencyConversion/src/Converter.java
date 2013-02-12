
import java.io.IOException;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

import java.util.HashMap;

/**
 * this is the currecny conversion udp server class
 * @author solekiller
 *
 */
public class Converter {
	private HashMap<String, Double> _toUSD;
	private final int PORT = 4444;
	private DatagramSocket _socket;
/**
 * this is the conversion udp server constructor here it is initialized with all the currency info
 */
	public Converter(){
		_toUSD = new HashMap<String, Double>();
		_toUSD.put("ILS",0.27);
		_toUSD.put("KRONE",0.18);
		_toUSD.put("YUAN",0.16);
		_toUSD.put("PESO",0.20);
		_toUSD.put("EURO",1.33);
		_toUSD.put("USD",1.0);
	}
	/**
	 * the conversion method
	 * @param from - what currency to convert from
	 * @param to - what currency to convert to 
	 * @param amount - what is the amount of the cash to convert
	 * @return returns a Double representation of the answer
	 */
	public Double convert(String from, String to,Double amount){
		Double in_usd,tmp,result;
		result = 0.0;
		if (_toUSD.containsKey(from) && _toUSD.containsKey(to)){
			in_usd = _toUSD.get(from)*amount;
			tmp = _toUSD.get(to);
			tmp = (1.0/tmp);
			result = in_usd * tmp;
		}else{
			System.err.println("requested currency doesnt exist"); 
		}
		return result;
	}
	/**
	 * the server starts up here, this is the main that calls it
	 * no cli arguments are needed
	 */
	public static void main(){
		Converter converter = new Converter();
		converter.startListening();
	}
	/**
	 * the socket is initialized here and the server starts listening for packets
	 */
	public void startListening(){
		String datum;
		String[] data;
		String from,to,resultString;
		Double amount, result;
		int port,requestIndex;
		InetAddress address;
		try {
			_socket = new DatagramSocket(PORT);
			byte[] buf = new byte[256];
			DatagramPacket packet = new DatagramPacket(buf, buf.length);
			while (true){
				packet = new DatagramPacket(buf, buf.length);
				_socket.receive(packet);
				 datum = new String(packet.getData());
				 address = packet.getAddress();
				 port = packet.getPort();
				 data = datum.split(",");
				 requestIndex = Integer.parseInt(data[0]);
				 from = data[1];
				 to = data[2];
				 amount = Double.parseDouble(data[3]);
				 result = convert(from, to, amount);
				 resultString = requestIndex + "," +result.toString();
				 packet = new DatagramPacket(resultString.getBytes(), resultString.length(), address, port);
				 _socket.send(packet);
			}
		} catch (IOException e) {
			System.err.println(e);
		}
	}

}
