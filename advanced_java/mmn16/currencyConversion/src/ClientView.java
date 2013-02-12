
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;


import javax.swing.BoxLayout;
import javax.swing.JButton;

import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;
/**
 * this is the client view, where the client starts running
 * @author solekiller 
 *
 */

public class ClientView {
	
	private JFrame _frame;
	private JTextField _field;
	private JComboBox _from;
	private JComboBox _to;
	private ConverterClient _client;
	private final String LOCALHOST = "127.0.0.1";
	/**
	 * this is the view's constructor it gets the width and the height of the client window
	 * and initializes the gui
	 * @param width - the window's width
	 * @param height  - the window's height
	 * @param host - the address of the host to connect to (will be passed to the client's logic class)
	 */
	public ClientView(int width,int height,String host){
		if (host.length() == 0){
			host = LOCALHOST;
		}
		_client = new ConverterClient(host);
		_frame = new JFrame("Convertsion client");
		_frame.setSize(width, height);
		_field = new JTextField();
		_from = new JComboBox(ConverterClient.getCurrencies());
		_to = new JComboBox(ConverterClient.getCurrencies());
		JButton convert = new JButton("convert");
		convert.addActionListener(new ConvertListener());
		JPanel panel = new JPanel();
		JPanel leftpanel = new JPanel();
		JPanel rightpanel = new JPanel();
		leftpanel.add(new JLabel("amount:"));
		leftpanel.add(_field);
		rightpanel.add(new JLabel("from:"));
		rightpanel.add(_from);
		rightpanel.add(new JLabel("to:"));
		rightpanel.add(_to);
		panel.setLayout(new FlowLayout());
		leftpanel.setLayout(new BoxLayout(leftpanel, BoxLayout.PAGE_AXIS));
		rightpanel.setLayout(new BoxLayout(rightpanel, BoxLayout.PAGE_AXIS));
		_frame.add(panel);
		panel.add(leftpanel);
		panel.add(rightpanel);
		leftpanel.add(convert);
		_frame.setVisible(true);
		_frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	
	/**
	 * this is the event listener for the convert button
	 *
	 */
	private class ConvertListener implements ActionListener{

		@Override
		public void actionPerformed(ActionEvent arg0) {
			String from,to,answer;
			Double amount;
			from = (String)_from.getSelectedItem();
			to = (String)_to.getSelectedItem();
			try{
				amount = Double.parseDouble(_field.getText());
				answer = _client.queryServer(from, to, amount);
				answer = "" + (Double.parseDouble(answer));
				if (answer == null)
					answer = "Server Error.";
				JOptionPane.showMessageDialog(_frame,answer);
			}catch(NumberFormatException e){
				JOptionPane.showMessageDialog(_frame,"bad number format");
			}
		}
		
	} 
}
