
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;



public class DictionaryView {
	private JFrame _frame;
	private JTextArea _textArea;
	private Controller _controller;
	
	public DictionaryView(Controller controller){
		int width,height;
		width = 520;
		height = 440;
		_controller = controller;
		_frame = new JFrame("Dictionary");
		_frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		_frame.setLayout(new FlowLayout());
		_frame.setSize(new Dimension(width, height));
		addPanels(_frame);
		_frame.setVisible(true);
	}
	private void addPanels(JFrame frame){
		JPanel left_panel = new JPanel();
		JPanel right_panel = new JPanel();
		addTextArea(left_panel);
		left_panel.setLayout(new BoxLayout(left_panel, BoxLayout.PAGE_AXIS));
		right_panel.setLayout(new BoxLayout(right_panel, BoxLayout.PAGE_AXIS));
		
		left_panel.setPreferredSize(new Dimension(350, 400));
		right_panel.setPreferredSize(new Dimension(111,400));
		
		frame.getContentPane().add(left_panel);
		frame.getContentPane().add(right_panel);
		
		addButtons(right_panel);
		
	}
	private void addButtons(JPanel right_panel) {
		JButton[] buttons = new JButton[6];
		for (int i = 0; i < buttons.length; i++) {
			buttons[i] = new JButton();
			buttons[i].addActionListener(new ButtonListener(i));
			right_panel.add(buttons[i]);
		}
		buttons[0].setText("Create");
		buttons[1].setText("Search");
		buttons[2].setText("Update");
		buttons[3].setText("Delete");
		buttons[4].setText("Load Dict.");
		buttons[5].setText("Save Dict.");
		
	}
	private void addTextArea(JPanel left_panel) {
		String dicText ="";
		_textArea = new JTextArea(dicText);
		_textArea.setLineWrap(false);
		JScrollPane scroll = new JScrollPane(_textArea);
		left_panel.add(scroll);
	}
	private class UpdateCombo implements ActionListener {
		JComboBox _cb;
		JTextField _field;
		public UpdateCombo(JComboBox cb,JTextField field){
			_cb = cb;
			_field = field;
		}
		@Override
		public void actionPerformed(ActionEvent arg0) {
			String term = _controller.search((String)_cb.getSelectedItem());
			if (term == null){
				System.err.println("fatal error in update combobox"); //cant really happen
			}else{
				_field.setText(_controller.search((String)_cb.getSelectedItem()));
			}
		}

	}

	private class ButtonListener implements ActionListener{
		private int _buttonNumber;
		public ButtonListener(int buttonNumber) {
			_buttonNumber = buttonNumber;
		}

		@Override
		public void actionPerformed(ActionEvent e) {
			switch (_buttonNumber) {
			case 0:
				createButtonPressed();
				break;
			case 1:
				searchButtonPressed();
				break;
			case 2:
				updateButtonPressed();
				break;
			case 3:
				deleteButtonPressed();
				break;
			case 4:
				loadDictButtonPressed();
				break;
			case 5:
				saveDictButtonPressed();
				break;
			default:
				System.err.println("invalid button number, please check code for " +
						"bad ActionListener assign..");
				break;
			}
		}

		private void createButtonPressed() {
			JPanel panel = new JPanel();
			JTextField term = new JTextField();
			JTextField def = new JTextField();
			panel.setPreferredSize(new Dimension(300,100));
			term.setPreferredSize(new Dimension(200,20));
			def.setPreferredSize(new Dimension(200,20));
			panel.add(new JLabel("term:"));
			panel.add(term);
			panel.add(new JLabel("definition:"));
			panel.add(def);
			try{
				JOptionPane.showMessageDialog( _frame, panel, "please enter the values you want", JOptionPane.QUESTION_MESSAGE);
				if (JOptionPane.YES_OPTION == JOptionPane.showConfirmDialog(_frame, "are you sure?", "sure?", JOptionPane.YES_NO_OPTION)) {
					    try{
					    	_controller.create(term.getText(), def.getText());
					    	_textArea.setText(_controller.dictString());
					    }catch(BadInput e){
					    	JOptionPane.showMessageDialog(_frame, "bad input bro,\n try just letters and spaces next time");
					    }catch(Exception e){
					    	System.err.println("bad input popup failed");
					    }
				}else{
					    //do nothing
				}
			}catch(Exception e){
				System.err.println("create procedure error");
			}
			
		}

		private void searchButtonPressed() {
			String input;
			String result;
			try{
				input = JOptionPane.showInputDialog("Please enter the term you are looking for:");
				if (input == null){
					//do nothing
				}else{
					result = _controller.search(input);
					if (result != null){
						_textArea.setText(input +" => "+result);
					}else{
						JOptionPane.showMessageDialog(_frame, "i couldn't find it, sorry");
					}
				}
			}catch(Exception e){
				System.err.println("error in search dialog");
			}
		}

		private void updateButtonPressed() {
			String[] terms = _controller.getTerms();
			int choice;
			JPanel panel = new JPanel();
			JComboBox cb = new JComboBox(terms);
			JTextField field = new JTextField(_controller.search(terms[0]));
			panel.setPreferredSize(new Dimension(300,100));
			field.setPreferredSize(new Dimension(200,20));
			
			cb.setPreferredSize(new Dimension(200,20));
			cb.addActionListener(new UpdateCombo(cb,field));
			panel.add(cb);
			panel.add(field);
			try{
				JOptionPane.showMessageDialog( _frame, panel, "which entry do you want to update?", JOptionPane.QUESTION_MESSAGE);
				choice = JOptionPane.showConfirmDialog(null, "are you sure?", "sure?", JOptionPane.YES_NO_OPTION);
			
				if (choice == JOptionPane.YES_OPTION){
					try{
						_controller.update((String)cb.getSelectedItem(), field.getText());
						_textArea.setText(_controller.dictString());
					}catch(Exception e){
						try{
							JOptionPane.showMessageDialog(_frame, "bad input, only letters and spaces please");
						}catch(Exception ex){
							System.err.println("bad user input");
						}
					}
				}
			}catch(Exception e){
				System.err.println("message boxes in update failed miserably");
			}
		}

		private void deleteButtonPressed() {
			String[] terms = _controller.getTerms();
			String term;
			try{
				JComboBox cb = new JComboBox(terms);
				cb.setEditable(false);
				JOptionPane.showMessageDialog( _frame, cb, "which entry should i delete?", JOptionPane.QUESTION_MESSAGE);
				term = (String) cb.getSelectedItem();
				_controller.delete(term);
				_textArea.setText(_controller.dictString());
			}catch(Exception e){
				System.err.println("delete dict entry dialog crashed");
			}
		}

		private void loadDictButtonPressed() {
			_controller.loadDict();
			_textArea.setText(_controller.dictString());
		}

		private void saveDictButtonPressed() {
			try{
				_controller.saveDict();
				JOptionPane.showMessageDialog(_frame, "dict. saved");
			}catch(IOException e){
				try{
					JOptionPane.showMessageDialog(_frame, "dict didn't save, try again.. if doesn't work: reintall");
				}catch(Exception ex){
					System.err.println("dict fail dialog failed"); //yo dawg, i heared you like exception handling
				}
			}
			catch(Exception e){
				System.err.println("save dict. dialog box crashed.");
			}
		}
		
	}
}
