import java.awt.event.ActionListener;

/**
 * a data type used to transfer relevant button data between modules
 * in particular during initialization of the view from the controller (Coordinator)
 * @author solekiller
 *
 */
public class ButtonData {
	private int _value;
	private ActionListener _listener;
	public int getValue() {
		return _value;
	}
	public void setValue(int value) {
		this._value = value;
	}
	public ActionListener getListener() {
		return _listener;
	}
	public void setListener(ActionListener _listener) {
		this._listener = _listener;
	}

}
