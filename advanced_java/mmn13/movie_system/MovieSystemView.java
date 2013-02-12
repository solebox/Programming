

import javax.imageio.ImageIO;
import javax.swing.*;




import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.lang.String;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Observable;
import java.util.Observer;


/**
 * the movie system view
 * @author solekiller
 *
 */
public class MovieSystemView extends javax.swing.JFrame implements Observer{
    private static final long serialVersionUID = 1L;
    private static final String TITLE = "Ticket System";
    private static final int TAKEN = 0, NOT_TAKEN = 1;
    private static final int DEFAULT_ROWS = 4,DEFAULT_SEATS = 4;
    private JPanel[] _sittingSelection;
    private JPanel _personalInfoInput,_receipt;
    private final Hour[] SCREENINGS;
    private MovieSystemModel _model;
    private String _currentMovie = null;
    private Hour _currentHour = null;
    private int _currentHourIndex;
    private JButton[][] _buttonMatrix = null;  
    private ImageIcon[] _iconImages;
    private int _rowAmount, _seatAmount;
    private ArrayList<Seat> _theSeats;
    private double _subTotal;
/**
 * hour view constructor , gets the amount of rows and seats and initializes the gui and model accordingly 
 * @param initRows the amount of rows in our cinema
 * @param initSeats the amount of seats in our cinema
 * @throws HeadlessException 
 */
    public MovieSystemView(int initRows, int initSeats) throws HeadlessException {
        super(TITLE);
        _rowAmount = initRows; _seatAmount = initSeats;
        _buttonMatrix = new JButton[initRows][initSeats];
        _model = new MovieSystemModel(initRows, initSeats);
        SCREENINGS = _model.getScreeningTimes();
        _model.addObserver(this);
        _currentHourIndex = 0;
        _currentHour = SCREENINGS[_currentHourIndex];
        int width,height,gap,rows,cols;
        width = 800; height = 800; gap = 5;
        rows = 2; cols = 2;
        this.setLayout(new GridLayout(cols,rows,gap, gap));
        this.setSize(width,height);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        addPanels(initRows,initSeats);
        this.setVisible(true);
    }
    /**
     * same constructor only with default values
     */
    public MovieSystemView(){
    	this(DEFAULT_ROWS,DEFAULT_SEATS);
    }
    /**
     * here the billing data is updated from the model
     */
	@Override
	public void update(Observable o, Object arg) {
		MvcMessage msg = (MvcMessage)arg;
		_theSeats = msg.getSeats(); /* the return value ArrayList<Seat> */ 
		_subTotal = msg.getSubtotal();
	}
	/**
	 * this method resets the ticket system gui and makes a new model 
	 */
	private void reset(){
    	_model = new MovieSystemModel(_rowAmount, _seatAmount);
    	for (int i = 0; i < _buttonMatrix.length; i++) {
			for (int j = 0; j < _buttonMatrix[0].length; j++) {
				_buttonMatrix[i][j].setIcon(_iconImages[NOT_TAKEN]);
			}
		}
    	_model.addObserver(this);
    	_currentHourIndex = 0;
    	_currentHour = SCREENINGS[_currentHourIndex];
    }
	// private method to add the panels
	private void addPanels(int rows, int seats){
        addSittingSelectionPanels(rows, seats);
    }
	// adds the sitting selection panel view
    private void addSittingSelectionPanels(int rows,int seats){
        int gap,width,height, panelNumber;
        gap = 2;
        width = 800; height = 800;
        panelNumber = 1;

        _sittingSelection = new JPanel[3];
        _sittingSelection[0] = new JPanel(new GridLayout(rows,seats,gap,gap));
        _sittingSelection[1] = new JPanel();
        _sittingSelection[1].setLayout(new BoxLayout(_sittingSelection[1],BoxLayout.PAGE_AXIS));
        _sittingSelection[2] = new JPanel(new FlowLayout());
        addSeats(rows,seats);
        addSittingSceenOptions();
        JButton ok = new JButton("ok");
        ok.addActionListener(new OkListener(panelNumber));
        _sittingSelection[2].add(ok);
        this.add(_sittingSelection[0]);
        this.add(_sittingSelection[1]);
        this.add(_sittingSelection[2]);
        this.setSize(width, height);
    }
    // removes the sitting selection panel
    private void removeSittingSelectionPanels(){
    	for (int i = 0; i < _sittingSelection.length; i++) {
			this.remove(_sittingSelection[i]);
		}
    }
    // adds the seats to the sitting selection panel
    private void addSeats(int rows, int seats){
                ImageIcon[] icons = getIconBgs();
                _iconImages = icons;
                for (int row = 0; row < rows; row++){
                    for (int seat = 0; seat < seats;seat++){
                        JButton seatButton = new JButton();
                        seatButton.addActionListener(new SeatListener(row, seat));
                        seatButton.setIcon(icons[NOT_TAKEN]);
                        _buttonMatrix[row][seat] = seatButton;
                        _sittingSelection[0].add(seatButton);
                    }
                }

    }
    // adds the sitting screen options
    private void addSittingSceenOptions(){
        int boxWidth,boxHeight;
        boxHeight = 20;
        boxWidth = 300;
        String[] movieNames = _model.getMovieNames();
        _currentMovie = movieNames[0];
        _sittingSelection[1].add(new JLabel("movie name:"));
        JComboBox cb1 = new JComboBox();
        JComboBox cb2 = new JComboBox();
        cb2.setMaximumSize(new Dimension(boxWidth,boxHeight));
        cb1.setMaximumSize(new Dimension(boxWidth,boxHeight));
        for (int i = 0; i < movieNames.length; i++) {
			cb1.addItem(movieNames[i]);
		}
        _sittingSelection[1].add(cb1);
        _sittingSelection[1].add(new JLabel("hour:"));
        for (int i = 0; i < SCREENINGS.length; i++) {
			cb2.addItem(SCREENINGS[i]);
		}
        _sittingSelection[1].add(cb2);
        cb1.addActionListener(new MovieListener(cb1));
        cb2.addActionListener(new ScreeningTimeListener(cb2));


    }
    // a helper method that gets the seat icons
    private ImageIcon[] getIconBgs(){
        ImageIcon[] iconImages = new ImageIcon[2];
        try {
             iconImages[NOT_TAKEN] = new ImageIcon( ImageIO.read(getClass().getResource("images/FREE_SEAT.png")));
             iconImages[TAKEN] = new ImageIcon(ImageIO.read(getClass().getResource("images/TAKEN.png")));
        } catch (IOException ex) {
            System.err.println("couldn't open icon files");
        }

        return iconImages;
    }
    // this is the second screen the personal info panel , the user data wasnt saved anywhere because its never used
    private void addPersonalInfoInputPanels(){
    	int fieldHeight, fieldWidth,height,width,panelNumber;
    	height = 360; width = 200; 
    	fieldWidth = 300; fieldHeight = 20;
    	JTextField tmpField;
    	panelNumber = 2;
    	_personalInfoInput = new JPanel();
    	_personalInfoInput = new JPanel();
    	_personalInfoInput.setLayout(new BoxLayout(_personalInfoInput,BoxLayout.PAGE_AXIS));
    	_personalInfoInput.add(new JLabel("name:"));
    	tmpField = new JTextField();
    	tmpField.setMaximumSize(new Dimension(fieldWidth, fieldHeight));
    	_personalInfoInput.add(tmpField);
    	_personalInfoInput.add(new JLabel("last name:"));
    	tmpField = new JTextField();
    	tmpField.setMaximumSize(new Dimension(fieldWidth, fieldHeight));
     	_personalInfoInput.add(tmpField);
    	_personalInfoInput.add(new JLabel("phone number:"));
    	tmpField = new JTextField();
    	tmpField.setMaximumSize(new Dimension(fieldWidth, fieldHeight));
     	_personalInfoInput.add(tmpField);
    	_personalInfoInput.add(new JLabel("Email:"));
    	tmpField = new JTextField();
    	tmpField.setMaximumSize(new Dimension(fieldWidth, fieldHeight));
    	_personalInfoInput.add(tmpField);
    	JButton ok = new JButton("ok");
    	ok.addActionListener(new OkListener(panelNumber));
    	_personalInfoInput.add(ok);
     	this.add(_personalInfoInput);
     	this.setSize(width, height);
     	
    }
    // this method removes the personal info panel to make place for the recipt panel
    private void removePersonalInfoInputPanel(){
			this.remove(_personalInfoInput);
    }
    // this is the last panel that will be displayed before the system is restarted, here you would see the billing stuff and the tickets ordered
    private void addReceiptPanel(){
    	String receiptText = "";
    	int textRows, textColumns;
    	textRows = 10;
    	textColumns = 10;
    	int width,height;
    	width = 400;
    	height = 300;
    	receiptText = generateRecieptText();
    	_receipt = new JPanel();
    	_receipt.setLayout(new BoxLayout(_receipt, BoxLayout.PAGE_AXIS));
    	JTextArea ta = new JTextArea(receiptText, textRows, textColumns);
 		ta.setLineWrap(true);
 		JScrollPane sbrText = new JScrollPane(ta);
 		sbrText.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
 		_receipt.add(sbrText);
 		JButton ok = new JButton("OK");
 		ok.addActionListener(new OkListener(3));
    	_receipt.add(ok);
    	this.setSize(width, height);
    	this.add(_receipt);
    }
    // this is a helper method that creates the recipt text , ticket numbers movie name screening hour and total price to pay
    private String generateRecieptText(){
    	String reciept = "";
    	HashMap<String, String[]> hash = new HashMap<String, String[]>();// used hash to sort movie tickets at O(1) (yeah avg case , but we are in the real world now :D yay)
    
    	for (Seat seat : _theSeats) {
    		if (hash.containsKey(seat.getMovieName())){
    			String tmp = hash.get(seat.getMovieName())[seat.getHourIndex()];
    			if (tmp == null)
    				hash.get(seat.getMovieName())[seat.getHourIndex()] = "\trow: " + (seat.getRow()+1) + ", seat number: " + (seat.getSeatNumber()+1)+"\n";
    			else 
    				hash.get(seat.getMovieName())[seat.getHourIndex()] += "\trow: " + (seat.getRow()+1) + ", seat number: " + (seat.getSeatNumber()+1)+"\n";
    		}else{
    			hash.put(seat.getMovieName(), new String[SCREENINGS.length]);
    			String tmp = hash.get(seat.getMovieName())[seat.getHourIndex()];
    			if (tmp == null)
    				hash.get(seat.getMovieName())[seat.getHourIndex()] = "\trow: " + (seat.getRow()+1) + ", seat number: " + (seat.getSeatNumber()+1)+"\n";
    			else 
    				hash.get(seat.getMovieName())[seat.getHourIndex()] += "\trow: " + (seat.getRow()+1) + ", seat number: " + (seat.getSeatNumber()+1)+"\n";
    		}
		}
    	for (String movieName : hash.keySet()) {
			reciept += movieName+":\n";
			for (int i = 0; i < SCREENINGS.length; i++) {
				if (hash.get(movieName)[i] != null)
					reciept += "at: " + SCREENINGS[i] + ":\n" + hash.get(movieName)[i];
			}
		}
    	reciept += "Total Price: "+ _subTotal + "\n";
    	return reciept;
    }
    // this method updates the seat display
	private void updateSeatDisplay() {
		ArrayList<Seat> currentlyTaken = _model.getCurrentTheaterTakenSeats(_currentMovie, _currentHourIndex);
		for (int i = 0; i < _buttonMatrix.length; i++) {
			for (int k = 0; k < _buttonMatrix[0].length; k++) {
				_buttonMatrix[i][k].setIcon(_iconImages[NOT_TAKEN]);
			}
		}
		for (int i = 0; i < currentlyTaken.size(); i++) {
			_buttonMatrix[currentlyTaken.get(i).getRow()][currentlyTaken.get(i).getSeatNumber()].setIcon(_iconImages[TAKEN]);
		}
	}
	// this method removes the recipt panel
    private void removeReciptPanel(){
    	this.remove(_receipt);
    }
    // this is the seat action listener, it listens for seat clicks and sends the event to the model to be handles along with the movie and hour data for further 
    // computation and state change
	private class SeatListener implements ActionListener {
		private int _row,_seatNum;
		public SeatListener(int row, int seat){
			_row = row;
			_seatNum = seat;
			
		}
		@Override
		public void actionPerformed(ActionEvent e) {
			Seat seatOb;
			try{
				seatOb =  _model.occupySeat(_currentMovie, _row, _seatNum, _currentHour);
				if(seatOb == null){
					_buttonMatrix[_row][_seatNum].setIcon(_iconImages[TAKEN]);
				}else{
					_model.freeSeat(_currentMovie, seatOb, _currentHour);
					_buttonMatrix[_row][_seatNum].setIcon(_iconImages[NOT_TAKEN]);
				}
			}catch(Exception ex){
				System.err.print(ex);
			}
			
		}
		
	}
	// this is the action listener to for the movie jcombobox
	private class MovieListener implements ActionListener{
		private JComboBox _cb;
		public MovieListener(JComboBox cb){
			_cb = cb;
		}
        public void actionPerformed(ActionEvent e) {
          _currentMovie = _cb.getSelectedItem().toString();
          updateSeatDisplay();
        }
	
	          
	}
	// this is the action listener for the hour jcombobox dropdown list
	private class ScreeningTimeListener implements ActionListener{
		private JComboBox _cb;
		int hourIndex;
		public ScreeningTimeListener(JComboBox cb){
			_cb = cb;
		}  
		public void actionPerformed(ActionEvent e) {
	        hourIndex = _cb.getSelectedIndex();
	        _currentHour = SCREENINGS[hourIndex];
	        _currentHourIndex = hourIndex;
	        updateSeatDisplay();
	     }
	}
	// this is the action listener for the ok button
	private class OkListener implements ActionListener {
		private int _callingScreenNumer;
		public OkListener(int callingScreenNumber) {
			_callingScreenNumer = callingScreenNumber;
		}
		@Override
		public void actionPerformed(ActionEvent e) {
			switch (_callingScreenNumer) {
			case 1: //addSittingSelectionPanels
		        removeSittingSelectionPanels();
		        addPersonalInfoInputPanels();
			break;
			case 2:
				removePersonalInfoInputPanel();
				addReceiptPanel();
			break;
			case 3:
				removeReciptPanel();
				reset();
				addSittingSelectionPanels(_rowAmount, _seatAmount);
			break;

			default:
				
			break;
			}
			
		}
	}

}