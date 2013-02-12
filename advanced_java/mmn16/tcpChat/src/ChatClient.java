import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import java.io.BufferedReader;
import java.io.BufferedWriter;

import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.ConnectException;
import java.net.Socket;
import java.net.UnknownHostException;
import java.nio.charset.MalformedInputException;

import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextArea;
import javax.swing.JTextField;

/**
 * this is the chat client class it hosts the client gui and logic code
 * @author solekiller
 *
 */
public class ChatClient {
	static BufferedReader stdin = new BufferedReader(new InputStreamReader(System.in));
	private BufferedWriter _myWriter; 
	private  BufferedReader _myReader;
	private JFrame _frame;
	private JTextArea _textArea;
	private JTextField _textField;
	private final int DEFAULT_WIDTH = 500,DEFAULT_HEIGHT = 500;
	private Socket _socket;
	private boolean _connected = true; 
	private boolean _disconnect = false; 
	public final int BAD_NICKNAME_ERR = 1;
/**
 * this is the main program that runs the client class
 */
	public static void main(String args[])
	{
		String nick = "";
		String hostname = "";
		do {
			hostname = JOptionPane.showInputDialog("please choose a hostname");
			if (hostname == null)
				System.exit(0);
			if (hostname.equals(""))
				JOptionPane.showMessageDialog(null, "invalid hostname");
		}while(hostname == null || hostname.equals(""));
		do {
			nick = JOptionPane.showInputDialog("please choose a nickname");
		}while(nick != null && nick.equals(""));
		if (nick != null){
			ChatClient client = new ChatClient(nick,hostname);
			client.start();
		}
	}
	/**
	 * this is the gui initialization method
	 * @param width - the main window width
	 * @param height - the main window height
	 */
	private void showClientGui(int width, int height){
		int rows = 2;
		int cols = 2;

		JPanel panel = new JPanel();
		JButton send = new JButton("send");
		JButton disconnect = new JButton("disconnect");
	
		_textField = new JTextField();
		_textField.setMaximumSize(new Dimension(400, 40));
		panel.setLayout(new BoxLayout(panel, BoxLayout.PAGE_AXIS));
		 _frame = new JFrame("Chat client");
		 _frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		 _frame.setSize(width,height);
		 _textArea = new JTextArea("",rows,cols);
		 _textArea.setLineWrap(true);
		 panel.add(_textArea);
		 panel.add(_textField);
		 panel.add(send);
		 panel.add(disconnect);
		
		 _frame.add(panel);
		 _frame.setVisible(true);
		 SendMessageListener smlisten = new SendMessageListener();
		 send.addActionListener(smlisten);
		 _textField.addActionListener(smlisten);
		 disconnect.addActionListener(new disconnectButtonListener());
		 
	}
	/**
	 * this is the chatclient constructor	
	 * @param nick this is the nickname to be used
	 * @param hostname - this is the hostname to connect to (in the maman they specified hostname in this q and ip in the other so i figured that was the idea)
	 */
	public ChatClient(String nick,String hostname){
		showClientGui(DEFAULT_WIDTH,DEFAULT_HEIGHT);
	
		try {
				_socket =  new Socket(hostname, 5000);
				 if (_socket != null){
					  _myWriter = new BufferedWriter(new OutputStreamWriter(_socket.getOutputStream()));  
					  _myReader = new BufferedReader(new InputStreamReader(_socket.getInputStream()));
					  _myWriter.write("/nick "+nick, 0, ("/nick "+nick).length());
					  _myWriter.newLine();
						_myWriter.flush();
				 }
			}
			catch (MalformedInputException e){
				JOptionPane.showMessageDialog(null,"please dont insert evil chars in the nick");
				_connected = false;
			}
			catch (UnknownHostException e) {
				JOptionPane.showMessageDialog(null, "unknown host");
			}
			catch (ConnectException e){
				JOptionPane.showMessageDialog(null, "cant connect server is down");
				_connected = false;
			}
			catch (Exception e){
				System.out.println(e);
			}
	}
	/**
	 * the send message listener , its attached to the textfield and to the send button
	 * 
	 *
	 */
	private class SendMessageListener implements ActionListener {
		private String msg;
		@Override
		public void actionPerformed(ActionEvent arg0) {
			msg = _textField.getText();
			_textField.setText("");
			try {
				if (_connected){
					_myWriter.write(msg, 0, msg.length());
					_myWriter.newLine();
					_myWriter.flush();	 
				}else{
					JOptionPane.showMessageDialog(null, "not connected.");
				}
			}
			catch (Exception e){
				System.out.println(e);
			}
		}
	}
	/**
	 * the disconnect listener, its attached to the disconnect button and it dictates what the disconnection functionality will be
	
	 *
	 */
	private class disconnectButtonListener implements ActionListener {
		String msg = "disconnecting...";
		@Override
		public void actionPerformed(ActionEvent arg0) {
				try {
					if (_connected){
						_myWriter.write(msg, 0, msg.length());
						_myWriter.newLine();
						_myWriter.flush();	 // Send to server	
						_connected = false;
						_disconnect = true;
					}else{
						JOptionPane.showMessageDialog(null, "you are already not connected");
					}
				}
				catch (Exception e){
					System.out.println(e);
				}
		}
		
	}
	/**
	 * here the listening loop starts
	 */
	public void start(){
		String input = null;
		 while (_connected)
		   {
				try {
					if (_myReader != null && !_socket.isClosed() && !_disconnect && _connected){
						input = _myReader.readLine();
						if (_disconnect){
							input = null;
							_socket.close();
						}
						if (input == null){
							_connected = false;
							_textArea.append("client disconnected."+"\n");
						}else{
							_textArea.append(input+"\n");
						}
					}else{
						_textArea.append("server connection broken."+"\n");
						_connected = false;
					}				
				}
				catch (ConnectException e){
					System.err.println(e);
				}
				catch (Exception e){
					_textArea.append("ERROR: broken pipe.\n");
					_connected = false;
					System.err.println(e);
					System.exit(1);
				}
				
		   }
		 System.exit(0);
	}

}
