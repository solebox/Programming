import java.awt.Dimension;
import java.awt.event.ActionListener;

import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextArea;
import javax.swing.JTextField;



public class ClientView {
	private JFrame _frame;
	private JTextArea _textArea;
	private JTextField _textField;
	
	public ClientView(int width,int height){
		ActionListener sendMessageListener = new SendMessageListener();
		ActionListener disconnectButtonListener = new DisconnectButtonListener();
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
		
		 send.addActionListener(sendMessageListener);
		 _textField.addActionListener(sendMessageListener);
		 disconnect.addActionListener(disconnectButtonListener);
	}
	public String getUserInput(){
		String msg = _textField.getText();
		_textField.setText("");
		return msg;
		
	}
	public void postToUserChatWindow(String msg){
		_textArea.append(msg);
	}
}
