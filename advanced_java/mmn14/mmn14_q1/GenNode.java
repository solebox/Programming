/**
 * a generic node , gets a generic type and holds it
 * 
 * @author solekiller
 *
 * @param <T>
 */
public class GenNode<T> {
	private T _value;
	private GenNode<T> _next;
	/**
	 * our node constructor , ceates the node and a pointer to null
	 * @param value - the value to put in the node on creation
	 */
	public GenNode(T value) {
		_value = value;
		_next = null;
	}
	/**
	 * another constructor, this time it gets another node and points to it instead of null
	 * @param value - the value to hold
	 * @param next - the next node to point to
	 */
	public GenNode(T value, GenNode<T> next){
		_value = value;
		_next = next;
	}
	/**
	 * this is the value getter, it gets the value
	 * @return the value
	 */
	public T getValue() {
		return _value;
	}
	/**
	 * this is the value setter it sets the value
	 * @param value the value we want to set
	 */
	public void setValue(T value) {
		this._value = value;
	}
	/**
	 * this method gets the next node
	 * @return
	 */
	public GenNode<T> getNnext() {
		return _next;
	}
	/**
	 * this method sets the next node
	 * @param next the node we want to be our next
	 */
	public void setNext(GenNode<T> next) {
		this._next = next;
	}
}
